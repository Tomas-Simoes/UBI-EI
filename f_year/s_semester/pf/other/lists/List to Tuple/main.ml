let rec print_list_of_tuples lst =(
  match lst with
  | [] -> ()  (* Caso base: lista vazia, não há nada para imprimir *)
  | (x, y)::rest ->
      (* Imprime o primeiro elemento da tupla *)
      print_string "(";
      print_int x;
      print_string ", ";
      print_int y;
      print_string ") ";
      (* Chamada recursiva para imprimir o restante da lista *)
      print_list_of_tuples rest
);;

let rec convert_tuple list = (
  match list with 
  | []  -> []
  | h::[] -> [(h, h)]
  | h::h'::t -> 
    let newArr = [(h, h')] @ convert_tuple t in newArr; 
);;

let rec divide_tuple list rev_list = (
  let h, t = (
    match list with
    | [] -> -1, []
    | h::t -> h, t
  ) in
    match rev_list with
      | [] -> []
      | h'::t' -> 
      if List.length t' <> 0 then
        let newList = (
        [(h, h')] @ divide_tuple (List.rev (List.tl (List.rev(t)))) (List.rev (List.tl (List.rev(t'))))) in 
        newList;
      else 
        [(h,h)]
);;

let list = [1; 2; 3; 4] in
  (* print_list_of_tuples (convert_tuple list); *)
  print_list_of_tuples (divide_tuple list (List.rev list))

