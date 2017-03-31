d = {}
type(d)
d["oui"] = "yes"
d["non"] = "no"
d["bonjour"] = "hello"
d["au revoir"] = "good bye"
d["meilleur"] = "best"

def afficher():
    print (d)

def supprimer(a):
    i = 0
    while i < len(d):
        for key in d.keys():
            i+= 1
            if(key[0] == a):
                break
        del d[key]

def afficherKey():
    for key in d.keys():
        print(key)

def ajouter():
    mot = input("Mot à rajouter : ")
    str(mot)
    i = len(d)
    word = input("Entrer la traduction du mot : ")
    str(word)
    if((mot in d) == False):
        d[mot] = word
    else :
        print("Ce mot est déjà dans la liste")
    afficher()
    a = input("Entrer la lettre pour supprimer le mot commencant par cette lettre : ")
    str(a)
    supprimer(a)
    
    
