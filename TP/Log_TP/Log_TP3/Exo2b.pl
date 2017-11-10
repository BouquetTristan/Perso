element([_|[]], X).
element([_|Q], Res):- Res1 is Res+1,
				element(Q, Res1).