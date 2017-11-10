moyenne([], _, Moyenne, Moyenne).

moyenne([H|T], 0, _, Moyenne):-
	moyenne(T, 1, H, Moyenne).

moyenne([H|T], Len, Som, Moyenne):-
	Len1 is Len + 1,
	Som1 is (Som*Len + H)/Len1,
	moyenne(T, Len1, Som1, Moyenne).

moyenne(List, Moyenne):-
	moyenne(List, 0, 0, Moyenne).