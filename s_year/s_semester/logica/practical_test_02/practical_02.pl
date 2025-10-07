%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Util func
listLength([], 0).
listLength([_|T], Length) :-
    listLength(T, TailLength),
    Length is 1 + TailLength.

invert([], []).
invert([H|T], Inv) :-
    invert(T, TailInv),
    append(TailInv, [H], Inv).

member(X, [X|_]).
member(X, [_|T]) :-
    member(X, T).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 1
particionar([], _, [], []).
particionar([H|T], Pivot, [H|SmallerTail], HigherList) :-
	H =< Pivot,
	particionar(T, Pivot, SmallerTail, HigherList).
particionar([H|T], Pivot, SmallerList, [H|HigherTail]) :-
	particionar(T, Pivot, SmallerList, HigherTail).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 2

comprimento_par(List) :-
    listLength(List, ListLength),
    0 is ListLength mod 2.

comprimento_impar(List) :-
    listLength(List, ListLength),
    not(0 is ListLength mod 2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 3		TODO sort the final standings

% calculateFinalResults([
%     [monaco, [alonso, montoya, coulthard, barrichello, schumacher, fisichelella, massa, albers]],
%     [unitedStates, [schumacher, barrichello, monteiro, karthikeyan, albers, frisacher]],
%     [mola, [massa, schumacher, barrichello, button, trulli, albers, montoya, alonso, webber, monteiro, speed, sato]]
% ]).

pontos(1, 10).
pontos(2, 8).
pontos(3, 6).
pontos(4, 5).
pontos(5, 4).
pontos(6, 3).
pontos(7, 2).
pontos(8, 1).
pontos(_, 0).

calculateFinalResults(RaceList) :-
	totalPoints(RaceList, FinalPoints),
	
    format('**************************'), nl,
    format('     Final Standings      '), nl,
    format('**************************'), nl,
    format('Racer				Points'), nl,
    writePoints(FinalPoints).

writePoints([]).
writePoints([[Racer, RacerPoints]|RestRacers]) :-
    format('  ~w - ~d points~n', [Racer, RacerPoints]),	
    writePoints(RestRacers).

% Given an array of arrays of type [[race_name, [raceColocations]], ...] gives all 
% racers final points (sum of their points in all races)
%
% 1º (getRacePoints) For each race, get's each racer points on that race
% 2º (updatePoints)  Then updates the current final points given the previous final points and the current race
totalPoints([], []).
totalPoints([[_, RaceResults]|RestRaces], FinalPoints) :-
	getRacePoints(RaceResults, 1, RacePoints),
	totalPoints(RestRaces, RestPoints),
    updatePoints(RacePoints, RestPoints, FinalPoints).

% Given an racer and the array of all racers total points, gives the current total
% points of that racer
getCurRacerPoints(_, [], 0).
getCurRacerPoints(Racer, [[Racer, RacerPoints]|_], RacerPoints).
getCurRacerPoints(Racer, [[_,_]|RestRacers], RacerPoints) :-
    getCurRacerPoints(Racer, RestRacers, RacerPoints).

% Given an array of type [[Racer, RacerPoints], ...] and an array of type [[Racer, CurrentTotalPoints], ...]
% updates the current total points by adding the new RacerPoints
updatePoints([], _, []).
updatePoints(RacePoints, [], RacePoints).
updatePoints([[Racer, RacerPoints]|RestRacers], 
             CurTotalRacers, 
             [[Racer, FinalPoints]|RestFinalPoints]) :-
    getCurRacerPoints(Racer, CurTotalRacers, CurPoints),
    FinalPoints is RacerPoints + CurPoints,
    updatePoints(RestRacers, CurTotalRacers, RestFinalPoints).

% Given an array of type [Race, [RaceColocations]] returns an array of type [[Racer, RacerPoints], ...] 
getRacePoints([], _, []).
getRacePoints([Racer|T], Index, [[Racer, RacerPoints]|RestRacers]) :-
	pontos(Index, RacerPoints),
	NextIndex is Index + 1,
	getRacePoints(T, NextIndex, RestRacers).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 4
cor(vermelho).
cor(amarelo).
cor(azul).
cor(nomorecolors).

get_color([], [], []).

% Case for coloring the Node
get_color([Node|AdjNodes], [NodeColor|UsedColors], [[Node, NodeColor]|ColoredNodes]) :- 
    (cor(NodeColor), 
    	not(member(NodeColor, UsedColors)) ; NodeColor = nomorecolors
    ),
    get_color(AdjNodes, UsedColors, ColoredNodes).    

% Case for coloring the adjacent nodes
get_color([AdjNode|RestAdj], [NodeColor|UsedColors], [[AdjNode, NodeColor]|ColoredNodes]) :-
    (cor(NodeColor), 
    	not(member(NodeColor, UsedColors)) ; NodeColor = nomorecolors
    ),
    get_color(RestAdj, UsedColors, ColoredNodes).
    
 
%colorir([Node_Adj|Tail], NodesColors, [[Node,NewColor]|Coloracao]) :-
%	get_color(Node_Adj, Colored), %% Node Color
	

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 5

node(empty, 0).
node(binTree(Root, _, _), Root).

boa(empty).
boa(binTree(_, empty, empty)).
boa(binTree(Root, L, R)) :-
    node(L, LeftRoot),
    node(R, RightRoot),
    Root is LeftRoot + RightRoot,
    boa(L), boa(R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Ex. 6

equivalent(empty, e).
equivalent(binTree(Root, LTree, RTree), [Root, LList, RList]) :-
    equivalent(LTree, LList),
    equivalent(RTree, RList).