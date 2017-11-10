#include "liste_ptr.h"
#include <stdio.h>

/* Programme principal */

int saisir()
{
	int nb;

	printf("Choisissez un nombre : ");
	scanf("%i", &nb);
	
	return nb;

}

void afficher()
{
	int elem;

	en_tete();
	valeur_elt(&elem);

	printf("Liste : ");

	while(!hors_liste())
	{
		printf("%i ", elem);
		suivant();
		valeur_elt(&elem);
	}
	printf("\n");
}

void inserer()
{
	int elem;
	int nouv = saisir();

	en_queue();
	valeur_elt(&elem);
	if(elem < nouv)
		ajout_droit(nouv);
	else
	{

		en_tete();
		valeur_elt(&elem);
		
		if(elem > nouv)
			ajout_gauche(nouv);
		else
		{
			while(!hors_liste() && elem < nouv)
			{	
				
				suivant();
				valeur_elt(&elem);
			}
		
			ajout_gauche(nouv);
		}
	}
}

void afficher_multiples()
{
	int mult = saisir();
	int elem;

	printf("Liste multiple : ");
	en_tete();
	valeur_elt(&elem);
	
	while(!hors_liste())
	{
		if(elem%mult == 0)
			printf("%i ", elem);

		suivant();
		valeur_elt(&elem);
	}
	printf("\n");
}

void compter()
{
	int elem;
	int comp = saisir();
	int i = 0;

	en_tete();
	valeur_elt(&elem);

	while(!hors_liste())
	{
		if(elem == comp)
			i++;
		
		suivant();
		valeur_elt(&elem);
	}

	printf("Nombre de répétition de %i : %i\n", comp, i);
}

void supprimer()
{
	int elem;
	int supp = saisir();

	en_tete();
	valeur_elt(&elem);

	while(!hors_liste())
	{
		if(elem == supp)
			oter_elt();
		
		suivant();
		valeur_elt(&elem);
	}
}

void vider_liste()
{
	while(!liste_vide())
	{
		oter_elt();
		en_tete();
	}
}

void prensenter()
{
	printf("Cette fonction est en cours de construction\n");
}

void fibonacci()
{
	printf("Cette fonction est en cours de construction\n");
}
int main(void)
{
	int choix;

	/* Initialisation de la liste d’entiers */
	init_liste();

	do
	/* Affichage du menu et saisie du choix */
	{
		printf("\nMenu :\n");
		printf(" 1- Insérer une valeur\n");
		printf(" 2- Afficher les multiples\n");
		printf(" 3- Compter les occurrences d’une valeur\n");
		printf(" 4- Supprimer une valeur\n");
		printf(" 5- Vider la liste\n");
		printf(" 6- Afficher valeur présente 1 fois\n");
		printf(" 7- Cherche si la liste est une fibonacci\n");
		printf(" 8- Quitter\n");
		printf("Votre choix : ");
		scanf("%d",&choix);
		/* Traitement du choix de l’utilisateur */
		switch(choix)
		{ 
			case 1: inserer(); afficher(); break;
			case 2: afficher_multiples(); afficher(); break;
			case 3: compter(); afficher(); break;
			case 4: supprimer(); afficher(); break;
			case 5: vider_liste(); afficher(); break;
			case 6: prensenter(); afficher(); break;
			case 7: fibonacci(); afficher(); break;
			case 8: break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 6\n");
		}
	}
	 while(choix!=6);
	 printf("Au revoir !\n");
	 return 1 ; 
}