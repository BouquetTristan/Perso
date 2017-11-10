replique([], _, _, []).

replique([_|T], 0, Y, List):-
	replique(T, Y, Y, List).

replique([H|T], X, Y, List):-
	X1 is X-1,
	replique([H|T], X1, Y, [H|List]).
