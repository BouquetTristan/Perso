pack([],[]).
pack([T, T|Q], Res):- pack([[T, T]|Q], Res).
pack([[T|Q]|[T|Q2]], Res):- pack([[T, T|Q]|Q2], Res).
pack([T|Q], [[T]|Res]):-
	not(is_list(T)),
	pack(Q, Res).
pack([T|Q], [T|Res]):- pack(Q, Res).