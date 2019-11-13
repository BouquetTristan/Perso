# MAKEFILE pour Cours sur les files de messages

top_dir = .

fich_obj_coureur = coureur.o messages.o

GCCOBJ = gcc -c 
GCCLNK = gcc 

coureur : $(fich_obj_coureur)
	$(GCCLNK) $(fich_obj_coureur) $(opt) -o coureur -I ./

	
coureur.o : coureur.c 
	$(GCCOBJ) $(opt) coureur.c -o coureur.o -I ./

	
messages.o : messages.c messages.h 
	$(GCCOBJ) $(opt) messages.c -o messages.o -I ./

clean : 
	rm -f *.o 

all :   coureur 

tags :
	etags *.c 
