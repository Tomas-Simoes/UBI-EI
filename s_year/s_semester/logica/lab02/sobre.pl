sobre(objetoA, mesa).
sobre(objetoB, objetoA).

acima_de(X, Y) :- sobre(X, Y).
acima_de(X, Y) :- sobre(X, Z), acima_de(Z, Y).

/* 
Questions:  
    ? acima_de(objetoB, mesa) -> true
*/
