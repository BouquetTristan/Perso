my_last([Y|[]], Y).
my_last([_|Q], Y):- my_last(Q,Y).
