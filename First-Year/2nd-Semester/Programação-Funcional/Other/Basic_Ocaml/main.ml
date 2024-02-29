(* If Statements*)
let i = 2 and j = 3;;

if i < j then 
  (
    print_string("True Statement")
  )
else 
  (
    print_string("False Statement")
  );;


(*
  For/While Loop

Syntax:
  
    for variable = start_value to end_value do
      (expression)
    done

    "to" can also be "downto" to be a decrement loop. 

    
    while boolean-condition do
      expression
    done
*)

for i = 0 to 3 do 
  print_string "\nThe value of i is: ";
  print_int i; 
done;;

while i < 5 do
  print_string "test";
done