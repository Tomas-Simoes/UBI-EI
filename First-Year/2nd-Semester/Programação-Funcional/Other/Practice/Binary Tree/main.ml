(* Definição do tipo de árvore binária *)
type 'a binary_tree =
  | Empty                                  (* Nó vazio *)
  | Node of 'a * 'a binary_tree * 'a binary_tree  (* Nó com valor e subárvores *)

(* Função para criar um nó folha *)
let leaf value = Node (value, Empty, Empty)

(* Função para inserir um elemento na árvore binária *)
let rec insert tree value =
  match tree with
  | Empty -> leaf value    (* Se a árvore estiver vazia, insira o valor como uma folha *)
  | Node (v, left, right) ->
      if value < v then     (* Se o valor for menor que o valor do nó atual, insira à esquerda *)
        Node (v, insert left value, right)
      else if value > v then (* Se o valor for maior, insira à direita *)
        Node (v, left, insert right value)
      else                  (* Se o valor já existir na árvore, não faça nada *)
        tree

(* Função para verificar se um elemento está presente na árvore *)
let rec member tree value =
  match tree with
  | Empty -> false         (* Se a árvore estiver vazia, o elemento não está presente *)
  | Node (v, left, right) ->
      if value = v then     (* Se o valor for igual ao valor do nó atual, está presente *)
        true
      else if value < v then (* Se o valor for menor, procure na subárvore esquerda *)
        member left value
      else                   (* Se o valor for maior, procure na subárvore direita *)
        member right value

(* Exemplo de utilização *)
let tree =
  let open Random in
  let rec build n acc =
    if n = 0 then acc
    else build (n - 1) (insert acc (int 100))
  in
  build 10 Empty

let () =
  Printf.printf "Árvore binária: %b\n" (member tree 42)