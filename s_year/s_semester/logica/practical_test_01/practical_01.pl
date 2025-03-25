/* Problema 1
 * a) pais(_, portugal, X, _)
 * b) pais(europa, X, _, _)
 * c) pais(_, X, _, H), H >= 100.
 * d) pais(_, X, paris, _)

pais(continente, nome, capital, habitantes (M))
*/

pais(europa, portugal, lisboa, 10).
pais(europa, espanha, madrid, 100).
pais(europa, franca, paris, 100).
pais(america_sul, brasil, brasilia, 100).

/* Problema 2 
 *	a) progenitor(jose, joao)
 *	b) progenitor(maria, X)
 * 	c) primo(mario, X)
 *	f) irma(X, helena) 
 * */

feminino(maria).
feminino(ana).
feminino(helena).
feminino(joana).

masculino(jose).
masculino(joao).
masculino(mario).
masculino(carlos).

progenitor(jose, joao).
progenitor(maria, joao).
progenitor(jose, ana).
progenitor(maria, ana).

progenitor(ana, helena).
progenitor(ana, joana).

progenitor(joao, mario).

progenitor(helena, carlos).
progenitor(mario, carlos).

mae(X, Y) :- progenitor(Y, X), feminino(Y).
pai(X, Y) :- progenitor(Y, X), masculino(Y).

irma(X, Y) :- feminino(X), progenitor(Z, X), progenitor(Z, Y).
irmao(X, Y) :- masculino(X), progenitor(Z, X), progenitor(Z, Y).

avo(X, Y) :- masculino(X), progenitor(X, Z), progenitor(Z, Y).

tio(X, Y) :- masculino(X), irmao(Z, X), progenitor(Z, Y).
primo(X, Y) :- 
    masculino(X), 
    progenitor(Z, X), 
    progenitor(U, Z),
    progenitor(U, W),
    progenitor(W, Y).

descendente(X, Y) :- progenitor(X, Z), descendente(Z, Y).

/* Problema 3
 * a) 
 * 	arquelogo(codigo, nome, instituicao)
 * 	escavacao(id_escavacao, arquelogo, local, setor)
 * 	achado(id_achado, arquelogo, id_escavacao, classe, material, estado)
*/

arqueologo(arqueologo_01, carlitos, escaduras).
arquelogo(arquelogo_02, maria, escavaduras).

escavacao(escavacao_01, arquelogo_01, lisboa, setor_pedras).
escavacao(escavacao_02, arquelogo_02, porto, setor_dinosauros).

achado(achado_01, arquelogo_01, escavacao_01, pedra, granito, bom).
achado(achado_02, arquelogo_02, escavacao_02, osso, trex, desgastado).

/* Problema 4
 * a) feito_em(X, silico)
 * b) feito_em(X, Y), Y \= plastico
 * c) componente_pc(placa_mae) -> true, componente_pc(processador) -> true, componente_pc(teste) -> false 
*/
parte_de(computador, placa_mae).
parte_de(computador, caixa).
parte_de(placa_mae, processador).
parte_de(placa_mae, ram).
parte_de(caixa, painel_frontal).
parte_de(painel_frontal, botoes).
parte_de(teste, teste2).

componente_pc(X) :- parte_de(computador, X).
componente_pc(X) :- parte_de(Y, X), componente_pc(Y).

feito_em(ram, circuitos).
feito_em(processador, silico).
feito_em(caixa, metal).
feito_em(botoes, plastico).


/* Problema 6
 * a)
 * 	livro(id_isbn, id_autor, titulo, assunto, editora)
 * 	autor(id_autor, nome, pais, estilo)
 *  utente(id_utente, nome, classe, telefone)
 *  requesitacao(id_utente, id_isbn)
 * */

livro(isbn_01, autor_01, ulises, odisseia, historias_antigas).
livro(isbn_02, autor_01, carros_olivro, carros, pixar).

autor(autor_01, carlitos, portugal, variados).
autor(autor_02, ana, espanha, ficcao).

utente(utente_01, joao, estudante, 969608044).
utente(utente_02, maria, professor, 000000).

requesitacao(utente_01, isbn_01).
requesitacao(utente_01, isbn_02).


/* Problema 8
 * a) aluno(X, _, _)
 * b) aluno(maria, I, _).
 * c) mais_velho_de_todos(X)
 * */

aluno(joao, 18, m).
aluno(ana, 18, f).
aluno(maria, 16, f).
aluno(carlitos, 20, m).
aluno(pedro, 14, f).

mais_velho(X, Y) :- aluno(X, I1, _), aluno(Y, I2, _), I1 > I2. 
mais_velho_de_todos(X) :- aluno(Y,_, _), mais_velho(X, Y).








