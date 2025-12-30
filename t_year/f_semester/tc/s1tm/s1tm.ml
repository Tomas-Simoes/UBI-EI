type estado = string [@@deriving yaml]

type simbolo = string

let simbolo_to_yaml s = `String s

let simbolo_of_yaml = function
  | `String s -> Ok s
  | `Float f -> Ok (string_of_int (int_of_float f))
  | `Bool b -> Ok (if b then "y" else "n")
  | v -> Error (`Msg ("Invalid simbolo in YAML: " ^ Yaml.to_string_exn v))

type direction = L | R | S

let direction_to_yaml = function
  | L -> `String "L"
  | R -> `String "R"
  | S -> `String "S"

let direction_of_yaml = function
  | `String "L" -> Ok L
  | `String "R" -> Ok R
  | `String "S" -> Ok S
  | v -> Error (`Msg ("Invalid direction in YAML: " ^ Yaml.to_string_exn v))

type transition = estado * simbolo * direction [@@deriving yaml]

type delta = (string, (string, transition) Hashtbl.t) Hashtbl.t

let delta_to_yaml delta =
  `O
    (Hashtbl.fold
       (fun key inner acc ->
         let inner_lst =
           Hashtbl.fold
             (fun k v acc2 -> (k, transition_to_yaml v) :: acc2)
             inner []
         in
         (key, `O inner_lst) :: acc )
       delta [] )

let delta_of_yaml = function
  | `O lst ->
      let outer_tbl = Hashtbl.create (List.length lst) in
      List.iter
        (fun (key, value) ->
          match value with
          | `O inner_lst ->
              let inner_tbl = Hashtbl.create (List.length inner_lst) in
              List.iter
                (fun (k, v) ->
                  let transition =
                    match transition_of_yaml v with
                    | Ok t -> t
                    | Error (`Msg m) -> failwith m
                  in
                  Hashtbl.add inner_tbl k transition )
                inner_lst ;
              Hashtbl.add outer_tbl key inner_tbl
          | v ->
              failwith ("Invalid inner delta YAML: " ^ Yaml.to_string_exn v) )
        lst ;
      Ok outer_tbl
  | v -> failwith ("Invalid delta YAML: " ^ Yaml.to_string_exn v)

type tm =
  { states: estado list
  ; input_alphabet: simbolo list
  ; tape_alphabet_extra: simbolo list
  ; start_state: estado
  ; accept_state: estado
  ; reject_state: estado
  ; delta: delta }
[@@deriving yaml]

type tm_w = {m: tm [@key "M"]; w: string} [@@deriving yaml]

let rec read_multiplelines () =
  try
    let line = read_line () in
    line ^ "\n" ^ read_multiplelines ()
  with End_of_file -> ""

let yaml_val = function
  | Ok v -> v 
  | Error (`Msg m) -> failwith m

let tm_w_de_string s = s |> Yaml.of_string_exn |> tm_w_of_yaml |> yaml_val

let tm_w_para_string tm_w = tm_w |> tm_w_to_yaml |> Yaml.to_string_exn

let verbose = true 

let enable f = if verbose then f () else ()

let debug_print fmt =
  Printf.ksprintf (fun s -> enable (fun () -> print_endline s)) fmt

let update_tape tape index new_symbol = 
  if index >= String.length tape then 
    tape ^ (String.make (index - String.length tape) '_' ^ String.make 1 new_symbol)
  else 
    let tape' = Bytes.of_string tape in 
    Bytes.set tape' index new_symbol;
    Bytes.to_string tape'

let validate_input tm w =
  let input_set = List.fold_left (fun acc s -> acc || s = "") false tm.input_alphabet in
  if input_set then true 
  else
    let rec check_chars i =
      if i >= String.length w then true
      else
        let c = String.make 1 w.[i] in
        if List.mem c tm.input_alphabet then check_chars (i + 1)
        else false
    in
    String.length w = 0 || check_chars 0

let rec check_tape tm tape t_index cur_state steps max_steps =
  if cur_state = tm.accept_state then Some (true, tape)
  else if cur_state = tm.reject_state then Some (false, tape)
  
  else if steps >= max_steps then (
    debug_print "Reached maximum steps (%d) - DON'T KNOW" max_steps;
    None
  )
  else if t_index < 0 then (
    debug_print "Head moved left of index 0 - REJECT";
    Some (false, tape)
  ) 
  else
    let cur_char = if t_index >= String.length tape then '_' else tape.[t_index] in
    let cur_char_str = String.make 1 cur_char in
    
    match Hashtbl.find_opt tm.delta cur_state with 
    | None ->
        debug_print "No transitions found for state '%s'" cur_state;
        Some (false, tape) 
    | Some transitions ->
        match Hashtbl.find_opt transitions cur_char_str with 
        | None -> 
            debug_print "No transition for symbol '%s' in state '%s' - REJECT" cur_char_str cur_state;
            Some (false, tape)
        | Some (new_state, new_symbol, direction) ->
            let new_tape = update_tape tape t_index new_symbol.[0] in 
            
            let new_t_index = match direction with 
              | L -> if t_index = 0 then 0 else t_index - 1 
              | R -> t_index + 1 
              | S -> t_index 
            in 
            
            debug_print "State: %s | Read: %s | Write: %s | Move: %s | New Tape: %s" 
                        cur_state cur_char_str new_symbol (match direction with L->"L"|R->"R"|S->"S") new_tape;

            if new_state = tm.accept_state then Some (true, new_tape) 
            else if new_state = tm.reject_state then Some (false, new_tape)
            else check_tape tm new_tape new_t_index new_state (steps + 1) max_steps

let () =  
  let _ = read_multiplelines in 
  let _ = tm_w_de_string in 
  let _ = tm_w_para_string in 
  
  let s = read_multiplelines () |> String.trim in
  let tm_w_obj = match s |> Yaml.of_string_exn |> tm_w_of_yaml with
    | Ok v -> v | Error (`Msg m) -> failwith m in
  
  if not (validate_input tm_w_obj.m tm_w_obj.w) then
    print_endline "INVALID"
  else
    match check_tape tm_w_obj.m tm_w_obj.w 0 tm_w_obj.m.start_state 0 200 with
    | Some (true, final_tape) ->
        print_endline "YES";
        let output_tape = 
          if String.length final_tape > 0 && final_tape.[String.length final_tape - 1] = '_' 
          then final_tape 
          else final_tape ^ "_" 
        in
        Printf.printf "%s\n" output_tape
    | Some (false, final_tape) ->
        print_endline "NO";
        let output_tape = 
          if String.length final_tape > 0 && final_tape.[String.length final_tape - 1] = '_' 
          then final_tape 
          else final_tape ^ "_" 
        in
        Printf.printf "%s\n" output_tape
    | None -> print_endline "DON'T KNOW"