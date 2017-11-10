#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define N 10

/*Initialisation d'une matrice*/
void initMatrice( int mat[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			mat[i][j] = 0;
		}
	}
}

/*Place les coordonnées dans une matrice, le tout reçu en param*/
void initCellule(int Xpos, int Ypos, int mat[N][N])
{
	mat[Xpos][Ypos] = 1;
}

/*Lit les coordonnées contenue dans un fichier*/
void lectureFichier(int mat[N][N])
{
	FILE * fichier;
	int Xpos, Ypos;

	printf("Entrez le nom du fichier : ");
	scanf("%s", nom_fichier);
	fichier = fopen(nom_fichier, "r");

	while(fichier == NULL)
	{
		printf("Erreur, indiquez le nom du fichier à lire : ");
		scanf("%s", nom_fichier);
		fichier = fopen(nom_fichier, "r");
	}

	fscanf(fichier, "%i", &Xpos);
	fscanf(fichier, "%i", &Ypos);
	while(!feof(fichier))
	{	
		initCellule(Xpos, Ypos, mat);
		
		fscanf(fichier, "%i", &Xpos);
		fscanf(fichier, "%i", &Ypos);
	}
	fclose(fichier);
}

/*Compte le nombre de voisin de chaque case d'une matrice et place leur nombre dans une autre*/
void nbrVoisin( int mat[N][N], int mat2[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(mat2[i][j] == 1)
			{
				if(i-1 > 0 && j-1 > 0)
					mat[i-1][j-1] += 1;

				if(i-1 > 0)
					mat[i-1][j] += 1;

				if(i-1 > 0 && j+1 < N)
					mat[i-1][j+1] += 1;

				if(j-1 > 0)
					mat[i][j-1] += 1;

				if(j+1 < N)
					mat[i][j+1] += 1;

				if(i+1 < N && j-1 > 0)
					mat[i+1][j-1] += 1;

				if(i+1 < N)
					mat[i+1][j] += 1;

				if(i+1 < N && j+1 < N)
					mat[i+1][j+1] += 1;

			}
		}
	}
}
/*Change les cellules d'une matrice d'après ses voisins*/
void newGen( int mat[N][N], int mat2[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(mat[i][j] == 2 && mat2[i][j] == 1);
			
			else
			{
				if(mat[i][j] == 3 )
					mat2[i][j] = 1;
				else
					mat2[i][j] = 0;
			}
		}
	}
}

/*Affichage complet d'une matrice*/
void affichage( int mat[N][N])
{
	printf("\n\n\n\n");
	for(int i = 0; i < N; i++)
	{
		printf("	");
		for(int j = 0; j < N; j++)
			printf("%i ", mat[i][j]);
		printf("\n");
	}

	sleep(2);
	system("clear");
}

void main()
{
	int matCellule[N][N];
	int matVoisin[N][N];

	int nbrGen;

	printf("Nombre de génération : ");
	scanf("%i", &nbrGen);

	initMatrice(matCellule);
	lectureFichier(matCellule);

	affichage(matCellule);

	for (int i = 0; i < nbrGen; ++i)
	{
		initMatrice(matVoisin);
		nbrVoisin(matVoisin, matCellule);
		newGen(matVoisin, matCellule);
		affichage(matCellule);
	}
}