open Ppx_yojson_conv_lib.Yojson_conv.Primitives

type state = int [@@deriving yojson]
type symbol = char option [@@deriving yojson]
type transition = (state * symbol) * state [@@deriving yojson]

type nfa =
  state list * symbol list * transition list * state list * state list
[@@deriving yojson]

let rec read_multiple_lines () =
  try
    let line = read_line () in
    line ^ " " ^ read_multiple_lines ()
  with End_of_file -> ""

let nfa_from_string s = s |> Yojson.Safe.from_string |> nfa_of_yojson
let nfa_to_string nfa = yojson_of_nfa nfa |> Yojson.Safe.to_string

let sort_nfa nfa =
  let (states, alphabet, transitions, initials, finals) = nfa in
  let sorted_states = List.sort_uniq compare states in
  let sorted_alphabet = List.sort_uniq compare alphabet in
  let sorted_transitions = List.sort_uniq compare transitions in
  let sorted_initials = List.sort_uniq compare initials in
  let sorted_finals = List.sort_uniq compare finals in
  (sorted_states, sorted_alphabet, sorted_transitions, sorted_initials, sorted_finals)

let reverse nfa =
  let (states, alphabet, transitions, initials, finals) = nfa in
  let reversed_transitions =
    List.map (fun ((origin, symbol), dest) -> ((dest, symbol), origin)) transitions
  in
  (states, alphabet, reversed_transitions, finals, initials)

let rec unify_aux transitions initials new_initial =
  match transitions with
  | [] -> []
  | ((origin, symbol), dest) :: tail ->
    if List.mem origin initials then
      ((new_initial, symbol), dest) :: ((origin, symbol), dest) :: unify_aux tail initials new_initial
    else
      ((origin, symbol), dest) :: unify_aux tail initials new_initial

let unify nfa =
  let (states, alphabet, transitions, initials, finals) = sort_nfa nfa in
  let new_initial = if states <> [] then List.hd (List.rev states) + 1 else 0 in 
  let new_states = states @ [new_initial] in 
  let new_transitions = unify_aux transitions initials new_initial in
  let new_finals =
    if List.exists (fun i -> List.mem i finals) initials then
      finals @ [new_initial]
    else
      finals
  in
  (new_states, alphabet, new_transitions, [new_initial], new_finals)

let rec destinations_from_state states transitions alphabet =
  match alphabet with
  | [] -> []
  | ref_symbol :: tail ->
    let dests =
      List.fold_left (fun acc ((origin, symbol), dest) ->
        if List.mem origin states && symbol = ref_symbol then dest :: acc else acc
      ) [] transitions
    in
    if dests <> [] then 
    ((states, ref_symbol), List.sort compare dests) :: destinations_from_state states transitions tail
    else
    destinations_from_state states transitions tail

let rec update_destination_mapping dest cur_map acc_map =
  match acc_map with
  | [] ->
    if cur_map <> [] then
      let (last_index, _) = List.hd (List.rev cur_map) in
      (last_index + 1, cur_map @ [(last_index + 1, dest)])
    else
      (0, [(0, dest)])
  | (index, mapped_dest) :: rest_map ->
    if dest = mapped_dest then (index, cur_map)
    else update_destination_mapping dest cur_map rest_map

let rec process_new_transitions new_transitions mapped_new_transitions cur_map origin_index =
  match new_transitions with
  | [] -> 
      (mapped_new_transitions, cur_map)
  | ((_, symbol), dest) :: tail_transitions ->
      let (dest_index, new_map) = update_destination_mapping dest cur_map cur_map in

      process_new_transitions tail_transitions
        (mapped_new_transitions @ [((origin_index, symbol), dest_index)])
        new_map
        origin_index

let rec get_all_transitions state_index_queue processed_states states_mapping transitions alphabet =
  match state_index_queue with
  | [] -> 
    ([], processed_states, states_mapping)
  | cur_state_index :: tail_index_queue ->
    let ( _, cur_states ) = List.find (fun (index, _) -> index = cur_state_index) states_mapping in
    let new_transitions = destinations_from_state cur_states transitions alphabet in
    let (new_mapped_transitions, new_states_map) =
      process_new_transitions new_transitions [] states_mapping cur_state_index
    in
    let new_states =
      List.fold_left (fun acc ((_, _), dest) ->
        if List.mem dest processed_states || List.mem dest tail_index_queue || dest = cur_state_index then acc else acc @ [dest]
      ) [] new_mapped_transitions
    in
    let (acc_transitions, final_processed, final_map) =
      get_all_transitions (tail_index_queue @ new_states) (processed_states @ [cur_state_index])
        new_states_map transitions alphabet
    in
    (new_mapped_transitions @ acc_transitions, final_processed, final_map)
    
let convert nfa =
  let (_, alphabet, transitions, initials, finals) = nfa in
  let initial_states = List.sort_uniq compare initials in
  let initial_map = [(1, initial_states)] in
  let initial_queue = [1] in

  let (final_transitions, _, final_map) =
    get_all_transitions initial_queue [] initial_map transitions alphabet
  in

  let new_states_list = List.sort_uniq compare (List.map fst final_map) in
  
  let new_finals =
    List.fold_left (fun acc (mapped_state, original_states_set) ->
      if List.exists (fun s -> List.mem s finals) original_states_set then
        mapped_state :: acc
      else
        acc
    ) [] final_map
  in
  let new_initials =
    List.fold_left (fun acc (mapped_state, original_states_set) ->
      if List.exists (fun s -> List.mem s initials) original_states_set then
        mapped_state :: acc
      else
        acc
    ) [] final_map
  in

  ((new_states_list, alphabet, final_transitions, (List.sort_uniq compare new_initials), (List.sort_uniq compare new_finals)), final_map)

let _ =
  let s = read_multiple_lines () |> String.trim in
  let nfa = nfa_from_string s in
  
  let(_,_,transitions,_,_) = nfa in 
  let epsilon = List.exists(fun (((_,symbol),_)) -> symbol=None) transitions in

  if epsilon then (
    print_endline "EPSILON";
    exit 0;
  );


  let nfa_reversed = reverse nfa in

  let nfa_unified = unify nfa_reversed in

  let (nfa_converted, _) = convert nfa_unified in

  let nfa_reversed_again = reverse nfa_converted in

  let nfa_unified_again = unify nfa_reversed_again in

  let (nfa_converted_again, _) = convert nfa_unified_again in
  print_endline (nfa_to_string (sort_nfa nfa_converted_again))