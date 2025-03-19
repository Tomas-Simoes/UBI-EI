membro(X, [X|T]).
membro(X, [_|T]) :- membro(X, T).

concatena([], L2, L2).
concatena([X| T], L2, [X|L3]) :- concatena(T, L2, L3).

inverter([], L3) :- writeln(L3).
inverter(L1, L2) :- append(T, [Last], L1), append(L2, [Last], L3t), inverter(T, L2).

remover(_, [], []).
remover(EL, [EL|L2], L2).
remover(EL, [H|T], [H|L3]) :- remover(EL, T, L3).

sublista([], L2).
sublista([H1, T1], [H2|T2]) :- sublista([H1, T1], T2).
sublista([H1|T1], [H1|T2]) :- sublista(T1, T2).

intercalar([], [], L3).
intercalar([H1|T1], [H2|T2], [H1, H2|L3]) :- intercalar(T1, T2, L3).

intercalarInv([], [], L3) :- writeln(L3).
intercalarInv([H1|T1], [H2|T2], L3) :- intercalarInv(T1, T2, [H1, H2|L3]).

tamanho([], S).
tamanho([H1|T], S) :- S is S+1, tamanho(T, S).

ultimo([], 0).
ultimo([H|[]], H).
ultimo([_|T], X) :- ultimo(T, X).

soma([], 0).
soma([H], H).
soma([H|T], S) :- soma(T, S1), S=S1+H.

maior([H], H).
maior([H|T], B) :- maior(T, B1), (B1>H -> B=B1; B=H).

menores([H], N) :- (H < N).
menores([H|T], N) :- menores(T, N), (H<N).

duplicar([H], [H,H]).
duplicar([H|T], [H,H|L]) :- duplicar(T, L).

dividir([], 0, [], []).
dividir([E1|T1], 0, S, [E1|R]) :- dividir(T1, 0, S, R).
dividir([E1|T1], P, [E1|S], R) :- P1 is P - 1, dividir(T1, P1, S, R).