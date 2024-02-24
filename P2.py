# AKOBI BANCONLE TP3

from numpy import array,zeros


from typing import Iterable


from random import randint

# Les Types
TabEntiers = Iterable[int]
Texte = (str, 15)
TabTexte = Iterable[str]
class Calcul:
    etapes: TabTexte = None
    valeur: int = 0
    
# Les constantes
SIGNES: TabTexte = array(["+", "*", "-", "/"])

# 1- procédure qui copie le contenu desnb cases du tableau src dans le tableau dest

def copier_tab(src: TabEntiers, dest: TabEntiers, nb: int):
    for i in range(0, nb):
        dest[i] = src[i]
# 2- procedure qui retourne la ième valeur de tab et la supprime du tableau

def extraire(tab: TabEntiers, i: int, pos_fin: int) -> int:
    # stockons dans n la ième valeur pour ne pas la perdre
    n: int = tab[i] 
    tab[i] = tab[pos_fin]
    tab[pos_fin] = 0
    return n

# testez :
tab: TabEntiers = [1, 2, 3, 4, 5, 6, 7]
v: int = extraire(tab, 2, 6)
print(v, tab)


# 3-fontion qui verifie que l'opérateur sur a sur b est faisable ou utile en respectant certaines contraintes

def verifier(signe: str, a: int, b: int) -> bool:
    t: bool = True
    # la division par 1 ou un resultat de division non entier n'est pas faisable
    if (signe == "/"):
         if ((b == 1) or (b == 0) or (a%b != 0)):
             t = False
    # la multuplication par 1 n'est pas faisable
    elif (signe == "*"):
        if ((a == 1) or (b == 1)):
            t = False
    # la soustraction doit donner un resultat positif
    elif (signe == "-"):
        if ( a-b < 0):
            t = False
    # Tous les autres cas retourne True
    return t

# Tester
a: int = 1
b: int = 2
print(verifier("+", a, b), verifier("-", a, b), verifier("*", a, b), verifier("/", a, b))
a: int = 5
b: int = 4
print(verifier("+", a, b), verifier("-", a, b), verifier("*", a, b), verifier("/", a, b))

# 4-fonction qui retourne le resultat entier de l'operation a signe b

def calculer(signe: str, a: int, b: int) -> int:
    if signe == "+":
        return a + b
    elif signe == "*":
        return a * b
    elif signe == "-":
        return a - b
    elif signe == "/":
        return a / b
# Tester
print(calculer("+", 4, 5))
print(calculer("/", 984, 24))

# 5- fonction qui pioche un operateur applicable sur a et b passé par l'étape de vérification et la retourne

def choisir_operateur(a:int, b:int) -> str:
    x: int = randint(0, 3)
    while (verifier(SIGNES[x], a, b) == False):
        x = randint(0, 3)
    return (SIGNES[x])
# Tester
print(choisir_operateur(4, 4))
print(choisir_operateur(4, 4))
print(choisir_operateur(4, 4))

"""
fonction qui tente des opérations au hasard sur les nombres prix au hasard
jusqu'à ce qu'il n'en reste qu'un.
retourne la chaine menant au calcul s'il arrive au but
"""
def essayer_calcul(tab_num: TabEntiers, but: int) -> Calcul:
    calcul = Calcul()
    calcul.etapes = zeros(5, Texte)
    #travailler sur une copie du tableau des nombres
    copie_num: TabEntiers = zeros(6, int)
    copier_tab(tab_num, copie_num, 6)
    j: int = 0
    for nb in range(5, 0, -1):
        
        # prendre une valeur entre 0 et nb
        i = randint(0, nb)
        
        a: int = extraire(copie_num, i, nb)
        i: int = randint(0, nb-1)
        
        # prendre une valeur entre 0 et nb-1
        b: int = extraire(copie_num, i, nb-1)

        # choisir une operation applicable sur a et b
        signe = choisir_operateur(a,b)
        
        # lancer le calcul de l'operation
        resultat = calculer(signe, a, b)
        
        # classer le resultat en fin de tableau
        copie_num[nb-1] = resultat
        
        # noter le détail de l'operation dans le tableau du calcul
        calcul.etapes[j] = str(a) + " "+ signe + " " + str(b) + " = " +str(resultat)
        j = j+1

        # mettre a jour le resultat actuel dans le calcul
        calcul.valeur = resultat
        # sortir si le but est trouve
        if (resultat == but):
            return calcul
    return calcul
# Tester
c: Calcul = essayer_calcul([12, 23, 34, 45, 56, 65], 77)
print(c.valeur, " trouvé par ", c.etapes)
c = essayer_calcul([12,23,34,45,56,65], 77)
print(c.valeur, " trouvé par ", c.etapes)


"""
BONUS procedure qui definit le but à atteindre , les nombres à utlilser et
lance plusieurs fois essayer_calcul tant que l'objet calculée est different du but en respectant toutefois un nombre maximal de test 
"""
def lancer_essais(but:int, tab_num:TabEntiers, nb_essais_max:int ):
    nb_essais: int = 1
    c: Calcul = essayer_calcul(tab_num, but)
    nb_le_plus_proche: int = c.valeur
    while ((c.valeur != but) and (nb_essais <= nb_essais_max)):
        c = essayer_calcul(tab_num, but)
        nb_essais += 1
        
        # cherchons la valeur la plus proche du but au cas où le nombre d'essais possible serait insuffisant
        if (abs(but - nb_le_plus_proche) > abs(but - c.valeur)):
            nb_le_plus_proche = c.valeur   
    print("Fin de recherche, valeur trouvee = " , c.valeur)
    print("Nb essais effectues = " , nb_essais)
    print("Détail des opérations : ")
    for i in range(0, len(c.etapes)):
        print(c.etapes[i])
    if nb_essais > nb_essais_max:
        print("le nombre d'essais étant limité , le nombre le plus proche du but est ", nb_le_plus_proche)

# tester
lancer_essais(6968, [1,10,4,5,3,50], 10_000)



