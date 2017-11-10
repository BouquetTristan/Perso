my_last([Y,_|[]], Y).
my_last([_|Q], Y):- my_last(Q,Y).
