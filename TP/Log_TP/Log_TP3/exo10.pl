add([],_,[]).
add([X|T],N,[B|Y]):- B is X+N , add(T,N,Y).