action(
    state(center, box, center, no),
    grab_banana,
    state(center, box, center, yes)
).

action(
    state(P, floor, P, YesOrNo),
    climb,
    state(P, box, P, YesOrNo)
).

action(
    state(P1, floor, P1, YesOrNo),
    push_box(P1, P2),
    state(P2, floor, P2, YesOrNo)
).

action(
    state(P1, floor, B, YesOrNo),
    walk(P1, P2),
    state(P2, floor, B, YesOrNo)
).

gets_banana(state(_,_,_,yes)).
gets_banana(StartState) :- 
    action(StartState, _Action, EndState),
    gets_banana(EndState).
