let user_n = read_int();;

let rec sum n i = 
  if i = 0 then 3
  else 3 * (1 - i) + sum n (i-1)

let rec sum_term n i acc = 
  if i = 0 then acc
  else sum_term n (i-1) (3 * (1 - i) + acc)
let rec fac n = 
  if n = 1 then 1
  else n * fac (n-1)

let rec fac_term n acc = 
  if n = 1 then acc
  else fac_term (n-1) (n * acc)

let rec fib n = 
  if n <= 2 then 1
  else fib (n-1) + fib (n-2)

let () = Printf.printf("Sum: %d\n") (sum user_n user_n)
let () = Printf.printf("Sum Terminal: %d\n") (sum_term user_n user_n 3)

let () = Printf.printf ("Factorial: %d\n") (fac 3)
let () = Printf.printf ("Factorial Terminal: %d\n") (fac_term 3 1)

let () = Printf.printf ("Fibonacci: %d\n") (fib 7)
