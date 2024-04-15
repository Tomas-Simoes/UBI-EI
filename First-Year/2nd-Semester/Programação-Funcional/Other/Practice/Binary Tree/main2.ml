type 'a binary_tree =
  | Empty                                  
  | Node of 'a * 'a binary_tree * 'a binary_tree  

  let rec print_tree_in_order tree = (
    match tree with
    | Empty -> ()
    | Node (v, left, right) ->
        print_string "Binary tree: \n";
        print_tree_in_order left;
        print_int v;   (* Output the value of the current node *)
        print_string " ";
        print_tree_in_order right;
        print_string "\n";
  );;

let rec create_binary tree list = (
  let h, h', t = (
    match list with
    | [] -> 0, 0,[]
    | h::[] -> h, -1, []
    | h::h'::t -> h, h', t
  ) in
    print_tree_in_order tree;
    match tree with
    |Empty -> 
      print_string "Empty tree\n";
      create_binary (Node(h', Empty, Empty)) (h::t); 
    |Node(v, l, r) -> 
      print_string "Tree with node\n";
      print_int h; print_string " / "; print_int v; print_string "\n";
      if h < v then 
        Node (v, create_binary l (v::list), r)
      else if h > v then 
        Node(v, l, create_binary r (v::list))
      else
        tree
);; 

let tree = create_binary Empty [7; 2; 9; 1; 5]
in
  print_tree_in_order tree;
  print_newline()