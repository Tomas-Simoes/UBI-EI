%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Exercicio 3

% ingles, espanhol, noruegues, portugues ucraniano
% vermelho, amarelo, azul, branca, verde
% cao, raposa, iguana, cavalo        zebra, 

% [noruegues, azul, leite, ...] 
% verde é a direita da branca

resolver_zebra(Casas, ZebraPos, AguaPos) :-
    Casas = [
      casa(1, _, _, _, _, _),
      casa(2, _, _, _, _, _),
      casa(3, _, _, _, _, _),
      casa(4, _, _, _, _, _),
      casa(5, _, _, _, _, _)
    ],

    aplicar_restricoes(Casas),
    zebra_pos(Casas, ZebraPos),
    agua_pos(Casas, AguaPos).

aplicar_restricoes(Casas) :-

    member(casa(_, ingles, vermelha, _, _, _), Casas),

    member(casa(_, espanhol, _, _, cao, _), Casas),

    member(casa(1, noruegues, _, _, _, _), Casas),

    member(casa(_, _, amarela, _, _, malboro), Casas),

    member(casa(PosRaposa, _, _, _, raposa, _), Casas),
    member(casa(PosChester, _, _, _, _, chesterfield), Casas),
    ( PosChester is PosRaposa + 1
    ; PosChester is PosRaposa - 1 ),

    member(casa(2, _, azul, _, _, _), Casas),

    member(casa(_, _, _, _, iguana, winston), Casas),

    member(casa(_, _, _, sumolaranja, _, lucky), Casas),

    member(casa(_, ucraniano, _, cha, _, _), Casas),

    member(casa(_, portugues, _, _, _, sglight), Casas),

    member(casa(PosCavalo, _, _, _, cavalo, _), Casas),
    member(casa(PosMalboro, _, _, _, _, malboro), Casas),
    ( PosMalboro is PosCavalo + 1
    ; PosMalboro is PosCavalo - 1 ),

    member(casa(PosVerde, _, verde, cafe, _, _), Casas),

    PosBranca is PosVerde - 1,
    member(casa(PosBranca, _, branca, _, _, _), Casas),

    member(casa(3, _, _, leite, _, _), Casas).

zebra_pos(Casas, PosZebra) :-
    member(casa(PosZebra, _, _, _, zebra, _), Casas).

agua_pos(Casas, PosAgua) :-
    member(casa(PosAgua, _, _, agua, _, _), Casas).
