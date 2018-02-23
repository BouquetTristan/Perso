#include<stdio.h>
#include<stdlib.h>

#include "arbre.h"
#include "abr.h"


t_arbre init_arbre()
{
	int val;
	printf("Entrez le premier évènement (date) : ");
	scanf("%i", &val);

	char texte[T];
	printf("Entrez le premier évènement (description) : ");
	scanf("%s", texte);

	return creer_arbre( val, texte, NULL, NULL, NULL);
}

void afficher(t_arbre a )
{
	afficher_arbre_infixe(a, 4);
}

void hauteur(t_arbre a )
{
	printf("La hauteur de l'arbre est de %i \n", hauteur_abr(a));
	
}

void rechercher(t_arbre a)
{	
	int val;
	printf("Choisissez une date : ");
	scanf("%i", &val);

	recherche(a, val);
}

void ajouter(t_arbre a)
{
	int val;
	printf("Entrez une date : ");
	scanf("%i", &val);

	char texte[T];
	printf("Entrez un évènement : ");
	scanf("%s", texte);

	ajout_abr(a, val, texte);
}


int main(void)
{	
	int choix;	/* Choix de l'utilisateur */

	t_arbre a =  init_arbre();

	do
	{	/* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Afficher les dates par ordre croissant\n");
        printf(" 2 - Afficher la hauteur de l'arbre\n");
		printf(" 3 - Ajouter un évènement\n");
		printf(" 4 - Chercher un évènement\n");
		printf(" 5 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1:  afficher(a); break;
			case 2:  hauteur(a); break;
			case 3:  ajouter(a); break;
			case 4:  rechercher(a); break;
			case 5:  break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
		}
	}
	while(choix!=5);
	printf("Au revoir !\n");
}