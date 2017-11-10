#include <stdio.h>
#include "file.h"


void ecriture(int elem)
{
	ajouter(elem);
}

void lecture()
{
	int valeur;

	printf("Nombres lus : ");
	while(!filevide())
	{
		retirer(&valeur);
		printf("%i ", valeur);
	}
	printf("\n");

}

void main()
{
	initfile();
	int elem;

	printf("Donnez un nombre : ");
	scanf("%i", &elem);

	while(elem != -1)
	{
		if(elem == 0)
			lecture();
		else
			ecriture(elem);

		printf("Donnez un nombre : ");
		scanf("%i", &elem);
	}

	printf("Au revoir !\n");
}