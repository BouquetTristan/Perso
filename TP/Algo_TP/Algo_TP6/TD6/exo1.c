void taiterVcour(char valeur)
{
	int val1, val2;

	if(valeur == '\n')
		printf("Fin calcul");
	
	if(!isdigit(valeur))
	{
		depiler(&val1);
		depiler(&val2);
		if(valeur == '+')
			val1 = val1+val2;
		if(valeur == '-')
			val1 = val1-val2;
		if(valeur == '/')
			val1 = val1/val2;
		if(valeur == '*')
			val1 = val1*val2;
		empiler(val1);
	}
	else
	{
		val1 = convertir(valeur);
		empiler(val1);
	}
}

void affichageIaP(char valeur)
{
	if(valeur == '\n')
		printf("Fin traitement");

	if(!isdigit(valeur))
	{
		if(valeur == '(' || valeur == '+' || valeur == '_' || valeur == '/' || valeur == '*')
			empiler(valeur);
		else
		{
			while(valeur != '(')
			{
				depiler(&valeur);
				if(valeur != '(')
					printf("%c", valeur);
			}
		}
	}
	else
		printf("%i", convertir(valeur));
}


