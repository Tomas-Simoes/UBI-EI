let processa list = (
  let rec getTuples list sum =
    match list with
    | [] -> [];
    | h::t ->
      [(h, h+sum)] @ getTuples t (h+sum)
    in getTuples list 0
);;

let rec combina tuples_list = (
  match tuples_list with
  | [] -> ([],[])
  | (f, s)::t ->
    let odd_numbers, even_numbers = 
      combina t
    in
      let new_odd, new_even = 
        if f mod 2 <> 0 then (f::odd_numbers, even_numbers)
        else (odd_numbers, f::even_numbers);
      in
        if s mod 2 <> 0 then ((s::new_odd, new_even))
        else (new_odd, s::new_even)
      
);;

(*da para listas pares como para impares*)
let divide list = (
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
  ) in divide_tuple list (List.rev list)
);;

type 'a tree = E | N of 'a tree * 'a * 'a tree;;

let rec same_shape tree1 tree2 = (
      match (tree1, tree2) with
      | E, E -> true 
      | N(l, v, r), N(l', v', r') -> 
          same_shape l l' && same_shape r r'
      | _ -> false
);;

let rec map f t = (
  match t with
  | E -> E
  | N(l, v, r) ->
    N(map f l, (f v), map f r)
);;


