gcd(A, 0, A).
gcd(A, B, Resultado) :- 
    Resto is A mod B, 
    gcd(B, Resto, Resultado), !.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mdc_aux(A, 0, A, []).
mdc_aux(A, B, B, []) :-
    Resto is A mod B,
    Resto = 0.
mdc_aux(A, B, Resultado, [[Resto, [-Q, B], [1, A]]|L]) :- 
    Q is A // B,
    Resto is A mod B, 
    mdc_aux(B, Resto, Resultado, L).

mdc(A, B, Resultado, InvLista) :-
    mdc_aux(A, B, Resultado, L),
    reverse(L, InvLista).
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

diofantina(A, B, C, X, Y) :-
    A > B,
    mdc(A, B, M, L), !,
    0 is C mod M,
    expande(L, [M, [Y1, B], [X1, A]]),
    Mlt is C // M,
    X is X1 * Mlt,
    Y is Y1 * Mlt.

expande([L], L).

expande([[A1, [B1, _], [D1, E1]], [_, [B2, E1], [D2, E2]] | R], L) :-
        B is B1 * B2 + D1,
        D is B1 * D2,
        expande([[A1, [B, E1], [D, E2]] | R], L).