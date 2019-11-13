#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "messages.h"

int idMsg;

void abandon(int signal)
{
	requete_t requete;
	ack_t reponse;

	requete.corps.dossard = getpid();
	requete.type = PC_COURSE;
	requete.corps.etat = ABANDON;

	msgsnd(idMsg, &requete, sizeof(corps_requete_t), 0);
	msgrcv(idMsg, &reponse, sizeof(ack_t), getpid(), 0);

	messages_afficher_erreur(reponse.ack);
	printf("\n\n----- Interruption de la course -----\n");

	exit(2);
}



int main(int argc, char * argv[]) 
{
	if(argc != 2) 
	{
		printf("%s : <cle externe>\n", argv[0]);
		exit(-1);
	}
	
	key_t cleExterne = atoi(argv[1]);

	/* Abandon */
	struct sigaction action;
	action.sa_handler = abandon;
	action.sa_flags = 0;

	sigaction(SIGINT,&action, NULL);
	
	/* Création requête */
	requete_t requete;
	requete.corps.dossard = getpid();
	requete.type = PC_COURSE;
	requete.corps.etat = EN_COURSE;
	
	/* Création réponse */
	reponse_t reponse;
	reponse.corps.etat = EN_COURSE;
	
	idMsg = msgget(cleExterne, 0);
	
	messages_initialiser_attente();
	
	while(reponse.corps.etat == EN_COURSE) 
	{
		msgsnd(idMsg, &requete, sizeof(corps_requete_t), 0);
	
		msgrcv(idMsg, &reponse, sizeof(corps_reponse_t), getpid(), 0);
	
		/* Affichage de l'etat d'un coureur */
		//messages_afficher_etat(reponse.corps.etat) ;

		/* Affichage d'un message de requete d'un coureur au PC Course */
		messages_afficher_requete(&requete);

		system("clear");

		/* Affichage d'un message de reponse du PC Course */
		messages_afficher_reponse(&reponse);

		/* Affichage du parcours de la course */
		messages_afficher_parcours(&reponse);

		/* Attente entre 2 envois de message vers le PC Course */
		messages_attendre_tour();
	}

	switch( reponse.corps.etat ) 
	{

		case ARRIVE :
			printf("\n\tLe Dossard %li est arrivé\n",reponse.type);
		break ;

		case DECANILLE :
			printf("\n\tLe Dossard %li s'est fait décaniller\n",reponse.type) ;
			break ;

		default :
			printf("\n\tUn bug dans la matrice\n") ;
		break ;
	}
}