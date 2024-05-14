let hash_insert_any x =
  let hash = Hashtbl.create 7 in 
    if Hashtbl.mem hash x then Hashtbl.find hash x
    else 
      let hash_value = Hashtbl.hash x in 
        Hashtbl.add hash x hash_value;
        Hashtbl.find hash x