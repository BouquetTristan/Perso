init(_, _, _, _):-
	reine(1,1,1,1).

bouger(Y):-
	Y1 is Y+1.


pasvoisin(X, Y):-
	X = Y+1;
	X = Y-1;
	X = Y;
	bouger(Y),
	pasvoisin(X, Y).

reine(R1, R2, R3, R4):-
	init(R1, R2, R3, R4),
	pasvoisin(R1, R2),
	pasvoisin(R2, R3),
	pasvoisin(R3, R4).
