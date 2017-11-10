void main()
{
	initpile(p1);
	initpile(p2);

	scanf("%c", &carac);
	while(carac != '.')
	{
		if(carac == 'a')
			empiler(p1, a);
		else
			empiler(p2, b);
	}

	while(pilevide(p1) || pilevide(p2))
	{
		depiler(p1, &truc);
		depiler(p2, &truc);
	}

	if(pilevide(p1) && pilevide(p2))
		printf();
	else
		if(pilevide(p1))
			printf("a");
		else
			printf("b");
}