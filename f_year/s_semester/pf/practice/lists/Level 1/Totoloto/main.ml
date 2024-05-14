type grelhas = bool array array

let make_grelha n = Array.make_matrix n n false

let grelha: grelhas = Array.make_matrix 7 7 false 

let rec fill list =
  match list with 
  | [] -> grelha
  | el :: rx -> 
    grelha.(el / 7).(el mod 7) <- true;
    fill rx

let rec sorteio (grelha:grelhas) (list:int list) (n:int) = (
  match list with 
  | [] -> [], grelha.(n / 7).(n mod 7)  
  | h::t -> 
    if grelha.(h / 7).(h mod 7) = true then
      let numeros_certos, n_certo = sorteio grelha t n in 
      h :: numeros_certos, n_certo
    else 
      sorteio grelha t n
);;

fill [2; 6; 10; 35; 24; 12; 7; 1];;

let numeros_certos, n_certo = sorteio grelha [24; 29; 28; 2; 30; 12; 9] 1 in  
print_string "(";
print_string "[";
List.iter (fun x -> print_int x; print_string ",") numeros_certos;
print_string "] , ";
Printf.printf "%b" n_certo;
print_string ")";

