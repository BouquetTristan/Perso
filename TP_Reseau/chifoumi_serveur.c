/*
Realisation d'une application C/S mettant en oeuvre le jeu de Chifoumi
--> Code serveur
*/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#include "common_game.h"

typedef struct game_req_s {  // Definition de la requete
   int num_play; //Numero de la partie

   int cli_choice; // pierre(0), feuille(1), ciseau(2)
   int ser_choice;

   int state_parti; // gagne, perd, egalite...

} game_req_t ;


int main (int argc, char * argv[])
{	
	if(argc > 1){
		fprintf(stdout, "erreur, le programme \"%s\" ne prends pas d'arguments", argv[0]);
		return ERROR;	
	}
	int sd, newSd, n; 
	socklen_t cliLen ;
	
	game_req_t play_req;
	int nbr; // pierre 0, feuille 1, ou ciseau 2	
	 
	// Nombre de parties gagnees
	int win_client = 0;
	int win_serveur = 0;

	char choice; 
	char * player[4] = {"inconnu", "client", "serveur", "egalité"};
	char * jeu[3] = {"pierre", "feuille", "ciseau" };

	struct sockaddr_in cliAddr, servAddr ;
	char line[MAX_MSG] ;
	
	// Creaction de la socket
	sd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sd < 0)
	{
		perror("Cannot open socket !") ;
		return ERROR ;
	}
	
	// Boucle permettant d'eviter une erreur dans le cas ou l'adresse est deja prise
	 int optval = 1;
 	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1) { 
    		perror("setsockopt");
    		exit(EXIT_FAILURE);
  	}

	// Affectation des valeurs aux champs de la structure
	servAddr.sin_family = AF_INET ;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
	servAddr.sin_port = htons(SERVER_PORT) ;
	
	if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
	{
		perror("Cannot open socket !") ;
		return ERROR ;
	}
	
	listen(sd, 5) ;
	
	while(1)
	{
		printf("%s : waiting for data on port TCP %u\n", argv[0], SERVER_PORT) ;
		cliLen = sizeof(cliAddr) ;
		// Acceptation de la connexion, identification du client
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen) ;
		printf("cliaddr.sin_family : %d\n", cliAddr.sin_family);
		printf("cliaddr.sin_addr.s_addr : %s\n", inet_ntoa(cliAddr.sin_addr));
		printf("cliaddr.sin_port : %d\n", cliAddr.sin_port);

		if(newSd < 0)
		{
			perror("Cannot accept connection !") ;
			return ERROR ;
		}
		
		// Initialisation de la chaine de caracteres
		memset(line, 0x0, MAX_MSG) ;
		
		// Reception de la requete
		int cpt = 1; // Compteur de parti
		while(cpt <= 3){

			if((n = recv(newSd, &play_req, sizeof(game_req_t), 0)) > 0){
				nbr = rand()%3 ; // choix du serveur aleatoire
				play_req.ser_choice = nbr ;

				// pour eviter d'analyser tout les cas on suppose que client gagne
				win_client++;
				play_req.state_parti = CLIENT;
	
				if(play_req.cli_choice == nbr){ // Si le client et le serveur ont fait le meme choix
					win_client--;
					play_req.state_parti = EQUALITY;			
				}
	
				if((play_req.cli_choice == P)&&(nbr==F)){ // Si le client choisi P et le serveur F
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;			
				}
	
				if((play_req.cli_choice == F)&&(nbr == C)){ /* Si le client choisi F et le serveur C */
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;				
				}
				if((play_req.cli_choice == C)&&(nbr == P)){ /* Si le client choisi C et le serveur P */
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;		
				}

				memset(line, 0x0, MAX_MSG); 
				sprintf(line, "jeu n°%d : %s \" %s\" :: %s \"%s\" : Resultat %s gagne\n", play_req.num_play, player[CLIENT], jeu[play_req.cli_choice], player[SERVER], jeu[play_req.ser_choice], player[play_req.state_parti]);
				n = send(newSd, line, MAX_MSG, 0); // Envoi du resultat
					
				memset(line, 0x0, MAX_MSG);

				// Fin de partie :
				if((cpt % 3) == 0){
					if(win_client > win_serveur){						
						play_req.state_parti = CLIENT;
					}
					if(win_serveur > win_client){
						play_req.state_parti = SERVER;				
					}
					else if(win_serveur == win_client) play_req.state_parti = EQUALITY;
					
					sprintf(line, "%s a gagné le plus de manche\n", player[play_req.state_parti]);			
					n = send(newSd, line, MAX_MSG, 0);		
				}
				
			} 
			
			if(n == 0){
				perror("Connection closed by the Client\n");
				return ERROR;		
			}
			
			if(n < 0){
				perror("Cannot receive data\n");
				return ERROR;		
			}
			cpt++;
		}
	}/*while(1)*/
	close(sd);
	close(newSd);
}


