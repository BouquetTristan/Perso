somme([], Somme, Somme).

somme([H|T], Som, Somme):-
	Som1 is Som + H,
	somme(T, Som1, Somme).

somme(List, Somme):-
	somme(List, 0, Somme).