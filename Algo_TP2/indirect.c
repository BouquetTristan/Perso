#define N 50
#define Y 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void affichage(char tab[N][Y],int pos[N], int i, int end)
{
	printf("Liste finale : ");

	for(int j = 0; j < i; j++)
	{
		printf("%i ", pos[j]);
	}
	
	printf("\n");
}

void tri_indirect(char tab[N][Y], int pos[N])
{
	char x;
	for(int i = 0; i < N; i++)
	{
		pos[i] = 0;
		for(int j = 0; j < N; j++)
		{
			if(strcmp(tab[j], tab[i]) < 0)
				pos[i]++;
		}
	}
}

void main()
{
	char tab[N][Y];
	int pos[N];
	char x[Y];
	int i,j;

	i = 0;
	scanf("%s", x);

	while(!(strcmp(x, "##") == 0))
	{
		strcpy(tab[i], x);
		tri_indirect(tab, pos);
		i++;
		scanf("%s", x);
		
	}
	affichage(tab, pos, i, 1);
}