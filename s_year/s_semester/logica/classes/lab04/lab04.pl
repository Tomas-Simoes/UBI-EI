concatena([], L, L).
concatena([X|T], L, [X|C]) :-
    concatena(T, L, C).

adiciona(X, L [X|L]).

tira(_, [], []).
tira(X, [X|T], T).
tira(X, [Y|T], [Y|L]) :- tira(X, T, L).

adiciona_fim(X, L, NL) :-
    concatena(L, [X], NL).

tira_todos(_, [], []).
tira_todos(X, [X|T], L) :- tira_todos(X, T, L), !.
tira_todos(X, [Y|T], [Y|L]) :- tira_todos(X, T, L). 

pertence(X, [X|_]).
pertence(X, [_|T]) :- pertence(X, T).

ultimo(X, [X]).
ultimo(X, [_|T]) :- ultimo(X, T). 

sublista([X], [X|_]).
sublista([X|T1], [X|T2]) :- sublista(T1, T2).
sublista([X|T1], [_|T2]) :- sublista([X|T1], T2).

permutacao([], L2).
permutacao([X|T], L2) :- pertence(X, L2), permutacao(T, L2), !.

ordena([X], [X]).
ordena([X|T1], [Y|T2]) :-
    ordena(T1, [Y1|T2]),
    (X < Y1 -> 
        ordena(T1, [X, Y | T2]) ; 
        ordena([X | T1], T2)).
