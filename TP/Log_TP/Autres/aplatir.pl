aplatir([], []).
aplatir(T, [T]):-
	not(is_list(T)).
aplatir([T|Q], X):-
	aplatir(T,Y), aplatir(Q,U), append(Y,U,X).