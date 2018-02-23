
#include "arbre.h"

void ajout_abr(t_arbre a, int val, char texte[T])
{

	if(!arbre_vide(a))
	{
		if(a->val > val)
		{
			if(sag(a) == NULL)
				ajout_gauche(a, val, texte);
			else
				ajout_abr(sag(a), val, texte);			
		}

		if(a->val < val)
		{
			if(sad(a) == NULL)
				ajout_droit(a, val, texte);
			else
				ajout_abr(sad(a), val, texte);
		}

		if(a->val == val)
			printf("Cette valeur est déjà présente dans l'arbre\n");
	}

}

int max(int a, int b)
{
	if(a > b)
		return a;
	return b;
}

int hauteur_abr(t_arbre a)
{
	if(arbre_vide(a))
		return 0;
		
	if(!est_feuille(a))
		return 1+max(hauteur_abr(sad(a)), hauteur_abr(sag(a)));
	return 0;
}

void inferieur(t_arbre a, int val)
{
	if(!arbre_vide(a))
	{
		if(a->val > val)
			printf("Après : %i ", a->val);
				
		else
			inferieur(pere(a), val);
	}
}

void superieur(t_arbre a, int val)
{
	if(!arbre_vide(a))
	{
		if(a->val < val)
			printf("Avant : %i ", a->val);
				
		else
			superieur(pere(a), val);	
	}
}

void recherche(t_arbre a, int val)
{
	if(!arbre_vide(a))
	{
		if(a->val > val)
			recherche(sag(a), val);			
		

		if(a->val < val)
			recherche(sad(a), val);

		if(a->val == val)
		{
			printf("%i est présente dans l'arbre.\nL'évènement de cette année est : %s \n", val, a->texte);
			
			if(sag(a) != NULL)
				printf("Avant : %i ", (sag(a))->val);
					
			else
				superieur(pere(a), val);


			if(sad(a) != NULL)
				printf("Après : %i ", (sad(a))->val);
			else
				inferieur(pere(a), val);
			
			
		}
	}
	else
		printf("%i n'est pas présente dans l'arbre\n", val);
}

void supprimer( t_arbre a)
{
	if(est_feuille(a))
		supprimer_arbre(a);
	else
	{
		
	}
	
}