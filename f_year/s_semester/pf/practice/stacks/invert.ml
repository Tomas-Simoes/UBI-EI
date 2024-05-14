let is_empty s = 
  s = []

let push n stack = n :: stack

let pop = function
| [] -> failwith "asd"
| h :: t -> (h,t)

let rec invertList list stack =
  if is_empty list then stack
  else 
    let h_list, t_list = pop list in 
      let new_stack = push h_list stack in 
        invertList t_list new_stack;;

List.iter (fun x -> print_int x) (invertList [1;2;2;1;4;6] []);;