add([],0).
add([X|T],B):- add(T,N), B is N+X.