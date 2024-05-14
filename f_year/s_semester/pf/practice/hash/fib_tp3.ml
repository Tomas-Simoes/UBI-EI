let rec fibonacci i n =
  if i <= 1 then 1
  else
    let hash = Hashtbl.create 100 
    in
      let new_sum =
        try Hashtbl.find hash i
          with Not_found ->
            match n with
            | 0 -> Hashtbl.add hash 0 0; 0
            | 1 -> Hashtbl.add hash 1 1; 1
            | _ -> 
              let new_fib =
                fibonacci i (n-1) + fibonacci i (n-2)
              in 
              print_string "\n"; print_int i; print_string "/"; print_int n; print_string "->"; print_int new_fib;
              new_fib + fibonacci (i-1) (i-1)
      in Hashtbl.add hash i new_sum; new_sum;;
