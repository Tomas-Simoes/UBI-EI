let v1 = [|"A exelência"; "A intervenção"; "O objetivo"|];;
let v2 = [|"reforça"; "revela"; "estimula"|];;
let v3= [|"os fatores"; "os parâmetros"; "os conceitos"|];;
let v4=[|"instituicionais"; "analíticos"; "motivacionais"|];;
let v5=[|"do grupo"; "dos beneficiários"; "da hierarquia"|];;

let list = [v1; v2; v3; v4; v5];;

let rec create_setence list = (
  match list with
  | [] -> " "
  | h :: t -> 
    let randomIndex = Random.int (Array.length h) in
      h.(randomIndex) ^ " " ^ create_setence t;;
      other instruction;
    return of match;;
);;

print_string (create_setence list)