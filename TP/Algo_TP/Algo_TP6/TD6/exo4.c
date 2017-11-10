All = pile.o file.o exo.o

pile.o : pile.c
	gcc -c pile.c -g
file.o : file.c
	gcc -c file.c -g
exo.o : exo.c
	gcc -c exo.c -g

exe : $(All)
	gcc -o exe $(All) 