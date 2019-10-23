#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>
#include <signaux.h>

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */
char Nom_Prog[256] ;

char fich_terrain[128] ;
int fd_terrain;

booleen_t GAME_OVER = FAUX;

/* Initialisation des vers */
ver_t  ver;
vers_t * liste_vers = (vers_t *) NULL;




void afficher_la_Terre()
{
	/* Affichage de la Terre*/
	/* On affiche le terrain uniquement quand on fait un traitement sur la Terre */
	if( (fd_terrain = open( fich_terrain, O_RDWR, 0644)) == ERREUR)
	{
		fprintf(stderr, "%s: Erreur lors de l'ouverture de la Terre %s, merci de contacter Dieu.\n", Nom_Prog, fich_terrain);
		exit(ERREUR);
	}

	terrain_afficher(fd_terrain);
}


/*
 * HANDLER
 */

void jouer(int signal, siginfo_t * siginfo)
{

	int dimx, dimy;
	int indice_ver;
	pid_t pid_ver = siginfo->si_pid;

	int nb_voisin, voisin_choisi;
	coord_t * futur_tete, nouvelle_tete;

	//ver_pid_set(&ver, pid_ver);
	
	

	/* Si le pid reçu n'est pas dans notre liste des vers, on initialise un nouveau ver */
	if((indice_ver = vers_pid_seek(liste_vers, pid_ver)) == -1 )
	{
		terrain_dim_lire(fd_terrain, &dimx, &dimy);
		ver_marque_set(&ver, 'A'+ vers_nb_get(liste_vers));
		ver_pid_set(&ver, pid_ver);
		/* On ajoute un ver dans la liste et on stocke le pid */
		vers_ver_add(liste_vers, ver);
		/* On pose le ver sur Terre */
		jeu_ver_initialiser(fd_terrain, dimx, dimy, &ver);		
			/* On affiche la Terre */
			afficher_la_Terre();
	}

	/* Sinon on essaye de bouger le ver */
	else
	{
		ver = vers_ver_get(liste_vers, indice_ver);
		/* Recherche de case disponible autour du ver */
		terrain_voisins_rechercher( fd_terrain, ver_tete_get(ver), &futur_tete, &nb_voisin ) ;  
		terrain_case_libre_rechercher( fd_terrain, futur_tete, nb_voisin, &voisin_choisi );

		/* Si le ver peut bouger */
		if(voisin_choisi != -1)
		{
			/* On fait bouger le ver */
			nouvelle_tete = futur_tete[voisin_choisi];
			terrain_marque_ecrire( fd_terrain, nouvelle_tete, ver_marque_get(ver)) ; 
			ver_tete_set(&ver, nouvelle_tete);
			vers_ver_set(liste_vers, indice_ver, ver);
			/* On affiche la Terre */
			afficher_la_Terre();
		}

		/* Sinon */
		else
		{
			/* Envoie du signal de mort au ver */
			/* C'est le ver victorieux*/
			if(vers_nb_get(liste_vers) == 1)
			{
				kill(pid_ver, SIG_VICTOIRE);
				GAME_OVER = VRAI;
				fprintf(stdout, "Le vainqueur est %c [%i] .\n", ver_marque_get(ver), pid_ver);
			}
			/* C'est un ver lambda*/
			else
			{
				kill(pid_ver, SIG_MORT);
			}
			/* Suppression du ver dans la liste */
			vers_ver_del(liste_vers, vers_marque_seek(liste_vers,ver_marque_get(ver)));
		}
	}
}

int
main( int nb_arg , char * tab_arg[] )
{
	
	pid_t pid_aire ; 

	struct sigaction requete_du_joueur;

	liste_vers = vers_new();

	/*----------*/

	/* 
	 * Capture des parametres 
	 */
	strcpy( Nom_Prog , tab_arg[0] );

	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <fichier terrain>\n", Nom_Prog );
		exit(-1);
	}

	strcpy( fich_terrain , tab_arg[1] );
	pid_aire = getpid() ; 

	/* Affichage du pid pour les processus verDeTerre */
	printf( "\n\t--------------------------\n") ; 
	printf(   "\t- pid de la Terre = %d -\n", pid_aire ) ; 
	printf(   "\t--------------------------\n\n") ; 

	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)pid_aire);

	/*----------*/

	/* Initialisation de la partie */
		/* On vide la liste des vers */
		/* On met notre condition de victoire à false */ 

	requete_du_joueur.sa_sigaction = jouer;
	requete_du_joueur.sa_flags = SA_SIGINFO; /*pid de l'envoyeur de la requete*/
	sigemptyset(&requete_du_joueur.sa_mask);

	sigaction(SIG_JOUER, &requete_du_joueur, NULL);


	afficher_la_Terre();

	printf("\n\t------ Début du jeu ------\n\n");

	fd_terrain = open(fich_terrain, 0666);

	while(!GAME_OVER)
	{

		pause();
	}

	vers_destroy(&liste_vers);

	printf("\n\n\t----- %s : Fin du jeu -----\n\n" , Nom_Prog );

	exit(0);
}