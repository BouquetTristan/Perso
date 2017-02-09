#include<stdlib.h>
#include<stdio.h>
#define N 100

int donnees[N];
int limite;

void init()
{
	for(int i=0; i<limite; i++)
	{
		graph0[i] = 0;
		graph1[i] = 0;
		graph2[i] = 0;
	}
}

void recup_donnees(char nom_fichier[N]){
	int i = 0;
	int val = 0;

	FILE * fichier;
	fichier = fopen(nom_fichier, "r");

	while(feof(fichier) == 0){
		fscanf(fichier,"%i",&val);
		donnees[i] = val;
		i++;
	}
	limite = i-1;
	
}


void affichage(int tab[N]){
	int i;

	for(i=0; i<limite; i++){
		printf("%i ", tab[i]);	
		printf(" ");
	}
	printf("\n\n");
		
	init();
	for(i=0; i<limite; i++)
	{
		if(tab[i] == 1)
		{
			graph0[i] = 1;
			
		}
		else
		{ 
			if(tab[i] == 0)
			{
				graph1[i] = 1;
			}
			else 
			{
				
				graph2[i] = 1;
			}
		}
	}
	
	char vide = ' ';
	char plein = '_';
	
	for(i=0; i<limite; i++)
	{
		if(graph0[i] ==0)
			printf("%c%c", vide, vide);
		else
			printf("%c%c", plein, plein);
	}
	printf("\n");
	for(i=0; i<limite; i++)
	{
		if(graph1[i] ==0)
			printf("%c%c", vide, vide);
		else
			printf("%c%c", plein, plein);
	}
	printf("\n");
	for(i=0; i<limite; i++)
	{
		if(graph2[i] ==0)
			printf("%c%c", vide, vide);
		else
			printf("%c%c", plein, plein);
	}
	printf("\n\n");
}


void encodeur(int v, int hdbn, int un)			/*'v' correspond au signe initiale du viol, 'hdbn' au numero du hdbn, et 'un' a la valeur -1 ou 1 du premier '1' rencontré*/
{
	
	int i = 0;
	int x = un;
	int compteur;
	
	if(x == 1){
		x = -1;
	}
	
	else if(x == -1){
		x = 1;
	}
	
	else {
		x = 0;
	}

	for(i; i<limite; i++){

		if(donnees[i] == 0){					/*Si la valeur est de 0, on verifiera si la suite de 0 ne depasse pas 'n'*/
		
			compteur++;
			
			if(compteur == hdbn+1){
			
				if(v == 1){						/*Si le viol est negatif*/
				
					if(x == 1){
						donnees[i] = -1;
						donnees[i-hdbn] = -1;		
					}
		
					else{
						donnees[i] = -1;
					}
					
					x=donnees[i];
					compteur = 0;
					v = -1;
				}
				else{							/*Si le viol est positif*/
				
					if(x == 1){
						donnees[i] = 1;		
					}
		
					else{
						donnees[i] = 1;
						donnees[i-hdbn] = 1;
					}
					
					x=donnees[i];
					compteur = 0;
					v = 1;
				}
			}
		}
		
		else{ 									/*Si la valeur du signal est egal à '1', attribution de sa nouvelle valeur en fonction du dernier '1'*/
			if(x == 1){
				donnees[i] = -1;		
			}
		
			else{
				donnees[i] = 1;
			}

			x=donnees[i];
			compteur = 0;
		}	
	}
}

void decodeur(int v, int hdbn, int un){			/*'v' correspond au signe initiale du viol, 'hdbn' au numero du hdbn, et 'un' a la valeur -1 ou 1 du premier '1' rencontré*/
	
	int x = un;
	int memoire = 0;
	int i,j,k;
	
	for(i=0; i<limite; i++){
		if(donnees[i] == 0);
		
		else if(memoire != donnees[i]){
			memoire = donnees[i];
			donnees[i] = 1;
		}
		
		else{
			for(j=i; j<hdbn; j++){
				for(k=hdbn; k>0; k--){
					donnees[k] = 0;
				}
			}
		}
	}		
}

void main(){
	int v, hdbn, un;
	
	/*Attribution des parametres initiale par l'utilisateur*/
	printf("Parametre initial V (1 ou -1)= ");
	scanf("%i", &v);
	
	printf("HDBn = ");
	scanf("%i", &hdbn);
	
	printf("Valeur du premier '1' = ");
	scanf("%i", &un);	
	printf("\n");
	
	/*Affichage du signal initial*/
	recup_donnees("test.txt");
	printf("Signal initial :\n ");
	affichage(donnees);
	
	/*Encodage par le HDBn*/
	encodeur(v, hdbn, un);
	
	/*Affichage du signal codé*/
	printf("Signal codé :\n ");
	affichage(donnees);

	/*Decodage par le HDBn*/
	decodeur(v, hdbn, un);
	
	/*Affichage du signal décodé*/
	printf("Signal décodé :\n ");
	affichage(donnees);
	printf("\n");
}