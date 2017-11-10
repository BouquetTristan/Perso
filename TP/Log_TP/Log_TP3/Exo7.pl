dupli([], []).
dupli([T|Q], [T,T|X]):- dupli(Q, X).