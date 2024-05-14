type 'a tree = Leaf | Node of 'a * 'a tree * 'a tree

let rec print_tree node depth =
  match node with
  | Leaf -> ()
  | Node (value, left, right) ->
      print_string (String.make (depth * 2) ' ');
      print_endline (string_of_int value);
      print_tree left (depth + 1);
      print_tree right (depth + 1)
      
let create_binary list = (
  let rec input_number tree n =
    match tree with
    | Leaf -> Node(n, Leaf, Leaf)
    | Node (v, l, r) -> 
      if n < v then Node(v, input_number l n, r)
      else if n > v then Node(v, l, input_number r n)
      else tree
    in 
      List.fold_left (fun acc a -> input_number acc a) Leaf list
);;

let rec create_list binary acc= (
  let vertice, left, right = 
    match binary with 
      | Leaf -> -1, Leaf, Leaf
      | Node (v, l, r) -> v, l, r
    in 
      if vertice <> -1 then 
        create_list right (create_list left (acc @ [vertice]))
      else
        acc 
)
          
let example_list = [7; 10; 1; 3; 2; 5];;

let example_tree =
  Node (1,
        Node (2,
              Node (4, Leaf, Leaf),
              Node (5, Leaf, Leaf)),
        Node (3,
              Node (6, Leaf, Leaf),
              Node (7, Leaf, Leaf)));;


(* print_tree (create_binary example_list) 0;; *)
print_tree example_tree 0;;
List.iter (fun x -> print_int x; print_string ", ") (create_list example_tree [])