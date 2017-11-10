impair([_|[]]).
impair([_,_|Q]):- impair(Q).