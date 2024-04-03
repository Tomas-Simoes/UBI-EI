let rec sum n = 
  if n = 0 then 4
  else 2 * (2 - n) + sum (n - 1);;

let rec sum_term n acc = 
  if n = 0 then acc
  else sum_term (n-1) (acc + 2 * (2 - n));;

let () = Printf.printf("\nsum: %d") (sum 8)
let () = Printf.printf("\nsum_term: %d\n") (sum_term 8 4)