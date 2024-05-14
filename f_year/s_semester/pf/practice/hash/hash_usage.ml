let create_hash arr = 
  let hash = Hashtbl.create 16 in 
    let rec add_arr arr = 
      match arr with
      | [] -> hash
      | h::t -> 
        Hashtbl.add hash h (string_of_int h); 
        add_arr t
    in add_arr arr

let hash_stats =
  let hash = create_hash [1; 2; 3; 4; 5; 6; 7; 8; 9] in 
    Hashtbl.stats hash;;
