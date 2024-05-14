type 'a tree = Leaf | Node of 'a * 'a tree * 'a tree

let rec print_tree node depth =
  match node with
  | Leaf -> ()
  | Node (value, left, right) ->
      print_string (String.make (depth * 2) ' ');
      print_endline (string_of_int value);
      print_tree left (depth + 1);
      print_tree right (depth + 1)
      
let example_tree1 =
  Node (1,
        Node (2,
              Node (4, Leaf, Leaf),
              Node (5, Leaf, Leaf)),
        Node (3,
              Node (6, Leaf, Leaf),
              Node (7, Leaf, Leaf)));;

let example_tree2 =
  Node (1,
        Node (2,
              Node (4, Leaf, Leaf),
              Node (5, Leaf, Leaf)),
        Node (7,
              Node (6, Leaf, Leaf),
              Node (8, Leaf, Leaf)));;

let rec difere_tree tree1 tree2 = (
  let root, l, r = 
    match tree1 with 
    | Leaf -> -1, Leaf, Leaf
    | Node (root, l, r) -> root, l, r
  in 
    match tree2 with
    | Leaf -> -1
    | Node (root', l', r') -> 
      if root <> root' then 
        root
      else
        let diffLeft = difere_tree l l' in
          if diffLeft <> -1 then root
          else 
            difere_tree r r'
);;

let rec differenceTree binary_tree1 binary_tree2 = (
  match (binary_tree1, binary_tree2) with
  | Leaf, Leaf -> -1 
  | Leaf, _ -> failwith "A primeira árvore é vazia."
  | _, Leaf -> failwith "A segunda árvore é vazia."
  | Node(root, left, right), Node(root2, left2, right2) -> 
    if root <> root2 then 
      root
    else  
      let diffLeft = differenceTree left left2 in
      if diffLeft <> -1 then
        diffLeft
      else 
        differenceTree right right2 
        );;

print_int (difere_tree example_tree1 example_tree2)
