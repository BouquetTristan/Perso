subset([], [_|_]).

subset([T|Q], [Y|Q2]):- find([T|Q], [Y|Q2], [Y|Q2]).

subset([T|Q], [T|Q2]):- subset(Q, [T|Q2]).
subset([T|Q], [Q2|T]):- subset(Q, [Q2|T]).

find([T|Q], [_|Q2], C):- find([T|Q], Q2, C).
find([T|Q], [T|_], C):- subset(Q, C).