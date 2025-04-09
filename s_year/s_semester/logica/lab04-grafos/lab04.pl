produto_de(_, 0, 0).
produto_de(A, B, C) :- B1 is B - 1, produto_de(A, B1, C1), C is C1 + A.

binario(0, "").
binario(A, B) :- Res is div(A, 2), Bit is mod(A, 2), binario(Res, B), string_concat(B, Bit, B).

edge(a, b, 25). 
edge(a, d, 23).
edge(b, c, 19).
edge(b, e, 32).
edge(e, f, 26).
edge(c, f, 28).
edge(d, f, 30).
edge(c, d, 14).


dist(A, B, D) :- edge(A, B, D).
dist(A, C, D) :- 
    edge(B, C, D1), dist(A, B, D2), D is D1 + D2.

edge2(a, b, 1). 
edge2(a, d, 2).
edge2(b, c, 3).
edge2(b, e, 5).
edge2(e, f, 8).
edge2(c, f, 6).
edge2(d, f, 7).
edge2(c, d, 4).

route(A, B, [B, A]) :- edge2(A, B, _).
route(A, C, P) :-
    edge2(B, C, _), route(A, B, P1), P = [C|P1] .


W W