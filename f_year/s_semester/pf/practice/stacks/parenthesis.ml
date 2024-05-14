let is_empty s = 
  s = []

let push n stack = n :: stack

let pop = function
| [] -> failwith "erro"
| h :: t -> (h,t)

let rec parenthesis stack = 
  if is_empty stack then true 
  else 
    let h_stack, t_stack = pop stack in 
      let h'_stack, t'_stack = pop t_stack in 
        if h_stack='(' && h'_stack = ')' || h_stack='[' && h'_stack = ']'
        then parenthesis t'_stack
        else false;;

string_of_bool (parenthesis ['(';')';'[';']']);;

let rec processa stack =
  if is_empty stack then
    true
  else
    let h_stack, t_stack = pop stack in
      let h'_stack, t'_stack = pop t_stack in
        match h_stack with
        | '(' ->
          if h'_stack = ')' then
            processa t'_stack
          else
            false
        | '[' ->
          if h'_stack = ']' then
            processa t'_stack
          else
            false
        | _ -> false