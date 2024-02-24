# Akobi banconle

#07/04/2023

# exo 1 en tête

from numpy import zeros, array
from typing import Iterable, TypeVar
TabReels = TypeVar(Iterable[float])
MatReels = TypeVar(Iterable[TabReels])
MAXPRODUITS = 100


# exo 2:saisie de la note et du prix du produit no

def saisir_produit(no: int, tabPrixNotes: MatReels):
    tabPrixNotes[0][no] = float(input("entrer le prix du produit ", no))
    tabPrixNotes[1][no] = float(input("entrer la note du produit ", no))

# exo3:saisie des notes et prix de nb produits

def saisir_produits(nb: int, tabPrixNotes: MatReels):
    for i in range(0, nb):
        saisir_produit(i, tabPrixNotes)

# exo4:afficher les details du produit no

def afficher_detail_produit(no: int,tabPrixNotes: MatReels):
    print("produit n°", no,"prix = " ,tabPrixNotes[0][no],"; note = ", tabPrixNotes[1][no])

# exo5:afficher les details de nb produits
def afficher_produits(nb:int,tabPrixNotes: MatReels):
    for i in range(0,nb):
        afficher_detail_produit(i,tabPrixNotes)

# exo6:retourner la valeur maximum parmi les nb valeurs du tableau

def max_tab(nb: int ,tab: TabReels) -> float:
    maximum:float=tab[0]
    for i in range(1,nb):
        if(tab[i]>maximum):
            maximum=tab[i]
    return (maximum)

# exo7retourner le minimum parmi les nb valeures du tableau

def min_tab(nb: int, tab : TabReels) -> float :
    minimum:float = tab[0]
    for i in range(1,nb):
        if(tab[i]<minimum):
            minimum=tab[i]
    return(minimum)

# exo8:afficher les details des produits les moins chers 
def afficher_moins_chers(nb: int, tabPrixNotes: MatReels):
    minimumprix:float=min_tab(nb,tabPrixNotes[0])
    print("les produits les moins chers sont: ")
    for i in range(0, nb):
        if (tabPrixNotes[0][i] == minimumprix):
            afficher_detail_produit(i, tabPrixNotes)

# exo9:afficher les details des produits les mieux notés

def afficher_mieux_notes(nb: int, tabPrixNotes : MatReels ) :
    maximumnotes:float = max_tab(nb, tabPrixNotes[1])
    for i in range(0,nb):
        if (tabPrixNotes[0][i] == maximumnotes):
            afficher_detail_produit(i, tabPrixNotes)
    
# exo10:remplir les valeurs de tab divisées par le minimum de tab

def remplir_tab_norme(nb: int, tab: TabReels, tabNorm:TabReels ):
    maximum:float = max_tab(nb, tab)
    for i in range(0, nb):
        tabNorm[i] = tab[i]/maximum

# exo11:trouver les compromis

def trouver_compromis(nb:int, tabPrixNotes: TabReels ):
    tabNormPrix = zeros(nb,float)
    tabNormNotes = zeros(nb,float)
    tabMixte = zeros(nb,float)
    remplir_tab_norme(nb, tabPrixNotes[0], tabNormPrix)
    remplir_tab_norme(nb, tabPrixNotes[1], tabNormNotes)
    for i in range( 0,nb):
        tabMixte[i] = tabNormNotes[i]*(1-tabNormPrix[i]*0.9)
    print("le ou les  produits dont l'interet est le plus grand est/sont: ")
    for i in range(0,nb):
        if (tabMixte[i] == max_tab(nb,tabMixte)):
            afficher_detail_produit(i, tabPrixNotes)
            
# exo12:moyenne des nb premiers valeurs

def moyenne(nb: int , tab: TabReels) -> float:
    somme: float = 0 
    for i in range(0,nb):
        somme+= tab[i]
    return (somme/nb)

# exo 13:test du tp
def test_TP1():
    prix:TabReels = array([81,72,85,71,66,104,91,87])
    notes:TabReels = array([2,4,5,3,2,0,2,5])
    prixNotes:MatReels = array([prix, notes])
    nb:int = len(prix)
    afficher_moins_chers(nb, prixNotes)
    afficher_mieux_notes(nb, prixNotes)
    trouver_compromis(nb, prixNotes)
    print("Moyenne des prix : " + str(moyenne(nb, prix)))
    print("Moyenne des notes : " + str(moyenne(nb, notes)))
    
 

# fonction principale
test_TP1()


    
    



                            


