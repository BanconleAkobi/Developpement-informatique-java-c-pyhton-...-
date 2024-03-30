#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 


#define MAX_LIGNES 1024
#define MAX_CHARS 1024
//definition du mot de passe administrateur
#define mot_de_passe "Vict1" 

#ifndef FONCTIONS_H_INCLUDED

#define  FONCTIONS_H_INCLUDED

typedef struct {
    /*int identifiant;lecture des variables de la structure*/
    char identifiant[MAX_CHARS];
    char nom[MAX_CHARS];
    char adresse[MAX_CHARS];
    char ville[MAX_CHARS];
    char etat[MAX_CHARS];
    int places_disponibles;
    int capacite_max;
    char date_mise_a_jour[MAX_CHARS];
    char affichage_panneaux[MAX_CHARS];
              } lignedechaqueparking;

// le struct tm est une structure qui contient les champs correspondants à l'heure, l'année, le mois .....(tm_hour,tm_year, tm_mon...) de type entiers
typedef struct {
// date , heure, et le montant à regler à la sortie //
  char numero_du_parking[9];
  char plaque_d_immatriculation[11];
  struct tm *date_heure_entree;
  int montant;
  struct tm *date_heure_sortie;
              } clients;



// le menu permettra de presenter à l'utilisateur les differents choix possibles 
void menu(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement,clients *client);

// Cette fonction permettra de presenter à l'utilisateur de visualiser les parkings de la ville de son choix
void chercherparking(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement, clients *client);

//ici après l'entrée dans le parking ; la date et heure d'entrée sont enregistrées 
void entrerparking(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement, clients *client);

// Cette fonction affiche à l'utilisateur le montant à payer 
void sortirparking(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement, clients *client);

int lecture_csv( char *nomFichier, lignedechaqueparking *tableau_enregistrement);
// creation du fichier csv du client 
void ecriture_du_client(clients *client);
void mettre_a_jour(lignedechaqueparking *tableau_enregistrement,
                   int nb_enregistrement);

// Fonctions pour  modifier les parkings 

void modifier_parking(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement);

// fonction permettant d'ecrire les nouvelles donnees d'un client dans une structure de type client provisoire
void remplir_nouvelles_infos_client();
// fonction permettant d'editer les fiches de clients
void editer_client(clients *client);

#endif