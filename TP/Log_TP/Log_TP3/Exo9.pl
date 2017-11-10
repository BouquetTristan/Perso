inverse(Liste, Res):-
    inverse2(Liste, Res, []).

inverse2([], L, L).
inverse2([T|Q], L, Acc):-
    inverse2(Q, L, [T|Acc]).
