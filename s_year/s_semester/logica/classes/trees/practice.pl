%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Representação de árvore binária.
%% binTree(Root, Left, Right): árvore binária com raiz Root, subárvore esquerda Left e subárvore direita Right.
%% A árvore vazia é representada pelo átomo 'empty'.

%% Exemplos de árvores binárias
tree1(
    binTree(1,
        binTree(2,
            binTree(3, empty, empty),
            binTree(4, empty, empty)
        ),
        binTree(5,
            binTree(6, empty, empty),
            binTree(7, empty, empty)
        )
    )
).

tree2(
    binTree(1, 
        binTree(2, empty, empty),
        empty
    )
).

tree3(
    binTree(1,
        binTree(2, empty, empty),
        binTree(1,
            empty,
            binTree(8,
                empty,
                binTree(8, empty, empty)
            )
        )
    )
).

%% Exemplos de árvores binárias de busca (BST)
bst1(
    binTree(10,
        binTree(5,
            binTree(3, empty, empty),
            binTree(7, empty, empty)
        ),
        binTree(15,
            binTree(12, empty, empty),
            binTree(20, empty, empty)
        )
    )
).

bst2(
    binTree(8,
        binTree(3,
            binTree(1, empty, empty),
            binTree(6, 
                binTree(4, empty, empty),
                empty
            )
        ),
        binTree(10,
            empty,
            binTree(14,
                binTree(13, empty, empty),
                empty
            )
        )
    )
).

