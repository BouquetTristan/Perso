#include "matrice.h"


int main()
{
    double A[N][N]= {{0,1,2,-1},{-3,1,1,-1},{1,1,1,2},{2,-1,-1,0}};
    double B[N][N]= {{1,1,1,1},{2,2,2,2},{-3,-3,-3,-3},{-1,-1,-1,-1}};
    double res[N][N];
    double d = 2;
    
    inversionPivotGauss(A, res);


    return 0;
}
