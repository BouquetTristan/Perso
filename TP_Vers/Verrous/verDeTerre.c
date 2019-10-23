#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>

int
main( int nb_arg , char * tab_arg[] )
{

     /* Parametres */
     char fich_terrain[128] ;
     char nomprog[128], fichier_vers[] = "mes_vers" ;
     int noerr = 0;

     int nb_voisin, voisin_choisi;

     booleen_t etat_ver = VRAI;

     int dimx, dimy;
     coord_t * futur_tete, nouvelle_tete;
     case_t marque = CASE_LIBRE ;

     struct flock verrou;

     vers_t * liste_des_vers = vers_new();

     /*----------*/

     /* Initialisation du verrou */

     verrou.l_type = F_WRLCK;
     verrou.l_whence = 0;
     verrou.l_start = 0;
     verrou.l_len = CASE_TAILLE;

     /*----------------------------*/

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

     printf( "\n\n%s : ----- Debut du ver %c (%d) -----\n\n ", nomprog , marque , getpid() );

          //Initialisation du terrain et de la liste des vers
          int fichier;
          int fichier_des_vers;

          fichier = open(fich_terrain, O_RDWR, 0644);
          fichier_des_vers = open(fichier_vers, O_RDWR, 0644);

          //Lecture des dimensions du terrain
          terrain_dim_lire(fichier, &dimx, &dimy);

          //Création d'un ver
          ver_t ver;
          ver_marque_set(&ver, marque);


          //Initialisation du ver
          /* Pose du verrou en écriture sur le fichier du terrain */
          verrou.l_start = 0;
          verrou.l_len = 0;

          fcntl(fichier, F_SETLKW, &verrou);
               if((noerr = jeu_ver_initialiser(fichier, dimx, dimy, &ver)))
                    printf("ERREUR");
          /* Levé du verrou sur le fichier */
          verrou.l_type = F_UNLCK;

          fcntl(fichier, F_SETLKW, &verrou);


          /* Pose du verrou en écriture sur la liste des vers*/
          verrou.l_type = F_WRLCK;
          verrou.l_start = 0;
          verrou.l_len = 0;

          fcntl(fichier_des_vers, F_SETLKW, &verrou);

               vers_fichier_load(&liste_des_vers, fichier_vers);
               //Ajout d'un ver dans la liste des vers
               vers_ver_add(liste_des_vers, ver);

               //Sauvegarde de la liste des vers
               vers_fichier_save(liste_des_vers, fichier_vers);

          /* Levé du verrou sur le fichier */
          verrou.l_type = F_UNLCK;

          fcntl(fichier_des_vers, F_SETLKW, &verrou);


          //Tant que le ver est vivant
          while(etat_ver)
          {
               
                    /*Comportement d'un ver*/
                    /* Pose du verrou en écriture sur le fichier du terrain */
                    verrou.l_type = F_RDLCK;
                    verrou.l_start = 0;
                    verrou.l_len = 0;

                    fcntl(fichier, F_SETLKW, &verrou);

                         /*Avancement du ver*/
                         terrain_voisins_rechercher( fichier, ver_tete_get(ver), &futur_tete, &nb_voisin ) ;  
                         terrain_case_libre_rechercher( fichier, futur_tete, nb_voisin, &voisin_choisi );

                    /* Levé du verrou sur le fichier */
                    verrou.l_type = F_UNLCK;

                    fcntl(fichier, F_SETLKW, &verrou);


                    nouvelle_tete = futur_tete[voisin_choisi];

                    if (voisin_choisi != -1)
                    {
                         /* Le ver peut se déplacer */ 

                         /* Pose du verrou en écriture sur le fichier du terrain */
                         verrou.l_type = F_WRLCK;
                         verrou.l_start = coord_pos_get(nouvelle_tete)*CASE_TAILLE;
                         verrou.l_len = CASE_TAILLE;

                         fcntl(fichier, F_SETLKW, &verrou);

                              terrain_marque_ecrire( fichier, nouvelle_tete, marque) ; 


                         /* Levé du verrou sur le fichier */
                         verrou.l_type = F_UNLCK;

                         fcntl(fichier, F_SETLKW, &verrou);
                    }

      
                    /*Mort du ver*/
                    else
                    {
                         /* Le ver doit mourir */


                         /* Pose du verrou en écriture sur la liste des vers */
                         verrou.l_type = F_WRLCK; 
                         verrou.l_start = 0;
                         verrou.l_len = 0;

                         fcntl(fichier_des_vers, F_SETLKW, &verrou);

                              // Vérification de la condition de victoire
                              vers_fichier_load( &liste_des_vers, fichier_vers );

                              vers_ver_del(liste_des_vers, vers_marque_seek(liste_des_vers, ver_marque_get(ver)));
                              printf("mort du ver %c", ver_marque_get(ver));

                              //Sauvegarde de la liste des vers
                              vers_fichier_save(liste_des_vers, fichier_vers);

                              etat_ver = 0;

                         /* Levé du verrou sur la liste des vers */
                         verrou.l_type = F_UNLCK;

                         fcntl(fichier_des_vers, F_SETLKW, &verrou);

                    }


               /***********************/
               //Attends parfois entre 1 et 4 secondes pour changer à nouveau de position
               srand(getpid());
               int a = rand()%4+1; 
               //printf("%c : %i\n", marque, a);
               sleep(a);
          }

     verrou.l_type = F_RDLCK;
     fcntl(fichier_des_vers, F_SETLKW, &verrou);

          vers_ver_del(liste_des_vers, 0);

          //Sauvegarde de la liste des vers
          vers_fichier_save(liste_des_vers, fichier_vers);

     /* Levé du verrou sur le fichier */
     verrou.l_type = F_UNLCK;

     fcntl(fichier_des_vers, F_SETLKW, &verrou);

     close(fichier);

     printf( "\n\n%s : ----- Fin du ver %c (%d) -----\n\n ", nomprog , marque , getpid() );

     exit(0);
}
