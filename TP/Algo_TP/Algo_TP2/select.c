#define N 50
#include <stdio.h>
#include <stdlib.h>

void affichage(char tab[N], int i, int end)
{
	if(end == 0)
		printf("Liste actuelle : ");
	else
		printf("Liste finale : ");


	for(int j = 0; j < i; j++)
	{
		printf("%c ", tab[j]);
	}
	printf("\n");
}

void tri_select(char tab[N], int j)
{
	char x;
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
	char tab[N];
	char x;
	int i,j;

	i = 0;
	scanf("%c", &x);

	while(x != '\n')
	{
		tab[i] = x;
		tri_select(tab, i);
		i++;
		affichage(tab, i, 0);
		scanf("%c", &x);
	}

	affichage(tab, i, 1);
}