let rec halve list lenght = (
  match list with
  | [] -> [], [] 
  | h::t ->
    let firstHalf, secondHalf = halve t lenght in 
    if List.length list > int_of_float(ceil (lenght /. 2.)) then
      h :: firstHalf, secondHalf
    else 
      firstHalf, h :: secondHalf
);;

let list = [1; 2];;
halve list (float_of_int(List.length list));;

