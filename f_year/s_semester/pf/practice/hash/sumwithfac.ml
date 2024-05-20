let sum n =
  let hash = Hashtbl.create 50 in 
    let rec sum_rec n =
      let rec get_fac i =
        try Hashtbl.find hash i 
        with Not_found -> 
          let result = 
              if i <= 1 then 1
              else i * get_fac (i-1)
            in Hashtbl.add hash i result; 
              result 
      in 
        if n <= 1 then 1
        else get_fac n + sum_rec (n-1)
    in 
      sum_rec n 

let sum n = 
  let hash = Hashtbl.create 50 in 
    let rec sum_rec n = 
      let rec fac_rec i =
        try Hashtbl.find hash i 
        with Not_found -> 
          let fac = 
            if i <= 1 then 1
            else i * fac_rec (i-1)
          in
            Hashtbl.add hash i fac;
            fac
        in
        if n <= 1 then 1
        else fac_rec n + sum_rec (n-1)
      in 
      sum_rec n