#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * fichier;
char nom_fichier[20];
char caractere;
int entier;

/*Compte le nbr de caracrtère, de mot, d'espace et de retour à la ligne d'un fichier*/
void compteur_texte()
{
	int space = 0;
	int saut_ligne = 0;
	int carac = 0;
	int nb_mot = 0;
	int mot = 0;

	printf("Sélectionner un nom de fichier : ");
	scanf("%s", nom_fichier);
	fichier = fopen(nom_fichier, "r");
	
	while(fichier == NULL)
	{
		printf("Erreur, indiquez le nom du fichier à lire : ");
		scanf("%s", nom_fichier);
		fichier = fopen(nom_fichier, "r");
	}

	fscanf(fichier, "%c", &caractere);
	while(!feof(fichier))
	{	
		if(caractere == ' ' && mot == 0)
		{	
			space++;
			mot = 1;
			nb_mot++;
		}
		else
		{
			if(caractere == '\n')
			{
				saut_ligne++;
				space++;
				mot = 1;
				nb_mot++;
			}
			else
				if(caractere != ' ' && caractere != '\n')
				{
					carac++;
					mot = 0;
				}
		}
		fscanf(fichier, "%c", &caractere);
	}
	printf("Caractère : %i\nEspace : %i\nSaut_ligne : %i\nMots : %i\n", carac, space, saut_ligne, nb_mot);
	fclose(fichier);
}

void main()
{
	
	compteur_texte();
}
