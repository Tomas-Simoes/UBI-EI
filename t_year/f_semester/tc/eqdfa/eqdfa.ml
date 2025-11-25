open Ppx_yojson_conv_lib.Yojson_conv.Primitives

type estado = int [@@deriving yojson]
type simbolo = char option [@@deriving yojson]
type transicao = (estado * simbolo) * estado [@@deriving yojson]

type nfa =
  estado list * char list * transicao list * estado list * estado list
[@@deriving yojson]

let rec read_multiplelines () =
  try
    let line = read_line () in
    line ^ " " ^ read_multiplelines ()
  with End_of_file -> ""

let nfa_de_string_2 s =
  let s = String.trim s in
  let len = String.length s in
  if len < 2 || s.[0] <> '<' || s.[len - 1] <> '>' then
    failwith "Formato invalido"
  else
    let inner = String.sub s 1 (len - 2) in
    let json_str = "[" ^ inner ^ "]" in
    match Yojson.Safe.from_string json_str with
    | `List [a1; a2] ->
        (nfa_of_yojson a1, nfa_of_yojson a2)
    | _ ->
        failwith "Formato invalido"

let is_dfa (states, alphabet, transitions, initials, finals) =
  let one_initial = match initials with [_] -> true | _ -> false in
  let has_epsilon = List.exists (fun ((_, symbol), _) -> symbol = None) transitions in
  let states_ok =
    let in_states q = List.mem q states in
    let trans_states_ok = List.for_all (fun ((q, _), q') -> in_states q && in_states q') transitions in
    let initials_ok = List.for_all in_states initials in
    let finals_ok = List.for_all in_states finals in
    trans_states_ok && initials_ok && finals_ok
  in
  let alphabet_ok =
    List.for_all
      (fun ((_, symbol), _) -> match symbol with None -> false | Some c -> List.mem c alphabet)
      transitions
  in
  let rec check_deterministic trans =
    match trans with
    | [] -> true
    | ((q, sym), _) :: rest ->
        if List.exists (fun ((q2, sym2), _) -> q = q2 && sym = sym2) rest then false
        else check_deterministic rest
  in
  one_initial && (not has_epsilon) && states_ok && alphabet_ok && check_deterministic transitions

let normalize nfa alpha_req =
  let (states, _, trans, ini, fin) = nfa in
  let max_state = match states with [] -> 0 | _ -> List.fold_left max min_int states in
  let dead_state = max_state + 1 in
  
  let missing_transitions =
    List.concat_map (fun s ->
      List.filter_map (fun a ->
        if List.exists (fun ((origin, symbol), _) -> origin = s && symbol = Some a) trans then
          None
        else
          Some ((s, Some a), dead_state)
      ) alpha_req
    ) states
  in
  
  if missing_transitions = [] then
    (states, alpha_req, trans, ini, fin)
  else
    let dead_transitions = List.map (fun a -> ((dead_state, Some a), dead_state)) alpha_req in
    let new_states = dead_state :: states in
    let new_trans = trans @ missing_transitions @ dead_transitions in
    (List.sort_uniq compare new_states, alpha_req, List.sort_uniq compare new_trans, ini, fin)

let product_bfs nfa1 nfa2 is_final_pred =
  let (_, alpha1, _, _, _) = nfa1 in
  let (_, alpha2, _, _, _) = nfa2 in
  let common_alpha = List.sort_uniq compare (alpha1 @ alpha2) in
  
  let (st1, _, tr1, ini1, fin1) = normalize nfa1 common_alpha in
  let (st2, _, tr2, ini2, fin2) = normalize nfa2 common_alpha in
  
  let get_dest transitions s a =
    match List.find_opt (fun ((orig, sym), _) -> orig = s && sym = Some a) transitions with
    | Some (_, dest) -> dest
    | None -> -1 
  in

  let start_pairs = 
    List.concat_map (fun i1 -> List.map (fun i2 -> (i1, i2)) ini2) ini1 
  in

  let queue = Queue.create () in
  List.iter (fun p -> Queue.add p queue) start_pairs;
  
  let visited = Hashtbl.create 100 in
  List.iter (fun p -> Hashtbl.add visited p true) start_pairs;
  
  let final_states = ref [] in

  while not (Queue.is_empty queue) do
    let (curr1, curr2) = Queue.take queue in
    
    if is_final_pred (List.mem curr1 fin1) (List.mem curr2 fin2) then
      final_states := (curr1, curr2) :: !final_states;

    List.iter (fun char ->
      let next1 = get_dest tr1 curr1 char in
      let next2 = get_dest tr2 curr2 char in
      
      if next1 <> -1 && next2 <> -1 then (
        let next_pair = (next1, next2) in
        if not (Hashtbl.mem visited next_pair) then (
          Hashtbl.add visited next_pair true;
          Queue.add next_pair queue
        )
      )
    ) common_alpha
  done;

  !final_states

let eqdfa nfa1 nfa2 = 
  let (_, alpha1, _, _, _) = nfa1 in
  let (_, alpha2, _, _, _) = nfa2 in 
  let common_alpha = List.sort_uniq compare (alpha1 @ alpha2) in
  
  let norm1 = normalize nfa1 common_alpha in
  let norm2 = normalize nfa2 common_alpha in 
  
  let comp1 = normalize nfa1 common_alpha in 
  let (s1, a1, t1, i1, f1) = comp1 in
  let c_nfa1 = (s1, a1, t1, i1, List.filter (fun s -> not (List.mem s f1)) s1) in

  let comp2 = normalize nfa2 common_alpha in
  let (s2, a2, t2, i2, f2) = comp2 in
  let c_nfa2 = (s2, a2, t2, i2, List.filter (fun s -> not (List.mem s f2)) s2) in

  let finals_diff1 = product_bfs norm1 c_nfa2 (fun f1 f2 -> f1 && f2) in
  let finals_diff2 = product_bfs c_nfa1 norm2 (fun f1 f2 -> f1 && f2) in
  
  (finals_diff1 = []) && (finals_diff2 = [])

let _ =
  let s = read_multiplelines () |> String.trim in
  try
    let (nfa1, nfa2) = nfa_de_string_2 s in
    
    if not (is_dfa nfa1 && is_dfa nfa2) then (
      print_endline "INVALID";
      exit 0
    );

    if eqdfa nfa1 nfa2 then 
      print_endline "TRUE"
    else
      print_endline "FALSE"
      
  with _ ->
    print_endline "INVALID"