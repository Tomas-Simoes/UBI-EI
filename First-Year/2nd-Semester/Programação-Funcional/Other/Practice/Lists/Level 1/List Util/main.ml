let list = [1; 2; 3; 4; 7; 10];;
let list_string = ["a"; "g"; "W"; "R"; "y"];;


(* UTIL Functions *)
let rec print_stringlist list = (   
  match list with
    [] -> ()
  | h::t -> print_string h; print_string " "; print_stringlist t 
);;

let isOdd num = 
  if num mod 2 == 0 then 
    true
  else 
    false

(* Main Function*)
let rec sum list = (
  match list with
  | [] -> 0
  | head :: tail -> head + sum tail
)

let rec count_odd list = (
  match list with
  | [] -> 0
  | head :: tail -> 
    if isOdd head then 1 + count_odd tail 
    else 0 + count_odd tail
);;

let rec revert list = (
  match list with
    | [] -> []
    | head::tail -> revert tail @ [head]
);;

let rec pallidroma list = (
  match list with
  | [] | [_] -> true
  | _ -> list = revert list
);;

let rec all_uppercase list = (
  match list with
  | [] -> []
  | head :: tail -> [String.uppercase_ascii head] @ all_uppercase tail
);;

let rec isSorted list order = (
  match list with
    | [] | [_] -> 0
    | h::h'::t -> order h' h + isSorted t order 
);;

let rec remove_duplicate list = (
  match list with
  | [] -> []
  | h :: [] -> [h]
  | h::h'::t -> 
    if h <> h' then 
      h :: remove_duplicate (h' :: t) 
    else
      remove_duplicate (h' :: t) 
);;



Printf.printf "List sum: %d\n" (sum list);
Printf.printf "Number of odd elements: %d\n" (count_odd list);;
Printf.printf "Is a pallidroma? %b\n" (pallidroma [1; 2; 3; 2; 1;]);;
Printf.printf "All uppercase: "; print_stringlist (all_uppercase list_string);;
Printf.printf "\nIs sorted? %b\n"  (if isSorted list compare > 0 then true else false);;
Printf.printf "Remove all duplicates from [1;1;1;2;2;3;5;9;9;10;10;10]: ";; List.iter (fun x -> print_int x; print_string " ") (remove_duplicate [1;1;1;2;2;3;5;9;9;10;10;10]);; 
Printf.printf "\n";;