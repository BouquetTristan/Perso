
substituer(_, _, [], _).

substituer(X, Y, [H|Q], []):-
	substituer(X, Y, Q, [H]).

substituer(X, Y, [X|Q], L2):-
	substituer(X, Y, Q, [Y|L2]).

substituer(X, Y, [H|Q], L2):- 
	substituer(X, Y, Q, [H|L2]).