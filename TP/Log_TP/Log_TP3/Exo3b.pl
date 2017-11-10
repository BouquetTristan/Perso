inverse(Res, [], Res).
inverse(Res, [T|Q], Acc):- inverse(Res, Q, [T|Acc]).

palindrome(P):- inverse(P, P, []).