#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#include "fonctions.h"

int main() {
  // Declaration des variables
    int choix;
    lignedechaqueparking tableau_enregistrement[MAX_LIGNES];
    int nb_enregistrement;
  // definissons une variable du type clients pour pouvoir utiliser son adresse et initialiser le pointeur client qui pointe vers une structure de type clients
  clients intermediaire;
  // cette structure  permettra de ne pas permettre les donnees d'un client
    clients *client = &intermediaire ;
  
nb_enregistrement = lecture_csv ("exemple.csv", tableau_enregistrement);
      char test[11];
      int reponse_admi;

  // Affichage du tableau de structure rempli
  
    for (int i = 0; i < nb_enregistrement; i++) {
        printf("Identifiant: %s\n", tableau_enregistrement[i].identifiant);
        printf("Nom: %s\n", tableau_enregistrement[i].nom);
        printf("Adresse: %s\n", tableau_enregistrement[i].adresse);
        printf("Ville: %s\n", tableau_enregistrement[i].ville);
        printf("État: %s\n", tableau_enregistrement[i].etat);
        printf("Places disponibles: %d\n", tableau_enregistrement[i].places_disponibles);
        printf("Capacité max: %d\n", tableau_enregistrement[i].capacite_max);
        printf("Date de mise à jour: %s\n", tableau_enregistrement[i].date_mise_a_jour);
        printf("Affichage panneaux: %s\n", tableau_enregistrement[i].affichage_panneaux);
        printf("\n");
    }
   printf("êtes-vous administrateur ou client ? , entrez 0 si administrateur , 1 si client ");
  scanf("%d", &choix);
  if (choix == 0){
      printf("Entrer un mot de passe, s'il vous plait \n ");
       getchar();
      fgets(test, 11, stdin);
      test[strlen(test)-1] = '\0';
       // test de verification de mot de passe
      if (strcmp(test, mot_de_passe) == 0){
          printf("-----bienvenue monsieur dans l'administration-----\n");
        // l'administrateur doit choisir si il veut modifier les donnees d'un client ou modifier les donnees des parkings
          printf("Si vous voulez éditer un client , taper 0 \nSi vous voulez modifier un parking , taper 1\n");
        scanf("%d",&reponse_admi);
        if (reponse_admi == 0){
          // cette fonction permet de lire les nouvelles infos d'un client et appelle la fonction editer_client pour remplacer les infos si ce dernier existe
          remplir_nouvelles_infos_client();
        }
        else{
          modifier_parking(tableau_enregistrement, nb_enregistrement);
        }
      }
  else{
        printf("le mot de passe n'est pas correct ");
      }
  }
  else{
menu(tableau_enregistrement, nb_enregistrement ,client);
  }

return 0;
}