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
% not completed

nivela([[]|T], List) :-
    nivela(T, List).
nivela([[X|Y]|T], List) :- 
    nivela([X|Y], List1),
    nivela(T, List2).
	append(List1, List2, List).
nivela([H|T], [H|List]) :-
    nivela(T, List).
