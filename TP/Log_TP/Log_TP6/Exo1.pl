
couleur(rouge).
couleur(jaune).
couleur(vert).
couleur(bleu).

voisin(X, V):-
	X \= V.

region(R1,R2,R3,R4,R5,R6 ):- 
			couleur(R1),
			couleur(R2),
			couleur(R3),
			couleur(R4),
			couleur(R5),
			couleur(R6),

			voisin(R1,R2),
			voisin(R1,R3),
			voisin(R1,R5),
			voisin(R1,R6),

			voisin(R2,R1),
			voisin(R2,R3),
			voisin(R2,R4),
			voisin(R2,R5),
			voisin(R2,R6),

			voisin(R3,R1),
			voisin(R3,R2),
			voisin(R3,R4),
			voisin(R3,R6),

			voisin(R4,R2),
			voisin(R4,R3),

			voisin(R5,R1),
			voisin(R5,R2),
			voisin(R5,R6),

			voisin(R6,R1),
			voisin(R6,R2),
			voisin(R6,R3),
			voisin(R6,R5).