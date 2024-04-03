let rec sum n =
  if n = 0 then 2 
  else 2 * (n + 1) + sum (n-1)

let rec sum_term n acc = 
  if n = 0 then acc
  else sum_term (n-1) (2 * (n + 1) + acc);;

  

  