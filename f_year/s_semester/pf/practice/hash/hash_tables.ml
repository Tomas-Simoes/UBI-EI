let hash_norec f =
  let hash = Hashtbl.create 11 in 
    fun x ->
      try Hashtbl.find hash x 
      with Not_found ->
        let y = f x in Hashtbl.add hash x y;
        y

let hash_rec f =
  let hash = Hashtbl.create 11 in 
    let rec g x =
      try Hashtbl.find hash x 
      with Not_found ->
        let y = f g x in Hashtbl.add hash x y;
        y
      in 
      g


