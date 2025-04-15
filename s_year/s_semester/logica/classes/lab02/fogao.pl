componente(estrutura, fogao).
componente(cordao_eletrico, fogao).

componente(resistencia_aquecimento, estrutura).
componente(painel, estrutura).

componente(botao, painel).

componente(fio_metalico, cordao_eletrico).
componente(isolador, cordao_eletrico).

material(resistencia_aquecimento, metal).
material(botao, plastico).
material(isolador, fibra_plastica).

parte_de(X, Y) :- componente(X, Y).

feito_em(X, Y) :- material(X, Y).
nao_feito_em(X, Y) :- feito_em(X, M), M \= Y.
    
faz_parte_fogao(X) :- componente(X, fogao).


/* 
Questions:  
    ? feito_em(M, metal) -> M = resistencia_aquecimento
    ? nao_feito_em(X, plastico) -> X = resistencia_aquecimento, X = isolador
*/


