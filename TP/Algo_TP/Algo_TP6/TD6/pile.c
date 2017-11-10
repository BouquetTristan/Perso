#define MAX 100

int pile[MAX];
int sommet;

void initpile()
{
	sommet = -1;
}

void empiler( int elem)
{
	if(sommet < MAX-1)
	{
		sommet++;
		pile[sommet] = elem;
	}
}

void depiler(int *elem)
{
	if(sommet > -1)
	{
		*elem = pile[sommet];
		sommet--;
	}
}

int pilevide(void)
{
	return(sommet == -1);
}