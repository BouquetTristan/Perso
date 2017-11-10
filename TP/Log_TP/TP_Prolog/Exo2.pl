supprimer(_, [], _).


supprimer(X, [X|Q], L2):-
	supprimer(X, Q, L2).
supprimer(X, [H|Q], []):-
	supprimer(X, Q, [H]).
supprimer(X, [H|Q], L2):-
	supprimer(X, Q, [H|L2]).