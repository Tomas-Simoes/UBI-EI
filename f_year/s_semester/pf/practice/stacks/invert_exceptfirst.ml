let is_empty s = 
  s = []

let pop s =
  match s with
  | [] -> failwith "stack empty"
  | h::t -> (h,t)

let peek s =
    match s with
    | [] -> failwith "stack empty"
    | h::_ -> h

let push n s = n :: s

let rec equality_aux stack1 stack2 written_stack1 written_stack2 = 
  if is_empty stack1 && is_empty stack2 then 
    let rec isequal stack1 stack2 =
      if List.length stack1 != List.length stack2 then false
      else if is_empty stack1 && is_empty stack2 then true
      else 
        let h_stack1, t_stack1 = pop stack1 in 
          let h_stack2, t_stack2 = pop stack2 in 
            if h_stack1 = h_stack2 then isequal t_stack1 t_stack2
            else false
    in
    isequal written_stack1 written_stack2
  else
  let h_stack1, t_stack1 = pop stack1 in 
    let h_stack2, t_stack2 = pop stack2 in 
      if h_stack1 = h_stack2 && (h_stack1 <> "#" && h_stack2 <> "#") then 
        equality_aux t_stack1 t_stack2 (push h_stack1 written_stack1) (push h_stack2 written_stack2)
      else
        if h_stack1 = "#" && h_stack2 = "#" then 
            equality_aux t_stack1 t_stack2 (List.tl written_stack1) (List.tl written_stack1)
        else if h_stack1 = "#" then 
            equality_aux t_stack1 (peek written_stack2 :: stack2) (List.tl written_stack1) (List.tl written_stack2)
        else if h_stack2 = "#" then 
            equality_aux (peek written_stack1 :: stack1) t_stack2 (List.tl written_stack1) (List.tl written_stack2)
        else if not (is_empty t_stack1) && not (is_empty t_stack2) then
            equality_aux t_stack1 t_stack2 (h_stack1 :: written_stack1) (h_stack2 :: written_stack2)
        else 
          false;;

string_of_bool (equality_aux  ["a";"b";"#";"c"] ["a";"d";"e";"c"] [] []);; 