bst3(
    binTree(5,
        empty,
        binTree(10,
            empty,
            binTree(15,
                empty,
                binTree(20,
                    empty,
                    binTree(25, empty, empty)
                )
            )
        )
    )
).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% node(Tree, Root)
%% Obtém o elemento da raiz do nó da árvore.
node(empty, 0).
node(binTree(X, _, _), X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% good(Tree)
%% Uma árvore é "good" se, para cada nó não-folha, o elemento da raiz é igual à soma dos elementos
%% das raízes das subárvores esquerda e direita.
good(empty).
good(binTree(_, empty, empty)).
good(binTree(Root, L, R)) :-
    node(L, LeftRoot),
    node(R, RightRoot),
    Root is LeftRoot + RightRoot,
    good(L), good(R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% equivalent(Tree, BinList)
%% Converte uma árvore binária para sua representação em lista.
%% Forma: [Root, LeftList, RightList]. Para árvore vazia, representa como 'e'.
equivalent(empty, e).
equivalent(binTree(Root, LTree, RTree), [Root, LList, RList]) :-
    equivalent(LTree, LList),
    equivalent(RTree, RList).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% height(Tree, Height)
%% Calcula a altura da árvore binária:
%% height = 1 + max(altura_esquerda, altura_direita).
height(empty, 0).
height(binTree(_, empty, empty), 1).
height(binTree(_, L, R), Height) :-
    height(L, HeightL),
    height(R, HeightR),
    (HeightL > HeightR -> Height is 1 + HeightL ; Height is 1 + HeightR).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% balanced(Tree)
%% Uma árvore é balanceada se a altura da subárvore esquerda está no intervalo [altura_direita - 1, altura_direita + 1].
balanced(empty).
balanced(binTree(_, L, R)) :-
    height(L, HeightL),
    height(R, HeightR),
    HeightL =< HeightR + 1,
    HeightL >= HeightR - 1,
    balanced(L), balanced(R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% nodes_list(Tree, List)
%% Retorna uma lista contendo todos os elementos (nós) da árvore.
nodes_list(empty, []).
nodes_list(binTree(Root, L, R), List) :-
    nodes_list(L, L_List),
    nodes_list(R, R_List),
    append(L_List, R_List, LR_List),
    append([Root], LR_List, List).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% levelif(Element, Tree, Level)
%% Retorna o nível (distância da raiz) do elemento na árvore usando uma abordagem com "if-then-else" (em estilo Prolog).
%% Se o elemento não for encontrado, retorna 0.
levelif(_, empty, 0).
levelif(Root, binTree(Root, _, _), 1).
levelif(Root, binTree(Other, L, R), Level) :-
    Root \= Other,
    levelif(Root, L, LevelL),
    levelif(Root, R, LevelR),
    (LevelL \= 0 ->  
        Level is 1 + LevelL ; 
        LevelR \= 0 ->  
            Level is 1 + LevelR ;
            Level is 0
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% level(Element, Tree, Level)
%% Retorna o nível (distância da raiz) do elemento na árvore.
%% Se o elemento for a raiz, retorna 1; caso contrário, procura recursivamente nas subárvores.
level(_, empty, 0).
level(Root, binTree(Root, _, _), 1).
level(Root, binTree(Other, L, _), Level) :-
    Root \= Other,
    level(Root, L, LevelL),
    LevelL > 0,
    Level is LevelL + 1.
level(Root, binTree(Other, _, R), Level) :-
    Root \= Other,
    level(Root, R, LevelR),
    LevelR > 0,
    Level is LevelR + 1.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Traversals: Pré-ordem, em-ordem e pós-ordem.
%%
%% preorder(Tree, List)
%% Retorna a lista de elementos em pré-ordem (raiz, esquerda, direita).
preorder(empty, empty).
preorder(binTree(Root, L, R), List) :-
    preorder(L, LList),
    preorder(R, RList),
    append([Root], [LList], Root_L_List),
    append(Root_L_List, [RList], List).

%%
%% inorder(Tree, List)
%% Retorna a lista de elementos em ordem (esquerda, raiz, direita).
inorder(empty, empty).
inorder(binTree(Root, L, R), List) :-
    inorder(L, LList),
    inorder(R, RList),
    append([LList], [Root], LList_Root),
    append(LList_Root, [RList], List).

%%
%% postorder(Tree, List)
%% Retorna a lista de elementos em pós-ordem (esquerda, direita, raiz).
postorder(empty, empty).
postorder(binTree(Root, L, R), List) :-
    postorder(L, LList),
    postorder(R, RList),
    append([LList], [RList], LR_List),
    append(LR_List, [Root], List).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% is_bst(Tree)
%% Verifica se a árvore binária é uma árvore de busca (BST).
%% Em uma BST, para cada nó, o valor da raiz deve ser maior ou igual ao da subárvore esquerda
%% e menor ou igual ao da subárvore direita.
is_bst(empty).
is_bst(binTree(_, empty, empty)).
is_bst(binTree(Root, L, R)) :-
    node(L, LRoot),
    node(R, RRoot),
    Root >= LRoot,
    Root =< RRoot,
    is_bst(L), is_bst(R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% bst_search(Element, BST)
%% Busca o elemento em uma árvore binária de busca (BST).
%% Se o elemento for menor que a raiz, pesquisa na subárvore esquerda;
%% se for maior, pesquisa na direita. Falha se a árvore estiver vazia.
bst_search(_, empty) :- !, fail.
bst_search(Root, binTree(Root, _, _)).
bst_search(El, binTree(Root, L, _)) :-
    El < Root,
    bst_search(El, L).
bst_search(El, binTree(Root, _, R)) :-
    El > Root,
    bst_search(El, R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% mirror(Tree, MirroredTree)
%% Produz a árvore espelhada (inverte as subárvores esquerda e direita recursivamente).
mirror(empty, empty).
mirror(binTree(Root, empty, empty), binTree(Root, empty, empty)).
mirror(binTree(Root, L, R), binTree(Root, MirroredL, MirroredR)) :-
    mirror(L, MirroredR),
    mirror(R, MirroredL).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% subTree(SubTree, Tree)
%% Verifica se SubTree é uma subárvore de Tree.
%% Pode ser que SubTree corresponda exatamente a Tree ou apareça em alguma das subárvores.
subTree(binTree(Root, L, R), binTree(Root, L, R)).
subTree(binTree(Root, LX, RX), binTree(_, LY, RY)) :-
    subTree(binTree(Root, LX, RX), LY)
    ; subTree(binTree(Root, LX, RX), RY).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% prune(Tree, Level, PrunedTree)
%% "Poda" a árvore até um determinado nível.
%% A árvore resultante contém apenas os nós até a profundidade Level.
prune(_, 0, empty).
prune(binTree(Root, L, R), Level, binTree(Root, PrunedLeft, PrunedRight)) :-
    LevelLeft is Level - 1,
    prune(L, LevelLeft, PrunedLeft),
    LevelRight is Level - 1,
    prune(R, LevelRight, PrunedRight).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% path(Element, Tree, Path)
%% Determina o caminho (lista de nós) da raiz até o nó contendo Element.

path(_, empty, []).
path(El, binTree(El, _, _), [El]).
path(El, binTree(Root, L, _), [Root|LPath]) :-
    El \= Root,
    path(El, L, LPath),
    LPath \= [].
path(El, binTree(Root, _, R), [Root|RPath]) :-
    El \= Root,
    path(El, R, RPath),
    RPath \= [].
path(El, binTree(Root, L, R), []) :-
    El \= Root,
    path(El, L, LPath),
    path(El, R, RPath),
    LPath = [],
    RPath = [].
