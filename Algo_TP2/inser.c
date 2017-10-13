#define N 10
#include <stdio.h>

void affichage(int tab[N], int i, int end)
{
	if(end == 0)
		printf("Liste actuelle : ");
	else
		printf("Liste finale : ");


	for(int j = 0; j < i; j++)
	{
		printf("%i ", tab[j]);
	}
	printf("\n");
}

void tri_insert(int tab[N], int j)
{
	int x;
	while(j>0 && tab[j] < tab[j-1])
	{
		x = tab[j];
		tab[j] = tab[j-1];
		tab[j-1] = x;
		j--;
	}
}

void main()
{
	int tab[N];
	int i,j,x;

	i = 0;
	scanf("%i", &x);

	while(x != -1)
	{
		tab[i] = x;
		tri_insert(tab, i);
		i++;
		affichage(tab, i, 0);
		scanf("%i", &x);
	}

	affichage(tab, i, 1);
}