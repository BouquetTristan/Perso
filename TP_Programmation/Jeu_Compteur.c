#include <stdio.h>
#include <stdlib.h>

int jeu(int nbTour, int compteur, int difficulte)
{
	int nombre = 0;
	srand(time(NULL));

	if(compteur == 20)
		return 0;
	if(compteur > 20)
		return 1;

	if(compteur < 20)
	{
		if(nbTour%2 == 1)
		{
			printf("\nC'est votre tour, choisissez un nombre en 1, 2 et 3 :\n");
			printf("Vous choisissez ");
			scanf("%i", &nombre);

		}

		else
		{
			if(difficulte == 1)
			{
				printf("\nC'est le tour de Peter l'ordinateur\n");
				nombre = (rand()%(3)) + 1;
				printf("Peter choisit %i\n", nombre);
			}

			if(difficulte == 2)
			{
				printf("\nC'est le tour de Tyler l'ordinateur\n");
				if(compteur < 17)
					nombre = (rand()%(3)) + 1;
				else
					nombre = 20 - compteur;
				
				printf("Tyler choisit %i\n", nombre);
			}

			if(difficulte == 3)
			{
				printf("\nC'est de tour d'Oliver l'ordinateur\n");
				if((compteur+1)%4 == 0)
					nombre = 1;
				if((compteur+2)%4 == 0)
					nombre = 2;
				if((compteur+3)%4 == 0)
					nombre = 3;
				printf("Oliver choisit %i\n", nombre );
			}
		}
	}

	compteur += nombre;

	printf("Le compteur est de %i\n", compteur);
	nbTour += 1;	

	return 1 + jeu(nbTour, compteur, difficulte);
}

void main()
{
	int gagnant = 0;
	int nbTour = 1;
	int compteur = 0;
	int difficulte = 1;

	printf("Veuillez choisir un niveau de difficulte (1, 2 ou 3) : ");
	scanf("%i", &difficulte);
	while(difficulte > 3 || difficulte < 0)
		scanf("%i", &difficulte);

	printf("C'est parti pour le jeu !\n");

	gagnant = jeu(nbTour, compteur, difficulte);

	if(gagnant%2 == 0)
	{
		if(difficulte == 1)
			printf("Peter a gagné la partie\n");
		if(difficulte == 2)
			printf("Tyler a gagné la partie\n");
		if(difficulte == 3)
			printf("Oliver a gagné la partie\n");
	}
	else
		printf("Bravo vous avez gagné contre Peter\n");


}