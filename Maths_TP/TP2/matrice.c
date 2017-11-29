#include <stdio.h>
#include <stdlib.h>

double * creerMatrice(int n)
{
    double * A = malloc (n * n * sizeof(*A));

    if (A == NULL)
    {
        printf("Erreur d'allocation");
        exit(EXIT_FAILURE);
    }

    return A;
}

void detruireMatrice(double * A)
{
    free(A);
}

void afficherMatrice(int n, double * A)
{
	int i = 0;

	while(i < n*n)
	{
		if(i%n == 0)
			printf("\n");
		printf("    %f", *(A+i));
		i++;
	}
	printf("\n\n");
}


void somme2Matrices(int n, double * A, double * B, double * resultat)
{
	int i = 0;

	for (i = 0; i < n*n; i++)
	{
	
		*(resultat+i) = *(A+i) + *(B+i);
	}
}

void produitReelMatrice(int n, double r, double * A, double * resultat)
{
	int i = 0;

	for (i = 0; i < n*n; i++)
	{
	
		*(resultat+i) = *(A+i) * r;
	}	
}

void produit2Matrices(int n, double * A, double * B, double * resultat)
{
	int i = 0, j, k;
	double somme = 0.0;
	for (i = 0; i < n; i++)
	{
		for ( j = 0; j < n; ++j)
		{
			for ( k = 0; k < n; ++k)
			{
				somme += *(A + n*i + k) * *(B + n*k + j);
			}
			*(resultat + n*i + j) = somme;
			somme = 0.0;
		}		
	}	
}

void copieMatrice(int n, double * A, double * copie)
{

	int i;

	for (i = 0; i < n*n; ++i)
	{
		*(copie + i) = *(A + i);
	}
}

void transposerMatrice(int n, double * A)
{
	int i, j;
	double tmp;

	for (i = 0; i < n; ++i)
	{
		for (j = i+1; j < n; ++j)
		{
			tmp = *(A + n*i + j);
			*(A + n*i + j) = *(A + n*j + i);
			*(A + n*j + i) = tmp;
		}
	}
}

void matriceSansLC(int n, double * A, int L, int C, double * resultat)
{
	int i, j, k = 0;

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if(i == L || j == C);
			else
			{
				*(resultat + k ) = *(A + n*i + j);
				k++;
			}
		}
	}
}

double determinant(int taille, double* A)
{
	int i;
	int indice;
	double subDet, det = 0.0;
	
	if(taille == 1)
	{
		/*printf("Taille 1 : %f\n", *A);*/
		return *A;
	}

	else
	{
		for (i = 0; i < taille; ++i)
		{
		
			double * tmp;
			tmp = creerMatrice(taille-1);
			matriceSansLC(taille, A, 0, i, tmp);
			/*afficherMatrice(taille-1, tmp);*/

			subDet = determinant(taille-1, tmp);

			if(i%2 == 0)
				indice = 1;
			else
				indice = -1;

			/*printf("indice : %i\n", indice);
			printf("subDet : %f\n", subDet);*/

			det += *(A + i) * subDet * indice;

			free(tmp);
		
		}
		return det;
	}
}

