let is_empty s = 
  s = []

let pop s =
  match s with
  | [] -> failwith "Stack is empty"
  | h::t -> (h, t)

let peek s =
  match s with
  | [] -> failwith "stack empty"
  | h::_ -> h

let push n s = n :: s 

let rec stack_equality_wo_backspace stack1 stack2 =
  if List.length stack1 != List.length stack2 then true
  else if is_empty stack1 && is_empty stack2 then false
  else 
    let h_stack1, t_stack1 = pop stack1 in 
      let h_stack2, t_stack2 = pop stack2 in 
        if h_stack1 = h_stack2 then stack_equality_wo_backspace t_stack1 t_stack2
        else true;;

let rec stack_equality stack1 stack2 written_stack1 written_stack2 = 
  if is_empty stack1 && is_empty stack2 then 
      stack_equality_wo_backspace written_stack1 written_stack2
  else
  let h_stack1, t_stack1 = pop stack1 in 
    let h_stack2, t_stack2 = pop stack2 in
      let () =
        Printf.printf "written stack1->"; 
        List.iter (fun x -> print_string x; print_string "\n") written_stack1;
        Printf.printf "written stack2->"; 
        List.iter (fun x -> print_string x; print_string "'\n") written_stack2; 
      in
      if h_stack1 = h_stack2 && (h_stack1 <> "&" && h_stack2 <> "&") then 
        stack_equality t_stack1 t_stack2 (push h_stack1 written_stack1) (push h_stack2 written_stack2)
      else
        if h_stack1 = "#" && h_stack2 = "#" then 
          stack_equality t_stack1 t_stack2 (List.tl written_stack1) (List.tl written_stack2)
        else if h_stack1 = "#" then 
          stack_equality t_stack1 (List.tl stack2) (List.tl written_stack1) (List.tl written_stack2)
        else if h_stack2 = "#" then 
          stack_equality (List.tl stack1) t_stack2 (List.tl written_stack1) (List.tl written_stack2)
        else if not (is_empty t_stack1) && not (is_empty t_stack2) then
          stack_equality t_stack1 t_stack2 (h_stack1 :: written_stack1) (h_stack2 :: written_stack2)
        else 
          let () = 
            List.iter (fun x -> print_string x) written_stack1;
            List.iter (fun x -> print_string x) written_stack2;
          in
          stack_equality_wo_backspace written_stack1 written_stack2;;

string_of_bool (stack_equality_wo_backspace ['a';'b';'#';'c'] ['a';'d';'#';'c']);;
string_of_bool (stack_equality  ["a";"b";"#";"c"] ["a";"d";"#";"c"] [] []);; 