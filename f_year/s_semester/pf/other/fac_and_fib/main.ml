let user_n = read_int();;

let rec fac n = 
  if n = 1 then 1
  else n * fac (n-1)

let rec fac_term n acc = 
  if n = 1 then acc
  else fac_term (n-1) (n * acc)

let rec fib n = 
  if n <= 2 then 1
  else fib (n-1) + fib (n-2)

let () = Printf.printf ("Factorial: %d\n") (fac 3)
let () = Printf.printf ("Factorial Terminal: %d\n") (fac_term 3 1)

let () = Printf.printf ("Fibonacci: %d\n") (fib 7)
