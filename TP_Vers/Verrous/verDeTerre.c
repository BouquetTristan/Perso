#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>

int
main( int nb_arg , char * tab_arg[] )
{

     /* Parametres */
     char fich_terrain[128] ;
     case_t marque = CASE_LIBRE ;
     char nomprog[128] ;
     int dimx, dimy;
     int noerr = 0;

     /*----------*/

     /* Capture des parametres */
     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <marque>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     if( strlen(tab_arg[2]) !=1 ) 
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   tab_arg[0] , tab_arg[2] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     marque = tab_arg[2][0] ;


   /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     printf( "\n\n%s : ----- Debut du ver %c (%d) -----\n\n ", 
	     nomprog , marque , getpid() );

          //Initialisation du terrain
          int nb_vers = 0;
          int fichier;

          fichier = open(fich_terrain, O_RDWR, 0644);

          //Lecture des dimensions du terrain
          terrain_dim_lire(fichier, &dimx, &dimy);

          //Création d'un ver
          ver_t ver;
          ver_marque_set(&ver, marque);

          //Initialisation du ver
          //A encapsuler dans un verrou
               if((noerr = jeu_ver_initialiser(fichier, dimx, dimy, &ver)))
                    printf("ERREUR");
          /* Test */ //ver_printf(ver);



     printf( "\n\n%s : ----- Fin du ver %c (%d) -----\n\n ", 
	     nomprog , marque , getpid() );

     exit(0);
}
