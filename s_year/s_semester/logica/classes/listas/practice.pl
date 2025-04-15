%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% comprimento_par(List) is true if listLength mod 2 = 0

listLength([], 0).
listLength([_|T], Length) :-
    listLength(T, TailLength),
    Length is 1 + TailLength.

comprimento_par(List) :-
    listLength(List, ListLength),
    0 is ListLength mod 2.

comprimento_impar(List) :-
    listLength(List, ListLength),
    not(0 is ListLength mod 2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% capicua(List)	[a,n,a] is capicua because List = InvList

inverter([], []).
inverter([H|T], Inv) :-
	inverter(T, InvTail),
    append(InvTail, [H], Inv).

capicua(List) :- 
	inverter(List, InvList),
    List = InvList.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% shift(List, Res)		[1,2,3,4] -> [2,3,4,1] -> [3,4,1,2]

shift([H|T], Res) :- append(T, [H], Res).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% traduz(List, Res)	[1,2,a,3,4] -> [um, dois, a, tres, 4] 	Translates 1,2 and 3 to um, dois, tres

dic(1, um).
dic(2, dois).
dic(3, tres).
dic(H, H).

traduz([], []).
traduz([H|T], [Translation|TailTranslation]) :-
    dic(H, Translation),
    traduz(T, TailTranslation).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% sublista(SubList, List)		[2,3] is sublist of [1,2,3,4] but [2,4] is not sublist (it's not consecutively)

sublista_aux([], _).
sublista_aux([HSub|TSub], [HList|TList]) :- 
    HList = HSub,
    sublista_aux(TSub, TList).

sublista([], _).
sublista(SubList, List) :- sublista_aux(SubList, List). 
sublista(SubList, [_|TList]) :- sublista(SubList, TList).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% subset(SubSet, Set)		[2,2,3] and [2,2,4] is subset of [1,2,3,2,4]

remove(X, [X|Tail], Tail).
remove(X, [H|Tail], [H|TailRes]) :-
    remove(X, Tail, TailRes).

subset([], _).
subset([HSub|TSub], Set) :-
	remove(HSub, Set, NewSet),
    subset(TSub, NewSet).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% divide(List, List1, List2)	[1,2,3,4,5] divides to [1,2] and [3,4,5]
% doesnt work for the case divide([1,2,3,4,5], [1,2,4], [3,5]) where it should return true because it's a way
% to divide the list where which list has length OriginalLenght / 2

divide_aux([], [], [], _).
divide_aux([H|T], List1, [H|List2], Index) :-
    Index == 0,
    divide_aux(T, List1, List2, 0).

divide_aux([H|T], [H|List1], List2, Index) :-
    Index > 0,
    NextIndex is Index - 1,
    divide_aux(T, List1, List2, NextIndex).

divide(List, List1, List2) :-
    listLength(List, ListLength),
    HalfLength is ListLength // 2,
    divide_aux(List, List1, List2, HalfLength).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% nivela(List, LeveledList)	[a, b, [c,d], [[e]], f] -> [a,b,c,d,e,f]

nivelar([], []).
nivelar([[]|Tail], Nivelada) :-
    nivelar(Tail, Nivelada).
nivelar([[X|Tx]|Tail], Nivelada) :-
       nivelar([X|Tx], TxNivelada),
       nivelar(Tail, TailNivelada),
       append(TxNivelada, TailNivelada, Nivelada).
nivelar([H|T], [H|Nivelada]) :- nivelar(T, Nivelada).
       
nivela([[]|T], List) :-
    nivela(T, List).
nivela([[X|Y]|T], List) :- 
    nivela([X|Y], List1),
    nivela(T, List2).
	append(List1, List2, List).
nivela([H|T], [H|List]) :-
    nivela(T, List).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% consecutive_members(X, Y, List)	returns true if: x and y belong to List and appear consecutively 

consecutive_members(X, Y, [X,Y|_]).
consecutive_members(X, Y, [_,_|Tail]) :- consecutive_members(X,Y,Tail).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% code(Phrase, EncodedPhrase, Delta)	'abc01' -> 'cde34' for delta = 3	moves every letter plus Delta 	

code(F, FCode, Delta) :-
    name(F, FAscii),
    encoder(FAscii, Delta, AsciiEncoded, encode),
    name(FCode, AsciiEncoded).

decode(F, FCode, Delta) :-
	name(FCode, AsciiEncoded),
    encoder(AsciiDecoded, Delta, AsciiEncoded, decode),
    name(F, AsciiDecoded).
    
encoder([], _, [], _).
encoder([HAscii|TAscii], Delta, [HEncoder|AsciiEncoded], encode) :-
    HEncoder is HAscii + Delta,
    encoder(TAscii, Delta, AsciiEncoded, encode).
encoder([HDecoded|AsciiDecoded], Delta, [HEncoded|TEncoded], decode) :-
    HDecoded is HEncoded - Delta,
    encoder(AsciiDecoded, Delta, TEncoded, decode).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% depth(El, NestedList, Depth)	gives the depth of the first occurence of an element in a list
%%									depth being how much nested arrays it has to search to find el
%%									depth(3, [3, [[2, [3, 4]], [5, 6]]], Depth)	-> 	Depth = 3
depth(_, [], 0).

depth(El, [[El|_]|_], 2).
depth(El, [[_|TNested]|Tail], Depth) :-
    depth(El, TNested, NestedDepth),
    (NestedDepth \= 0 ->
    	Depth is 1 + NestedDepth ;
    	depth(El, Tail, Depth)
    ).

depth(El, [El|_], 1).
depth(El, [_|Tail], Depth) :- 
    depth(El, Tail, Depth).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% duplicate(L, LL)	duplicates every element on list	[1,2,3] -> [1,1,2,2,3,3]

duplicate([], []).
duplicate([H|Tail], [H,H|DuplicateList]) :-
    duplicate(Tail, DuplicateList).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% separate(List, tuple(Numbers, Letters))	separetes every element on list into the tuple Numbers and Letters


separate([], ([], [])).
separate([Head|Tail], ([Head|Numbers], Letters)) :-
	number(Head),
    separate(Tail, (Numbers, Letters)).
separate([Head|Tail], (Numbers, [Head|Letters])) :-
    separate(Tail, (Numbers, Letters)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% plays some juicy 1D Conways Game of Life (sick)

rule(0,0,0).
rule(0,1,1).
rule(1,0,1).
rule(1,1,0).

next_generation([], []).
next_generation([H], [H]).
next_generation([H1, H2|Tail], [NextCell|NextGen]) :-
	rule(H1, H2, NextCell),
	next_generation([H2|Tail], NextGen).

conways_game(0, _, []).
conways_game(NumGen, Gen, [NextGen|Result]) :-
    next_generation(Gen, NextGen),
    NextNumGen is NumGen - 1,
    conways_game(NextNumGen, NextGen, Result).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% invertAll(List, Inverted)	inverts everything	[1,[2,3],4] -> [4,[3,2],1]

invertNested([], []).
invertNested([[HNested|TNested]|TList], Inv) :-
    invertNested([HNested|TNested], NestedInv),
    invertNested(TList, ListInv),
    append(ListInv, [NestedInv],Inv).
invertNested([HList|TList], Inv) :-
    invertNested(TList, ListInv),
    append(ListInv, [HList], Inv).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% merge(OrderedList1, OrderedList2, MergedList)	merges two ordered lists into one ordered list

smaller(X, Y) :- X =< Y.

merge([], [], []).
merge([], L, L).
merge(L, [], L).
merge([H1|T1], [H2|T2], [H1|Res]) :-
    smaller(H1, H2),
   	merge(T1, [H2|T2], Res).
merge([H1|T1], [H2|T2], [H2|Res]) :-
	smaller(H2, H1),
    merge([H1|T1], T2, Res).
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% separate(Obj, List, BeforeObj, AfterObj)		for Obj = * 	[1,2,3,4,*,a,b,c,d] -> [1,2,3,4] and [a,b,c,d]

separate(_, [], [], []).
separate(Obj, [H|T], [H|BeforeObj], AfterObj) :-
    Obj \= H,
    separate(Obj, T, BeforeObj, AfterObj).
separate(Obj, [Obj|T], [], T).








