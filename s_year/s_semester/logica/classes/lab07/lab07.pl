selecciona(Fornecedor) :-
    write(fornecedor(Fornecedor)), write('.'), nl,
    sel(Fornecedor).

sel(F) :-
    read(Item),
    processa(Item,F).

processa(end_of_file,_).
processa(item(N,D,P,F),F):- 
    write(item(N,D,P)),
    write('.'), nl,
    sel(F).
processa(_, F) :-
    sel(F).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

readFile(Item) :-
    read(Item).

processaFamilia(end_of_file, _, _, []).
processaFamilia(eFilhoDe(Ind1, Ind2), X, Y, []).
processaFamilia(eFilhoDe(X, Y), X, Y, [X,Y]).
processaFamilia(eFilhoDe(X, Ind1), X, Y, [X|NextPath]) :-
    consanguineos_aux(Y, Ind1, NextPath).

consanguineos(X, Y, Count) :-
    consanguineos_aux(X, Y, Path),
    length(Path, Count).
    
consanguineos_aux(X, Y, Path) :-
    readFile(Item),
    processaFamilia(Item, X, Y, Path).

