#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>

long int derniere_modif;


int check_modif(char * nom_fic)
{
	struct stat buff;
	stat(nom_fic, &buff);

	if(derniere_modif < buff.st_mtime)
	{
		derniere_modif = buff.st_mtime;
		return 1;
	}
	else
		return 0;
}

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
	/* Parametres */
	char fich_terrain[128] ;
	char nomprog[256] ;
	char fichier_vers[] = "mes_vers" ;

	FILE * create_fich_vers;

	int fd_terrain;
	int fichier_des_vers; 

	int nb_ver_vivant = 0;

	booleen_t GAME_OVER = FAUX;

	struct flock verrou;

	vers_t * liste_des_vers = vers_new();
	ver_t ver_gagnant;

	/*----------*/


	/* Initialisation du verrou */

	verrou.l_whence = 0;
	verrou.l_start = 0;
	verrou.l_len = 0;

	/*----------------------------*/

	/* Capture des parametres */
	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <fichier terrain>\n", tab_arg[0] );
		exit(-1);
	}

	strcpy( nomprog , tab_arg[0] );
	strcpy( fich_terrain , tab_arg[1] );


	if(access(fichier_vers, F_OK) == -1)
	{
		create_fich_vers = fopen(fichier_vers, "w");
		fclose(create_fich_vers);
	}



	printf("\n%s : ----- Debut de l'affichage du terrain ----- \n", nomprog );


	/* Ouverture du fichier de terrain et du fichier de la liste des vers */
	if((fd_terrain = open(fich_terrain,O_RDWR,0644)) == -1) 
	{
		fprintf(stderr,"%s : Problème d'ouverture sur le fichier \"%s\"\n",nomprog,fich_terrain);
		exit(-1);
	}

	if((fichier_des_vers = open(fichier_vers,O_RDWR,0644)) == -1) 
	{
		fprintf(stderr,"%s : Problème d'ouverture sur le fichier \"%s\"\n",nomprog,fichier_vers);
		exit(-1);
	}
	/* ------------------------------------------------------------------ */

	verrou.l_type = F_RDLCK;
	fcntl(fichier_des_vers, F_SETLKW, &verrou);

		vers_fichier_load( &liste_des_vers, fichier_vers ); 

	/* Levé du verrou sur le fichier */
	verrou.l_type = F_UNLCK;

	fcntl(fichier_des_vers, F_SETLKW, &verrou);


	nb_ver_vivant = vers_nb_get(liste_des_vers);


	/* Destruction des vers qui seraient restés dans la liste */
	while(vers_nb_get(liste_des_vers) != 0)
	{
		verrou.l_type = F_RDLCK;
		fcntl(fichier_des_vers, F_SETLKW, &verrou);

			vers_ver_del(liste_des_vers, 0);


			//Sauvegarde de la liste des vers
			vers_fichier_save(liste_des_vers, fichier_vers);

		/* Levé du verrou sur le fichier */
		verrou.l_type = F_UNLCK;

		fcntl(fichier_des_vers, F_SETLKW, &verrou);
	}
	printf("Erreur, Destruction de tous les vers\n");


	system("clear");
	terrain_afficher(fd_terrain);
	printf("La partie commence quand deux vers sont présents\n");


	/* Attend qu'il y ai au moins deux vers dans la liste avant de commencer la partie */
	while(nb_ver_vivant < 2)
	{

		/* Pose du verrou sur le fichier */ 
		verrou.l_type = F_RDLCK;
		fcntl(fichier_des_vers, F_SETLKW, &verrou);

			vers_fichier_load( &liste_des_vers, fichier_vers ); 

		/* Levé du verrou sur le fichier */
		verrou.l_type = F_UNLCK;

		fcntl(fichier_des_vers, F_SETLKW, &verrou);


		nb_ver_vivant = vers_nb_get(liste_des_vers);

		//printf("nb vers : %i\n", nb_ver_vivant);
	}
	/* -------------------------------------------------------------------------- */

	while(!GAME_OVER) 
	{

		/* Pose du verrou sur le fichier */ 
		verrou.l_type = F_RDLCK;
		fcntl(fichier_des_vers, F_SETLKW, &verrou);

			vers_fichier_load( &liste_des_vers, fichier_vers );

		/* Levé du verrou sur le fichier */
		verrou.l_type = F_UNLCK;

		fcntl(fichier_des_vers, F_SETLKW, &verrou);



		/* Check si un ver a gagné */
		if (vers_nb_get(liste_des_vers) < 2)
			GAME_OVER = VRAI;

		if(check_modif(fich_terrain))
		{
			system("clear");
			vers_printf(liste_des_vers);
			terrain_afficher(fd_terrain);
		}
	}


	system("clear");
	printf("\n%s : --- Arret de l'affichage du terrain ---\n", nomprog );
	vers_printf(liste_des_vers);
	terrain_afficher(fd_terrain);

	if (vers_nb_get(liste_des_vers) == 0)
		printf("Les derniers vers sont morts en même temps, il n'y a pas de vainqueur\n");
	else
	{
		ver_gagnant = vers_ver_get(liste_des_vers, 0);
		printf("Victoire du ver %c qui est le dernier en vie\n", ver_marque_get(ver_gagnant));
	}


	/* Destruction des vers qui seraient restés dans la liste */
	while(vers_nb_get(liste_des_vers) != 0)
	{
		verrou.l_type = F_RDLCK;
		fcntl(fichier_des_vers, F_SETLKW, &verrou);

			vers_ver_del(liste_des_vers, 0);


			//Sauvegarde de la liste des vers
			vers_fichier_save(liste_des_vers, fichier_vers);

		/* Levé du verrou sur le fichier */
		verrou.l_type = F_UNLCK;

		fcntl(fichier_des_vers, F_SETLKW, &verrou);
	}

	vers_destroy(&liste_des_vers);
	close(fd_terrain);
	close(fichier_des_vers);


	exit(0);
}
