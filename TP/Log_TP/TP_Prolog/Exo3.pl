nombre_car([], _, _).

nombre_car([X|Q], X, N):-
	N1 is N+1,
	nombre_car(Q, X, N1).
nombre_car([_|Q], X, N):-
	nombre_car(Q, X, N).
