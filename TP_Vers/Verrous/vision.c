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



int check_modif(char * nom_fic)
{
  struct stat buff;
  stat(nom_fic, &buff);

  return ((time(NULL) - buff.st_mtime) < 1);
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
  int fd_terrain;
  
     /*----------*/

  /* Capture des parametres */
  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <fichier terrain>\n", 
	       tab_arg[0] );
      exit(-1);
    }

  strcpy( nomprog , tab_arg[0] );
  strcpy( fich_terrain , tab_arg[1] );


  printf("\n%s : ----- Debut de l'affichage du terrain ----- \n", nomprog );


    if((fd_terrain = open(fich_terrain,O_RDWR,0644)) == -1) 
    {
      fprintf(stderr,"%s : Problème d'ouverture sur le fichier \"%s\"\n",nomprog,fich_terrain);
      exit(-1);
    }
    terrain_afficher(fd_terrain);

    while(1) //Remplacer 1 par GAME_OVER
    {
      if(check_modif(fich_terrain))
      {
        
        terrain_afficher(fd_terrain);
      }
      /* Test modification
      else
        printf("Pas de modification\n");
      */
    }
    
    close(fd_terrain);
    
  printf("\n%s : --- Arret de l'affichage du terrain ---\n", nomprog );

  exit(0);
}
