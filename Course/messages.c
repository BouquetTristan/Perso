#include <stdio.h>
#include <unistd.h>
#include <messages.h>


void affichage_arrive(int indice)
{
  switch(indice)
  {
    case 1 :
      printf("Pépito vient de finir sa course") ;
    break;
    case 2 :
      printf("Pépito est le dernier cheval en vie, il est donc déclaré vainqueur") ;
    break;
    case 3 :
      printf("Al Capone vient de déclarer Pépito vainqueur") ;
    break;
    case 4 :
      printf("Pépito vient de conquérir le public par son charisme et est donc déclaré vainqueur") ;
    break;
    case 5 :
      printf("Pépito vient enfin de terminer sa course, il ne lui aura fallut que 255 ans") ;
    break;
  }
}

void affichage_en_course(int indice)
{
  switch(indice)
  {
    case 1 :
      printf("Pépito court avec une fouge impressionnante") ;
    break;
    case 2 :
      printf("Pépito vient de glisser sur une plaque de glaçe le faisant gagner quelques mètres") ;
    break;
    case 3 :
      printf("Pépito vient de se doper pour avancer un peu plus vite") ;
    break;
    case 4 :
      printf("Pépito vient d'entamer une course en marche arrière pour corser les choses") ;
    break;
    case 5 :
      printf("Pépito court sur ses deux pattes avants") ;
    break;
  }
}

void affichage_decanille(int indice)
{
  switch(indice)
  {
    case 1 :
      printf("Pépito finit dans le fossé après avoir prit peur à la vue d'une souris") ;
    break;
    case 2 :
      printf("Pépito vient de s'endormir sur la piste") ;
    break;
    case 3 :
      printf("Pépito vient de se faire violemment insulter par le cheval d'à côté, il décide d'aller pleurer dans le vestiaire") ;
    break;
    case 4 :
      printf("Pépito vient de tomber dans un trou") ;
    break;
    case 5 :
      printf("Pépito se déclare en grève et décide d'abandonner la course") ;
    break;
  }
}

extern
void
messages_afficher_etat( const etat_coureur_t etat ) 
{
  int rdm;
  rdm = (rand() % 5)+1;
  switch( etat ) 
  {
    case ARRIVE : 
      affichage_arrive(rdm);
    break ;
    case EN_COURSE :
      affichage_en_course(rdm);
    break ;
    case DECANILLE :
      affichage_decanille(rdm);
    break ;
    default :
      printf("<inconnu (%d)>" , etat ) ;
      break ;
    }
}

static 
void
messages_afficher_type( int type )
{
  switch(type)
    {
    case PC_COURSE : 
      printf("PC_COURSE") ;
      break ;
    default :
      printf("%d" , type) ;
      break ;
    }

}
/*
 * Affichage d'un message de requete d un coureur au PC Course 
 */
extern
void
messages_afficher_requete( requete_t * const requete )
{
  
  /* Type du message */ 
  printf("\tType = ") ; messages_afficher_type(requete->type) ; printf("\n"); 

  /* Corps */
  printf("\tDossard = %d\n\n" , requete->corps.dossard ) ; 
}

/* 
 * Affichage d'un message de reponse du PC Course 
 */
extern
void
messages_afficher_reponse( reponse_t * const reponse )
{
  int i ;

  /*----------*/

  /* Corps */

  /* -- Petit commentaire rigolo sur la situation du coureur */
  printf(" Commentateur : ");  messages_afficher_etat( reponse->corps.etat ) ; printf("\n"); 

  /* -- Nombre de coureurs */
  printf("\nNombre de coureurs = %d\n" , reponse->corps.nb_coureurs );

  /* -- Entete classement */
  if( reponse->corps.nb_coureurs > 0 ) 
  {
       printf("\t*---------*----------*\n" );
       printf("\t| Dossard | Distance |\n" );
       printf("\t*---------*----------*\n" );
       /* -- Classement */
       for( i=0 ; i < reponse->corps.nb_coureurs ; i++)
       {
	    printf( "\t|  %5d  |      %3d |\n" , 
		    reponse->corps.tab_coureurs[i].dossard ,  
		    reponse->corps.tab_coureurs[i].distance );
       }
       /* -- Pied classement */
       printf("\t*---------*----------*\n\n" );
  }
}

/* 
 * Affichage du parcours de la course
 */
extern
void
messages_afficher_parcours( reponse_t * const reponse )
{
     int km ; 
     pid_t moi = getpid() ; 
     int ind_coureur  = 0 ;

     /*----------*/


     printf("-*-" ) ; for( km=DISTANCE ; km > 0; km--) printf("-") ; printf("---\n" );

     printf(" | " ) ;
     ind_coureur  = 0 ;
     km=DISTANCE ;
     while( (km > 0) && (ind_coureur < reponse->corps.nb_coureurs) )
     {
	  if( reponse->corps.tab_coureurs[ind_coureur].distance == km ) 
	  {
	       /* Il y a un coureur a cet endroit du parcours */
	       if( reponse->corps.tab_coureurs[ind_coureur].dossard == moi ) 
	       {
		    /* C'est ce processus */
		    printf("X");
	       }
	       else
	       {
		    /* C'est un autre coureur */
		    printf("O") ;
	       }
	       /* Saut des ex-aequos */
	       while(reponse->corps.tab_coureurs[ind_coureur].distance == km )
		    ind_coureur++ ;
	  }
	  else
	  {
	       /* Il n'y a pas de coureur a cet endroit */
	       printf( " " );
	  }
	  km -- ;
     }

     /* En principe, il ne reste plus de coureurs */
     while( km > 0 )
     {	  
	  printf( " " );
	  km -- ;
     }

     printf(" | \n" ) ;
     printf("-*-" ) ; for( km=DISTANCE ; km > 0; km--) printf("-") ; printf("---\n" );
}

/*
 * Initialisation de l'attente 
 */
extern
void
messages_initialiser_attente() 
{
  srandom(getpid()) ;
}

/* 
 * Attente entre 2 envois de message vers le PC Course 
 */
extern
void
messages_attendre_tour() 
{
  sleep(random()%10) ;
}

void messages_afficher_erreur( err_t cr )
{
  switch(cr)
  {
    case OK :
      printf("OK");
    break;
    case ETAT_BAD :
      printf("Mauvaise valeur de l'état du coureur");
    break;
    case ABANDON_ACK :
      printf("ACK sur abandon");
    break;
    default :
      printf("Type de compte rendu inconnu");
    break;
  }
}
