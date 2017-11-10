void main()
{
	initpile();
	for (int i = 0; i < 100; ++i)
		empiler(0);
	empiler(2);

	scanf("%c", &carac);
	while(carac != '.')
	{
		if(carac == 'a')
			empiler(1);
		else
			depiler(&truc);
	}

	if(sommetpile() == 2)
		printf("égaux");
	else
	{
		if(sommetpile() == 1)
			printf("trop de b");
		else
			printf("trop de a");
	}
}