#include <stdlib.h>

typedef struct element
{
	char caract;
	struct element* suivant;
}
t_element;
t_element* pile;

void initpile(void)
{
	pile = NULL;

}

void empiler(int c)
{
	t_element* nouv;

	nouv = malloc(sizeof(t_element));
	nouv->caract = c;
	nouv->suivant = pile;
	pile = nouv;

}

void depiler(int *c)
{
	t_element* sommet;
	if(pile != NULL)
	{
		*c = pile->caract;
		sommet = pile;
		pile = sommet->suivant;
		free(sommet);

	}
}

int pilevide(void)
{
	return(pile == NULL);
}
