#  AKOBI Banconlé

from numpy import zeros, array

import matplotlib.pyplot as plt

from typing import Iterable

from math import cos, sin, pi

from math import log10
from random import*
# Début du programme principal

Couleur = (float, float, float)
class Point:
        x:float=0
        y:float=0
# type tableau de points
TabPoints = Iterable[Point]

# type tableau de points
TabReels = Iterable[float]

def creer_point(x:float, y:float)->Point:
    p:Point = Point()
    p.x = x
    p.y = y
    return p
# tracer de courbes et de seuils
tab_prix:TabReels = array([5.25, 5.59, 4.71, 3.90, 5.25, 5.08, 3.91, 4.55, 5.25, 4.55, 3.91, 4.71, 4.63, 5.25, 5.89, 3.87, 3.92, 4.71])

#1..creation d'une courbe liant les tarifs

def creer_courbes_couts(tab_prix):
# recuperation du nb de villes
    nb_villes:int = len(tab_prix)
# creation d'un tableau d'entiers contenant nb_villes 0
    tab_x:TabReels = zeros(nb_villes, int)
# remplissage du tableau
    for i in range(0, nb_villes):
        tab_x[i] = i
# creation de la courbe
    plt.plot(tab_x, tab_prix)
    plt.show()

# test
creer_courbes_couts(tab_prix)

#2..fonction permettant de tracer les seuils (minimum , maximum et la moyenne des prix)

def creer_courbes_couts_seuils(tab_prix):
# recuperation du nb de villes
    nb_villes:int = len(tab_prix)
# creation d'un tableau d'entiers contenant nb_villes 0
    tab_x:TabReels = zeros(nb_villes, float)
    for i in range(0, nb_villes):
        tab_x[i] = i
    plt.plot(tab_x, tab_prix, color=(0,0,0))
# recherche du MIN, du MAX et de la moyenne des valeurs du tableau tab_prix
    cout_min:float = tab_prix[0]
    cout_max:float = tab_prix[0]
    somme_prix:foat = 0.
    cout_moyen:float = 0.
    for i in range(0, nb_villes):
        if (tab_prix[i] < cout_min):
            cout_min = tab_prix[i]
        if (tab_prix[i] > cout_max):
            cout_max = tab_prix[i]
        somme_prix += tab_prix[i]
    cout_moyen = somme_prix/nb_villes       
# courbe de la ligne du cout max
    tab_max = zeros(nb_villes, float)
# courbe de la ligne du cout min
    tab_min = zeros(nb_villes, float)
# courbe de la ligne du cout moyen
    tab_moy = zeros(nb_villes, float)
# remplissage des 3 tableaux
    for i in range(0, nb_villes):
        tab_max[i] = cout_max
        tab_min[i] = cout_min
        tab_moy[i] = cout_moyen
# creation de la courbe
    plt.plot(tab_x, tab_max, color=(1,0,0))
    plt.plot(tab_x, tab_min, color=(0,0,1))
    plt.plot(tab_x, tab_moy, '--', color=(0,1,0))
    plt.show()
# TEST
creer_courbes_couts_seuils(tab_prix)

# 3.. Tracer des cercles
# 3.a.. dessinons un petit cercle vide pas totalement fermé
def remplir_tab(tab:TabPoints):
    n:int = len(tab)
    a:float = 2.*pi/n
    for i in range(0,n):
        tab[i] = creer_point(cos(a*i), sin(a*i))
def dessiner_cercle(tab:TabPoints):
    nb_points:int = len(tab)
    tab_x = zeros(nb_points, float)
    tab_y = zeros(nb_points, float)
    for i in range(0, nb_points):
        tab_x[i] = tab[i].x
        tab_y[i] = tab[i].y
    plt.plot(tab_x, tab_y)
    plt.show()
    
# Test
nb_points:int = 36
le_tab:TabPoints = zeros(nb_points, dtype=Point)
remplir_tab(le_tab)
dessiner_cercle(le_tab)

#3.b.. dessiner un cercle de plusieurs droites

def dessiner_droites(tab:TabPoints, coef:int):
    nb_points = len(tab)
    plt.figure(figsize = (20,20))
    tab_x1 = zeros(nb_points, float)
    tab_y1 = zeros(nb_points, float)
    tab_x2 = zeros(nb_points, float)
    tab_y2 = zeros(nb_points, float)
    for i in range(0, nb_points):
        tab_x1[i] = tab[i].x
        tab_y1[i] = tab[i].y
        if (i < nb_points//coef):
            tab_x2[i] = tab[i*coef].x
            tab_y2[i] = tab[i*coef].y
        else:
            tab_x2[i] = tab[i*coef%nb_points].x
            tab_y2[i] = tab[i*coef%nb_points].y
    plt.plot([tab_x1, tab_x2], [tab_y1, tab_y2], color = (0.1, 0.1, 0.1))
    plt.show()
# test
nb_points:int = 1256
le_tab:TabPoints = zeros(nb_points, dtype=Point)
remplir_tab(le_tab)
dessiner_droites(le_tab, 2)


