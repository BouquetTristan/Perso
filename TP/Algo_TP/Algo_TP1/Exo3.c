#include <stdio.h>
#include <stdlib.h>

FILE * fichier;
FILE * fichier_pos;
FILE * fichier_neg;

char nom_fichier[20];

int minimum, maximum;

/*Ecrit dans le fichier choisi le nombre sélectionné*/
void ecriture(int type, int entier)
{
	if(type == 1)
		fprintf(fichier_pos, "%i ", entier);
	else
		fprintf(fichier_neg, "%i ", entier);
}

/*Lit un fichier de nombre et copie les nbr dans deux autres fichiers séparé en positif(nul)/négatif */
void lecture()
{
	int entier;

	fscanf(fichier, "%i", &entier);
	maximum = entier;
	minimum = entier;
	
	while(!feof(fichier))
	{		
		if(entier >= 0)
			ecriture(1, entier);
		else
			ecriture(0, entier);
		if(entier < minimum)
			minimum = entier;
		else if(entier > maximum)
				maximum = entier;

		fscanf(fichier, "%i", &entier);
	}
	fclose(fichier);
	fclose(fichier_pos);
	fclose(fichier_neg);
}

/*Ouvre les fichiers qui seront utilisé */
void ouverture()
{
	printf("Indiquez le nom du fichier à lire : ");
	scanf("%s", nom_fichier);
	fichier = fopen(nom_fichier, "r");
	
	while(fichier == NULL)
	{
		printf("Erreur, indiquez le nom du fichier à lire : ");
		scanf("%s", nom_fichier);
		fichier = fopen(nom_fichier, "r");
	}
	
	fichier_pos = fopen("positif.txt", "w");
	fichier_neg = fopen("negatif.txt", "w");
}

void main()
{
	ouverture();
	lecture();
	printf("Minimum : %i \nMaximum : %i\n", minimum, maximum);
}
