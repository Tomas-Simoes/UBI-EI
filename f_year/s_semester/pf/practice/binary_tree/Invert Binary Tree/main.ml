type 'a tree = Empty | Node of 'a * 'a tree * 'a tree 

let rec print_tree node depth =
  match node with
  | Empty -> ()
  | Node (value, left, right) ->
      print_string (String.make (depth * 2) ' ');
      print_endline (string_of_int value);
      print_tree left (depth + 1);
      print_tree right (depth + 1)

let example_tree =
  Node (1,
        Node (2,
              Node (4, Empty, Empty),
              Node (5, Empty, Empty)),
        Node (3,
              Node (6, Empty, Empty),
              Node (7, Empty, Empty)))

let invert_binary tree = (
  match tree with
  | Empty -> tree
  | Node (v, l, r) -> 
    Node (v, r, l)
);;

print_tree (invert_binary example_tree) 0
      