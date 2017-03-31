def str2b256(mot):
    n = len(mot)-1
    conversion = 0
    for x in mot :
        y = ord(x)
        conversion += y * (256 ** n)
        n -= 1
    return conversion

def h(mot):
    val_num = str2b256(mot)%255
    print(mot, val_num)

h("Blop")
h("Blpo")
h("Bolp")
h("opBl")
h("lopB")
        
#un mot avec les memes caractères mais dans un ordre différent donneront une valeur à conversion différente,
#conversion = ascii(ch[0])* 256**3 + ascii(ch[1])* 256**3 + ascii(ch[2])* 256**3 + ascii(ch[3])* 256**3
#comme on fait %255 sur conversion notre nombre retourne à 142 pour "Blop" car si on le fait séparement
#(66*256**3)%255 = (66*256**1)%255
#Au final on fait juste une addition des caractères en ASCII

