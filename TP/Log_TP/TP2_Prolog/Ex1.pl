longueur([], Longueur, Longueur).

longueur([_|T], Len, Longueur):-
	Len1 is Len + 1,
	longueur(T, Len1, Longueur).

longueur(List, Longueur):-
	longueur(List, 0, Longueur).