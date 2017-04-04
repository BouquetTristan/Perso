#Si l’on considère un groupe de N personnes, quelle est la probabilité
#que deux d’entre elles  soient nées  le  même  jour  de  l’année ?

# probabilité : 1 - ((365!)/(365-n)!)*(1/365**n)
# avec n = nombre de personnes

import math

def anniversaire(n):
    proba = 0
    proba = 1 - (math.factorial(365)/math.factorial(365-n))*(1/365**n)
    print(proba)

# le paradoxe des anniversaires est en faite une collision dans une fonction de hachage deux résultats identiques

def collision(n,m):
    proba = 0
    proba = 1 - (math.factorial(m)/math.factorial(m-n))*(1/m**n)
    print(proba)
