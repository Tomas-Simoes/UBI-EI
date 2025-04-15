eleiturade([], []).
eleiturade([Index,H2|T], [H2|R]) :-
    Index \= 0, NextIndex is Index-1, 
    eleiturade([NextIndex, H2|T], R).
eleiturade([Index,_|T], R) :- Index = 0, eleiturade(T, R).


jogo_degraus(NumDegraus, NumPossibilidades, Res) :-
    findall(X, climb(NumDegraus, X), Res), length(Res, NumPossibilidades).

num_possibilidades(Num, Res) :- Res is 2 ^ (Num - 1).

climb(0, []).
climb(Num, [1|R]) :- Num >= 1, N1 is Num-1, climb(N1, R).
climb(Num, [2|R]) :- Num >= 2, N1 is Num-2, climb(N1, R).

 
