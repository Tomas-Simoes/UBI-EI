type polinomios = float * float list

let rec horner x (polinomio:polinomios) = (
  let grau, coeficiente = polinomio in
  ( 
    match coeficiente with
    | [] -> 0.
    | h::t -> h * x + horner x (grau, )

  )
);;

(3x * x + (0)) * x + 5
  3x2 + 0

  print_float (horner 1. (4., [3.;0.;5.;0.;1.]))