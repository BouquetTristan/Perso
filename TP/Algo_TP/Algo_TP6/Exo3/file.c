#include <stdlib.h>

typedef struct element
{
	int nombre;
	struct element* suivant;
}
t_element;

t_element* tete;
t_element* queue;

void initfile(void)
{
	tete = NULL;
	queue = NULL;
}

int filevide(void)
{
	return(tete == NULL);
}

void ajouter(int v)
{
	t_element* nouv;

	nouv = malloc(sizeof(t_element));
	nouv->nombre = v;
	nouv->suivant = NULL;

	if(filevide())
		tete = nouv;
	else
		queue->suivant = nouv;
	queue = nouv;
}

void retirer(int *v)
{
	t_element * premier;
	if(!filevide())
	{
		premier = tete;
		*v = premier->nombre;
		tete = premier->suivant;
		free(premier);

	}
}
