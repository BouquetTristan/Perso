#include <stdio.h>
#include <stdlib.h>

FILE * fichier;
char nom_fichier[20];

/*Vérifie si l'hydro est correct*/
int choix_hydro(int type, int x, int y)
{
	if(type == 1)
	{
		if(2*x +2 == y)
			return 1;
		else
			return 0;
	}

	if(type == 2)
	{
		if(2*x == y)
			return 1;
		else
			return 0;
	}

	if(type == 3)
	{
		if(2*x -2 == y)
			return 1;
		else
			return 0;
	}
}
/*Détermine le type d'hydrocarbrure*/
void hydrocarbure(int x, int y)
{
	if(choix_hydro(1, x, y) == 1)
		printf("C%iH%i est un alcane\n", x, y);
	else
	{
		if(choix_hydro(2, x, y) == 1)
			printf("C%iH%i est un alcène\n", x, y);
		else
		{
			if(choix_hydro(3, x, y) == 1)
				printf("C%iH%i est un alcyne\n", x, y);
			else
				printf("C%iH%i n'est pas un hydrocarbure\n", x, y);
		}
	}
}
/*Lit un fichier ou se trouve un nbr pair de nbr et classe leur type d'hydrocrabure*/
void lecture()
{
	int carbo, hydro;

	fscanf(fichier, "%i", &carbo);
	fscanf(fichier, "%i", &hydro);
	while(!feof(fichier))
	{	
		hydrocarbure(carbo, hydro);
		
		fscanf(fichier, "%i", &carbo);
		fscanf(fichier, "%i", &hydro);
	}
	fclose(fichier);
}
/*Ouvre le fichier sélectionné*/
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
}

void main()
{
	ouverture();
	lecture();
}
