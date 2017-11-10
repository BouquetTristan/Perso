pack([],[]).
pack([T, T|Q], Res):- pack([[T, T]|Q], Res).
pack([[T|Q]|[T|Q2]], Res):- pack([[T, T|Q]|Q2], Res).
pack([T|Q], [[T]|Res]):-
	not(is_list(T)),
	pack(Q, Res).
pack([T|Q], [T|Res]):- pack(Q, Res).

encode([], []).
encode(Q, [[Long, X]|Y]):-
	pack(Q, [[X|Xs]|T]),
	length([X|Xs], Long),
	encode(T, Y).