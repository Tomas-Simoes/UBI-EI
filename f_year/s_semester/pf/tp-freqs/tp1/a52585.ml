let rec sum i = 
  if i = 0 then 4
  else 2 * (2 - i) + sum (i - 1);;

let rec sum_term i acc = 
  if i = 0 then acc
  else sum_term (i-1) (acc + 2 * (2 - i));;

let () = Printf.printf("\nsum: %d") (sum 8)
let () = Printf.printf("\nsum_term: %d\n") (sum_term 8 4)