#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

int main()
{
    double * A;
    double * B;
    double * resultat;

/*  double *C, * invC; */

    A = creerMatrice(3);

    *(A+0) = 1; *(A+1) = 2; *(A+2) = 3;
    *(A+3) = 4; *(A+4) = 5; *(A+5) = 6;
    *(A+6) = 7; *(A+7) = 8; *(A+8) = 9;

    B = creerMatrice(3);

    *(B+0) = -1; *(B+1) = -2; *(B+2) = 0;
    *(B+3) = 4; *(B+4) = 5; *(B+5) = 6;
    *(B+6) = 3; *(B+7) = 2; *(B+8) = 1;

    resultat = creerMatrice(3);

    printf("Matrice A: \r\n");
    afficherMatrice(3, A);
    printf("Matrice B: \r\n");
    afficherMatrice(3, B);

/*    
    somme2Matrices(3, A, B, resultat);
    printf("A + B: \r\n");
    afficherMatrice(3, resultat);
	
    produitReelMatrice(3, 4.5, A, resultat);
    printf("4,5 x A: \r\n");
    afficherMatrice(3, resultat);
	
    produit2Matrices(3, A, B, resultat);
    printf("A x B: \r\n");
    afficherMatrice(3, resultat);

    copieMatrice(3, A, resultat);
    printf("Copie de A dans resultat: \r\n");
    afficherMatrice(3, resultat);

    copieMatrice(3, A, resultat);
    transposerMatrice(3, resultat);
    printf("Transposee de A: \r\n");
    afficherMatrice(3, resultat);
*/
    matriceSansLC(3, A, 1, 1, resultat);
    printf("A privee de ligne 1 et colonne 1: \r\n");
    afficherMatrice(2, resultat);

    printf("det(A) = %8.3f\r\n", determinant(3, A));
    printf("det(B) = %8.3f\r\n", determinant(3, B));
/*
    comatrice(3, B, resultat);
    printf("comatrice de B: \r\n");
    afficherMatrice(3, resultat);

    C = creerMatrice(4);
    invC = creerMatrice(4);

    *(C+0) = 0; *(C+1) = 2; *(C+2) = 1; *(C+3) = 0.5;
    *(C+4) = 1; *(C+5) = 3; *(C+6) = 0; *(C+7) = 1.5;
    *(C+8) = 0.5; *(C+9) = -2; *(C+10) = 1; *(C+11) = -.5;
    *(C+12) = -.5; *(C+13) = 0; *(C+14) = -2; *(C+15) = 0.5;

    afficherMatrice(4, C);
    inverserMatrice(4, C, invC);
    printf("Inverse de C: \r\n");
    afficherMatrice(4, invC);

    detruireMatrice(C);
    detruireMatrice(invC);
    */

    detruireMatrice(A);
    detruireMatrice(B);
    detruireMatrice(resultat);

    return 0;
}
