socio(susana).
socio(joao).
socio(basilio).
socio(elviria).

casado(joao, susana).

irma(elvira, basilio).

irmao(Y, X) :- irma(X, Y).

/* 
Questions:  
    ? socio(S) -> S=Susana, S=joao, S=basilio, S=elviria
    ? irmao(basilio,  elvira) -> true
    ? socio(miquelina) -> false
    ? casado(S, susana) -> S=joao
*/
