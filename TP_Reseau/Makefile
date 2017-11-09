client : chifoumi_client.c common_game.h
	gcc -Wall chifoumi_client.c common_game.h -o client

serveur : chifoumi_serveur.c common_game.h
	gcc -Wall chifoumi_serveur.c common_game.h -o serveur

all: 	client
	@echo  "\n--> Executables client et serveur générés\n"

clean :
	@echo  "\n--> Suppression des executables"
	rm -f client
	rm -f serveur
	@echo  "[OK]\n"
