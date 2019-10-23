#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <signaux.h>


/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

pid_t pid_ver ;

booleen_t GAME_OVER = FAUX;

/*
 * HANDLERS
 */

void fin_de_partie(int signal)
{
	if (signal == SIG_VICTOIRE)
	{
		fprintf(stdout,"ver %i a péri mais a gagné!!\n", pid_ver);
	}
	else if (signal == SIG_MORT)
	{
		fprintf(stdout,"ver %i a juste péri!!\n", pid_ver);
	}
	else
		fprintf(stdout,"Signal %i inconnu !!\n", signal);


	GAME_OVER = VRAI;
}

int
main( int nb_arg , char * tab_arg[] )
{
	char nomprog[128] ;
	pid_t pid_aire ;

	/*----------*/

	/* 
	 * Capture des parametres 
	 */
	/* - nom du programme */
	strcpy( nomprog , tab_arg[0] );

	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <pid aire>\n", nomprog );
		exit(-1);
	}

	/* - parametres */
	pid_aire = atoi( tab_arg[1] ) ;


	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());

	pid_ver = getpid() ; 
	printf( "\n\n--- Debut ver [%d] ---\n\n" , pid_ver );

	signal(SIG_VICTOIRE, fin_de_partie);
	signal(SIG_MORT, fin_de_partie);

		while(!GAME_OVER)
		{

			sleep(1 + rand() % 4);

			fprintf(stdout, "Le ver %i demande à jouer.\n", getpid());

			if(kill(pid_aire, SIG_JOUER) != 0)
			{
				fprintf(stderr, "Erreur: Terre absente (Appelez Dieu pour qu'il répare le truc).\n");
				exit(ERREUR);
			}

		}

	printf( "\n\n--- Arret ver [%d] ---\n\n" , pid_ver );

	exit(0);
}