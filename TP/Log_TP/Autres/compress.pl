compress([], []).
compress([T],[T]).
compress([T,T|Q], Res):- compress([T|Q], Res).
compress([T,U|Q], [T|Res]):- T \= U, compress([U|Q], Res).
