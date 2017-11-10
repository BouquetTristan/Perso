element(Y, [Y|_], 1).
element(Res, [_|Q], L):- L1 is L-1,
					element(Res, Q, L1).