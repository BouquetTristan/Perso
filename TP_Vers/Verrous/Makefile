# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

#
# Object files
#

fich_obj_verDeTerre = verDeTerre.o \
	$(commun_dir)/jeu.o $(commun_dir)/coord.o \
	$(terrain_dir)/terrain.o \
	$(vers_dir)/vers.o \
	$(vers_dir)/ver.o


fich_obj_vision = vision.o \
	$(commun_dir)/coord.o \
	$(terrain_dir)/terrain.o \
	$(vers_dir)/vers.o \
	$(vers_dir)/ver.o

#
#-------- Mains ---------------
#

BIN = verDeTerre vision

verDeTerre : $(fich_obj_verDeTerre)
	$(CCLNK) $(fich_obj_verDeTerre) $(FLAGS) -o verDeTerre -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

verDeTerre.o : verDeTerre.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h $(commun_dir)/jeu.h $(vers_dir)/vers.h
	$(CCOBJ) $(FLAGS) verDeTerre.c -o verDeTerre.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

vision : $(fich_obj_vision)
	$(CCLNK) $(fich_obj_vision) $(FLAGS) -o vision -I$(commun_dir) -I$(terrain_dir)

vision.o : vision.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h $(vers_dir)/vers.h
	$(CCOBJ) $(FLAGS) vision.c -o vision.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

#
# --- Tests ---
#


#
#-------- Modules -------------
#
$(commun_dir)/jeu.o :
	cd $(commun_dir) ; make -f Makefile jeu.o

$(commun_dir)/coord.o :
	cd $(commun_dir) ; make -f Makefile coord.o

$(terrain_dir)/terrain.o :
	cd $(terrain_dir) ; make -f Makefile terrain.o

$(vers_dir)/vers.o :
	cd $(vers_dir) ; make -f Makefile vers.o

$(vers_dir)/ver.o :
	cd $(vers_dir) ; make -f Makefile ver.o

#
#-------- Headers -------------
#

#
#-------- Clean objects -------
#

clean :
	- rm $(BIN)
	- rm  *.o  *~


#
#-------- All executables -------
#

all : verDeTerre vision

#
#-------- All tests -------
#

all-test :
