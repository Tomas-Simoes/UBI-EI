let sortArray array = (
  let sortedArray = Array.sort (fun a b -> compare b a) in sortedArray
);;

let rec oddEvenSortList list = (
  let oddFirst = (match list with
      | [] -> []
      | h::t -> 
        if h mod 2 <> 0 then 
          [h] @ oddEvenSortList t 
        else
          oddEvenSortList t @ [h])   
  in 
  List.stable_sort (
    fun a b -> 
      if a mod 2 <> 0 && b mod 2 <> 0 then
        compare b a
      else if a mod 2 = 0 && b mod 2 = 0 then 
        compare a b 
      else
        compare a a 
  ) oddFirst
);;

let rec oddEvenSortArray array = (
  let oddFirst = [||] in 
  Array.iter (
    fun a -> 
      if a mod 2 = 0 then oddFirst = Array.concat oddFirst [a]
      else Array.append [a] oddFirst;
  ) array
);;

List.iter (fun a -> print_int a; print_string " ") (oddEvenSortList [1;5;2;4;6;1;7])
