#define N 4

#include <stdio.h>
#include <stdlib.h>


int estNul(double a)
{
	if(a < 0.000001 && a > -0.000001)
		return 1;
	else
		return 0;

}

void afficherMatrice(double mat[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		printf("\n\t");

		for(j = 0; j < N; ++j)
		{
			printf("%8.3f\t", mat[i][j]);
		}
	}
	printf("\n\n");
}


void somme2Matrice(double mat[N][N], double mat2[N][N], double res[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			res[i][j] = mat[i][j] + mat2[i][j];
		}
	}
}

void produitReelMatrice(double r, double mat[N][N], double res[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			res[i][j] = mat[i][j] * r;
		}
	}
}

void produit2Matrice(double mat[N][N], double mat2[N][N], double res[N][N])
{
	int c, l, i;
	for (c = 0; c < N; ++c)
	{
		
		for(l = 0; l < N; ++l)
		{
			res[c][l] = 0;
			for(i = 0; i < N; ++i)
			{
				res[c][l] += mat[c][i] * mat2[i][l];
			}
		}
	}
}

void copieMatrice(double mat[N][N], double copie[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			copie[i][j] = mat[i][j];
		}
	}
}

void creerIdentite(double mat[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

void permuter(double mat[N][N], int l1, int l2)
{
	int i;
	int temp;
	for (i = 0; i < N; ++i)
	{
		temp = mat[l2][i];
		mat[l2][i] = mat[l1][i];
		mat[l1][i] = temp;
	}
}

void diviserLigneMatrice(double mat[N][N], int ligne, double a)
{
	int i;
	for(i = 0; i < N; ++i)
	{
		mat[ligne][i] = mat[ligne][i]* 1/a;
	}
}

void multiLigneMatrice(double mat[N][N], int ligne, double a)
{
	int i;
	for(i = 0; i < N; ++i)
	{
		mat[ligne][i] = mat[ligne][i]* a;
	}
}

void additionLigneMatrice(double mat[N][N], int l1, int l2)
{
	int i;
	for(i = 0; i < N; ++i)
	{
		mat[l2][i] = mat[l2][i] + mat[l1][i];
	}
}

void inversionPivotGauss(double mat[N][N], double res[N][N])
{
	int i, j, k = 0;
	int add, div;

	creerIdentite(res);
	for(i = 0; i < N; i++)
	{
		

		while(mat[i][i] != 1)
		{
			afficherMatrice(mat);
			afficherMatrice(res);
			if(!(estNul(mat[i][i])))
			{
				div = (mat[i][i]);
				printf(" div = %i\n", div);
				diviserLigneMatrice(mat, i, div);
				multiLigneMatrice(res, i, div);

				afficherMatrice(mat);
				afficherMatrice(res);

			}
			else
			{
				while( k < N && mat[k][i] == 0)
					k++;
				printf("Permutation ligne %i avec la ligne %i\n", i, k);
				permuter(mat, i, k);
				permuter(res, i, k);

				afficherMatrice(mat);
				afficherMatrice(res);
			}
		}

		for (j = 0; j < N; ++j)
		{	
			printf("Addition\n");
			while(estNul(mat[i][j]))
			additionLigneMatrice(mat, i, j);
			additionLigneMatrice(res, i, j);

			afficherMatrice(mat);
			afficherMatrice(res);
		}
	}

	afficherMatrice(res);

}