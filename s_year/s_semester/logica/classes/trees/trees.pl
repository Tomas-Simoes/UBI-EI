
edge(a, b).
edge(a, c).
edge(b, d).
edge(b, e).
edge(c, f).
edge(f, i).
edge(c, g).


listAdj(A, LAdg) :-
    findall(B, edge(A, B), LAdg).

buscaProfundidade(A, [A]) :- not(edge(A, _)).
buscaProfundidade(A, [A|Res]) :-
    listAdg(A, LAdg),
    buscaProfundidade_List(LAdg, Res).
    
buscaProfundidade_List([], []).
buscaProfundidade_List([H|T], Res) :-
    buscaProfundidade(H, Res1),
    buscaProfundidade_List(T, Res2),
    append(Res1, Res2, Res).

buscaLargura(A, []) :- not(edge(A, _)).
buscaLargura(A, Res) :-
    listAdj(A, LAdj),
    buscaLargura_Adj(LAdj, NextLevel),
	append(LAdj, NextLevel, Res).
	
buscaLargura_Adj([], []).
buscaLargura_Adj([HAdj|TAdj], NextLevel) :-
    buscaLargura(HAdj, NextHLevel),
    buscaLargura_Adj(TAdj, NextLAdj),
    append(NextHLevel, NextLAdj, NextLevel).
	
