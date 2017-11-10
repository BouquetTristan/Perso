hanoi(0, _,_,_).

hanoi(N, D, A, I):-
	N1 is N-1,
	hanoi(N1, D, I, A),
	write('déplacement de '), write(D), write(' vers '), write(A), nl,
	hanoi(N1, I, A, D).

hanoi(N):-
	hanoi(N, départ, intermédiaire, arrivé).