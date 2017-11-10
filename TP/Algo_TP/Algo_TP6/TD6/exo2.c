#include <stdio.h>
#include "pile.h"

void main()
{
	int entier;
	int digit;
	int demi_entier;

	scanf("%i", &entier);
	while(entier > 1)
	{
		demi_entier = entier/2;
		entier = entier/(demi_entier);
		
		if(entier%2 == 0 && entier != 0)
		{
			empiler(1);
		}
		else
			empiler(0);
	}
	while(!pilevide())
	{
		depiler(&digit);
		printf("%i", digit);
	}
}