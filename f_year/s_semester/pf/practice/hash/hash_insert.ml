let hash_insert x =
  let hash = Hashtbl.create 7 in 
    if Hashtbl.mem hash x then Hashtbl.find hash x 
    else 
      let new_value = x mod 7 in 
        Hashtbl.add hash x new_value;
      Hashtbl.find hash x 

let hash_insert_int x =
  let hash = Hashtbl.create 7 in 
    if Hashtbl.mem hash x then Hashtbl.find hash x 
    else 
      let new_value = x mod 7 in 
        Hashtbl.add hash x new_value;
      Hashtbl.find hash x 

