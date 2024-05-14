let hash_rec f =
  let hash = Hashtbl.create 11 in 
    let rec g x =
      try Hashtbl.find hash x 
      with Not_found ->
        let y = f g x in Hashtbl.add hash x y;
        y
      in 
      g
      
let fib_hash = 
  let fib self n =
    if n < 2 then 1 else self (n - 1) + self (n - 2)
  in
  hash_rec fib  
        
let tribonacci_hash n = 
  let tri self n =
    if n < 2 then 1 else self (n - 1) + self (n - 2) + self (n - 3)
  in 
    hash_rec tri
