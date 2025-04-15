estadoInicial(cafe, 0).
estadoFinal(cafe, D) :-
    D >= 80,
    actua(D).

delta(cafe, EstadoAtual, 10, NovoEstado) :- NovoEstado is EstadoAtual + 10.
delta(cafe, EstadoAtual, 20, NovoEstado) :- NovoEstado is EstadoAtual + 20.
delta(cafe, EstadoAtual, 50, NovoEstado) :- NovoEstado is EstadoAtual + 50.
delta(cafe, EstadoAtual, M, _) :- 
    D is EstadoAtual + M,
    exit(D), !.

actua(80) :- darCafe.
actua(D) :- 
	darTroco(D),
    darCafe, !.

darCafe :- write("Café feito...").

darTroco(D) :-
	Troco is D - 80,
    write("Aqui tem o seu troco: "), write(Troco), write("Esc."), nl.

exit(D) :-
    write("A maquina nao aceita essas moedas!"),
    write("Aqui tem o seu dinheiro:"), write(D), write("Esc."), nl.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

estadoInicial(mb, inicio).
estadoFinal(mb, inicio).

% delta(Automato, EstadoAtual, Acao, NovoEstado)
delta(mb, inicio, cartao, cartao).
delta(mb, cartao, codigo, codigo).
delta(mb, codigo, levantar, levantar).

%% Ação Codigo -> Levantar
delta(mb, levantar, 15, entregar15).           % 15
delta(mb, entregar15, aceitar, inicio) :-
    msg(15),
    msg.

delta(mb, levantar, 10, entregar10).           % 10
delta(mb, entregar10, aceitar, inicio) :-
    msg(10),
    msg.

delta(mb, levantar, 5, entregar5).            % 5
delta(mb, entregar5, aceitar, inicio) :-
    msg(5),
    msg.

%% Ação de Código -> Consultar
delta(mb, codigo, consultar, consultar).

delta(mb, consultar, saldo, saldo).
delta(mb, saldo, aceitar, inicio) :-
    write("Retire o talao com o saldo"), nl, msg.
delta(mb, consultar, movimentos, movimentos).
delta(mb, movimentos, aceitar, inicio) :-
    write("Retire o talao com os movimentos"), nl, msg.

msg(D) :-
    write("Retire os seus "),
    write(D), write("000$00"), nl,
	write("Retire o talao").

msg :-
    write("Retire o seu cartao"), nl,
    write("Volte sempre").

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Testar Automatos
aceita(Acao, ListaAcoes) :-
    estadoInicial(Acao, EstadoInicial),
    aceita_aux(Acao, ListaAcoes, EstadoInicial).
    
aceita_aux(Acao, [], Estado) :-
	estadoFinal(Acao, Estado).

aceita_aux(Acao, [Head|Tail], Estado) :-
    delta(Acao, Estado, Head, NovoEstado),
    aceita_aux(Acao, Tail, NovoEstado).
