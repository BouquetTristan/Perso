#include <stdio.h>

FILE * fichier;
char nom_fichier[20];
int entier;

void creer_nom_fichier()
{
	printf("Entrez le nom de votre fichier à créer : ");
	scanf("%s", nom_fichier);
}

/*L'utilisateur entre des nombres et les envoie sur le fichier choisi et termine par -1 */
void creer_fichier()
{

	fichier = fopen(nom_fichier, "w");
	printf("Entrez une suite de chiffre se finissant par -1 :\n");
	scanf("%i", &entier);
	while(entier != -1)
	{
		fprintf(fichier, "%i ", entier );
		scanf("%i", &entier);
	}
	fclose(fichier);
}

/*Demande le nom d'un fichier à afficher */ 
void afficher_fichier()
{
	printf("Sélectionner un nom de fichier : ");
	scanf("%s", nom_fichier);
	fichier = fopen(nom_fichier, "r");
	
	while(fichier == NULL)
	{
		printf("Erreur, indiquez le nom du fichier à lire : ");
		scanf("%s", nom_fichier);
		fichier = fopen(nom_fichier, "r");
	}

	printf("La suite de nombre contenue dans %s est : ", nom_fichier);

	fscanf(fichier, "%i", &entier);
	while(!feof(fichier))
	{	
		printf("%i ", entier);
		fscanf(fichier, "%i", &entier);
	}
	printf("\n");
	fclose(fichier);
}
void main()
{
	creer_nom_fichier();
	creer_fichier();
	afficher_fichier();
}
