import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pylab import *
import os
from random import gauss


taillemoy = 175
poidsmoy = 70
    
def creerTaille():
    taille=gauss(taillemoy, 15)
    return taille

def creerPoids():
    poids = gauss(poidsmoy, 15)
    return poids

def creationPerso():
    i = 1
    a = input("nombre de personnage : ")
    perso = int(a)
    while i <= perso:
        print("Personnage ", i," :")
        print("    Taille = ", round(creerTaille(),2), "cm")
        print("    Poids = ", round(creerPoids(),2), " kg")
        i = i+1
        
    
    
