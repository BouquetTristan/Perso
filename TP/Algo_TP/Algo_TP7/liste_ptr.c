#include <stdlib.h>
#include <stdio.h>

typedef struct element
{
	int valeur;
	struct element * pred;
	struct element * succ;
}t_element;

t_element * drapeau;
t_element * ec;
t_element * temp;

void init_liste(void)
{
	drapeau = malloc(sizeof(t_element));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}

int liste_vide(void)
{
	return(drapeau->pred == drapeau);
}

int hors_liste(void)
{
	return(ec == drapeau);
}

void en_tete(void)
{
	if(!liste_vide())
		ec = drapeau->succ;
}

void en_queue(void)
{
	if(!liste_vide())
		ec = drapeau->pred;
}

void suivant(void)
{
	if(!hors_liste())
		ec = ec->succ;
}

void precedent(void)
{
	if(!hors_liste())
		ec = ec->pred;
}

void valeur_elt(int *v)
{
	if (!hors_liste())
		*v = ec->valeur;
}

void modif_elt(int v)
{
	if(!hors_liste())
		ec->valeur = v;
}

void oter_elt(void)
{
	if(!hors_liste())
	{
		ec->succ->pred = ec->pred;
		ec->pred->succ = ec->succ;

		ec->succ = temp;
		temp = ec->valeur;
		ec->valeur = ec->pred;
	}
}

void ajout_droit(int v)
{
	t_element * nouv;
	if(liste_vide() || !hors_liste())
	{
		nouv = temp;
		temp = ec->succ;

		nouv->valeur = v;
		nouv->pred = ec->valeur;
		nouv->succ = ec->succ;

		(ec -> succ) -> pred = nouv;
		ec -> succ = nouv;

		ec = nouv;
	}
}

void ajout_gauche(int v)
{
	t_element * nouv;
	if(liste_vide() || !hors_liste())
	{
		nouv = temp;
		temp = ec->succ;

		nouv->valeur = v;
		nouv->succ = ec->valeur;
		nouv->pred = ec->succ;

		(ec->pred)->succ = nouv;
		ec->pred = nouv;

		ec = nouv;
	}
}