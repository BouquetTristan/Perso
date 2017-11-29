#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#define N 4

#include <stdio.h>
#include <stdlib.h>

void afficherMatrice(double A[N][N]);
void somme2Matrices(double A[N][N], double B[N][N], double resultat[N][N]);
void produitReelMatrice(double r, double A[N][N], double resultat[N][N]);
void produit2Matrices(double A[N][N], double B[N][N], double resultat[N][N]);
void copieMatrice(double A[N][N], double copie[N][N]);
void creerIdentite(double id[N][N]);
void permuterLignes(double A[N][N], int l1, int l2);
void diviserLigneMatrice(double A[N][N], int ligne, double a);
int estNul(double a);
void inversionPivotGauss(double AOriginal[N][N], double resultat[N][N]);
/*void inversionPivotGauss(double AOriginal[N][N], double resultat[N][N], double* determinant);*/

#endif /* MATRICE_H_INCLUDED*/
