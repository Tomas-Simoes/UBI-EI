let is_empty s = 
  s = []

let push n stack = n :: stack

let pop = function
| [] -> failwith "asd"
| h :: t -> (h,t)


let rec remove_adj_pair list stack =
  if is_empty list then List.rev stack
  else
    let h_list, t_list = pop list in
      if is_empty stack then 
        let new_stack = push h_list stack in
            remove_adj_pair t_list new_stack
      else
        let h_stack, t_stack = pop stack in 
        if h_list = h_stack then 
          remove_adj_pair t_list t_stack
        else
          let new_stack = push h_list stack in
            remove_adj_pair t_list new_stack;;

List.iter (fun x -> print_int x) (remove_adj_pair [1;2;2;1;4;6] []);;