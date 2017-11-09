/*
Realisation d'une application C/S mettant en oeuvre le jeu de Chifoumi
--> Code client
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h> /* inet_ntoa(), */
#include <arpa/inet.h> /* gethostbyname(), */
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> /* strlen() */
#include <sys/timeb.h>
#include "common_game.h"

typedef struct game_req_s {  // Definition de la requete
   int num_play; // Numero de la partie

   int cli_choice; // pierre(0), feuille(1), ciseau(2)
   int ser_choice;

   int state_parti; // gagne, perd, egalite...

} game_req_t ;

void init_game(game_req_t play_req){
	play_req.num_play = 1;
	play_req.cli_choice = 0;
	play_req.ser_choice = 0;
	play_req.state_parti = UNKNOWN ;
}

extern int read_sizef(char * filename); // Retourne la taille du fichier en octets

int main(int argc, char ** argv){
	int sd, rc;
	char * jeu[3] = {"pierre", "feuille", "ciseau" };
	char * player[4] = {"inconnu", "client", "serveur", "egalité"};
	struct sockaddr_in localAddr, servAddr;
	struct hostent *h;
	
	game_req_t play_req;
	int choice;
	char line[MAX_MSG];
	
	// Verification du nombre d'arguments
	if(argc<1){
		printf("usage: %s <server>\n",argv[0]);
		exit (1);
	}
	
	h = gethostbyname(argv[1]); // Renvoie d'une structure de type "hostent" pour l'hote
	
	if(h == NULL){
		printf("%s: unknow host '%s'\n",argv[0],argv[1]);
		exit(1);
	}
	
	// Affectation des valeurs aux champs de la structure
	servAddr.sin_family = h->h_addrtype;
	memcpy((char*) &servAddr.sin_addr.s_addr, h->h_addr_list[0],h->h_length);
	servAddr.sin_port = htons(SERVER_PORT);
	
	//Creaction de la socket
	sd = socket(AF_INET, SOCK_STREAM,0);
	if(sd<0){
		perror("cannot open socket");
		exit(1);
	}
	
	// Affectation des valeurs aux champs de la structure
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);
	
	// Affection de l'addresse indiquee a la socket
	rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
	if(rc<0){
		printf("%s: cannot bind port TCP %u\n",argv[0],SERVER_PORT);
		perror("error");
		exit(1);
	}
	
	// Connexion au serveur
	rc = connect(sd,(struct sockaddr *) &servAddr, sizeof(servAddr)); 
	if(rc<0){
		perror("error");
		exit(1);
	}
	
	// Initialisation de la structure du jeu
	init_game(play_req);

	
	int cpt = 1 ; // Compteur de parti
	while(cpt<=3){
		// Choix du client
		printf("jeu n°%d : choose PIERRE(0), FEUILLE(1), CISEAU(2) ? \n", cpt);
		scanf("%d", &choice);
		while((choice<0)&&(choice>2)){
			printf("Erreur : le nombre doit etre compris entre 0 et 2\n");
			scanf("%d", &choice);
		}
		play_req.cli_choice = choice;
		play_req.num_play = cpt;

		// Envoi et receetpion de l'etat du jeu comprenant le choix du client et celui du serveur en reception
		rc = send(sd, &play_req, sizeof(play_req), 0);
		memset(line, 0x0, MAX_MSG);
		rc = recv(sd, line, MAX_MSG, 0);
		printf("%s\n", line);
		
		memset(line, 0x0, MAX_MSG);
		if(cpt==3){
			rc = recv(sd, line, MAX_MSG, 0);
			printf("%s\n", line);
		}
		cpt++;
	}		
	
	close(sd);
	return 0;
}

