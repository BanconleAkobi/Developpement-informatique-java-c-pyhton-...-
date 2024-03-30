#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule {
  char *nom, *prenom;
  char *tel;
  struct cellule *s;
} Cellule;

typedef struct {
  int taille, nb_elem;
  Cellule **t;
} TableH;

//Fonction qui retourne 1 si le numéro passé est au bon format et 0 sinon  
int bon_format(char *numero) {
  if (numero[0] != '+' || numero[1] != '3' || numero[2] != '3' || strlen(numero) != 12) {
    return 0;
  }
  return 1;
}


//Fonction qui retourne la valeur de hachage de la clé s modulo vmax
int hachage(char *s, int vmax) {
  int somme = 0, i;
  for (i = 0; s[i] != '\0'; i++) {
    somme += (int)s[i];
  }
  return (somme % vmax);
}

//Initialisation du tableau t de la table H 
void initialisation(TableH *h, int taille) {
  h->t = (Cellule **)calloc(taille, sizeof(Cellule *));
  if(h->t == NULL){
    printf("Erreur d'allocation de mémoire\n");
  }
  else{
  h->taille = taille;
  h->nb_elem = 0;
  }
}


//fonction d'insertion dans la table de H
int insertion(TableH *h, char *nom, char *prenom, char *tel) {

  //On n'insèrera pas si le numéro est au mauvais format
  if(bon_format(tel)){
    //on récupère d'abord l'indice pour insérer la cellule au bon endroit
  char *cle = (char *)calloc((strlen(nom) + strlen(prenom) + 1), sizeof(char));
  strcpy(cle, nom);
  strcat(cle, prenom);
  int i = hachage(cle, h->taille);
  //on libère la mémoire de la clé vu qu'elle ne sera plus utilisée
  free(cle);
  Cellule *nouveau = (Cellule *)malloc(sizeof(Cellule));
  nouveau->nom = (char *)calloc(strlen(nom) + 1, sizeof(char));
  nouveau->prenom = (char *)calloc(strlen(prenom) + 1, sizeof(char));
  nouveau->tel = (char *)calloc(strlen(tel) + 1, sizeof(char));
//Message d'erreur en cas d'erreur d'allocation de mémoire
  if (nouveau == NULL || nouveau->nom == NULL || nouveau->prenom == NULL || nouveau->tel == NULL) {
    printf("Erreur d'allocation de memoire pour la nouvelle cellule\n");
    return 0;
  } else {
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    strcpy(nouveau->tel, tel);
    nouveau->s = h->t[i];
    h->t[i] = nouveau;
    (h->nb_elem)++;
    return 1;
  }
  }
  printf("Le numéro de %s est au mauvais format -> ne peut pas être inséré, veuillez vérifiez qu'il est au format +33[9chiffres] \n ", nom); 
  return 0;
}

//fonction d'affichage qui appplique la méthode d'affichage de la table H
void affiche(TableH *h) {
  int i;
  Cellule *courant;
  printf("%d éléments\n", h->nb_elem);
  for (i = 0; i < h->taille; i++) {
    printf("[%d]: ", i);
    courant = h->t[i];
    while (courant != NULL) {
      printf("[%s %s %s] ", courant->nom, courant->prenom, courant->tel);
      courant = courant->s;
    }
    printf("\n");
  }
}


/*Fonction de recherche par le nom et le prénom*/
char *recherche(TableH *h, char *nom, char *prenom) {
  int i;
  char *cle = (char *)calloc((strlen(nom) + strlen(prenom) + 1), sizeof(char));
  strcpy(cle, nom);
  strcat(cle, prenom);
  i = hachage(cle, h->taille);

  Cellule *courant = h->t[i];
  while (courant != NULL) {
    if (strcmp(courant->nom, nom) == 0 && strcmp(courant->prenom, prenom) == 0) {
      free(cle);
      return courant->tel;
    }
    courant = courant->s;
  }
  free(cle);
  return NULL;
}

//fonction qui supprime un élément contenant le nom et le prénom passés en paramètre 
int supprime(TableH *h, char *nom, char *prenom) {
  int i;
  char *cle = (char *)calloc((strlen(nom) + strlen(prenom) + 1), sizeof(char));
  strcpy(cle, nom);
  strcat(cle, prenom);
  i = hachage(cle, h->taille);
   free(cle);
  Cellule *courant = h->t[i];
  Cellule *prec = NULL;
  while (courant != NULL){
    if(strcmp(courant->nom, nom) == 0 && strcmp(courant->prenom, prenom) == 0) {
      if (prec == NULL) {
        h->t[i] = courant->s;
      } else {
        prec->s = courant->s;
      }
      free(courant->nom);
      free(courant->prenom);
      free(courant->tel);
      free(courant);
      //on décrémente le nombre d'éléments après suppression d'un élément
      h->nb_elem --;
      return 1;  
  }
    prec = courant;
    courant = courant->s;
  }
    return 0;
}

//fonction qui supprime tous les éléments de la liste chainée pointée par l 
void supprime_liste(Cellule *l) {
  Cellule *courant;
  while (l != NULL) {
    courant = l;
    l = courant->s;
    free(courant->nom);
    free(courant->prenom);
    free(courant->tel);
    free(courant);
  }
}

//fonction qui supprime toute la mémoire allouée
void supprime_tout(TableH *h){
  int i;
  for(i=0; i< h->taille; i++){
    if(h->t[i] != NULL){
      supprime_liste(h->t[i]);
    }
  }
  free(h->t);
  h->taille = 0;
  h->nb_elem = 0;
}

//fonction qui double la table et réarrange les éléments
int augmente(TableH *h){
  Cellule *courant;
  Cellule **temp = h->t;
  int i;
  h->taille *= 2;
  h->t = (Cellule **)calloc(h->taille, sizeof(Cellule *));
  if (h->t == NULL){
    return 0;
  }
h->nb_elem = 0;
    for(i = 0; i< h->taille/2; i++){
      if(temp[i] != NULL){
        courant = temp[i];
        while(courant != NULL){
          insertion(h, courant->nom, courant->prenom, courant->tel);
          courant = courant->s;
        }
      }
    }
    for(i =0; i < h->taille/2; i++){
      supprime_liste(temp[i]);
    }
   free(temp);
    return 1;

}

/*fonction insertion dupliquée en une fonction qui ajoute l’élément puis augmente la taille de la table, si besoin*/
void insertion2(TableH *h, char *nom, char *prenom, char *tel, double seuil) {
   if(insertion(h, nom, prenom,tel) == 1){
  double taux_cmp = (double)(h->nb_elem) /(h->taille);
  if (taux_cmp > seuil){
    printf("Le taux de compression est de %.2lf pourcents->\n", taux_cmp *100);
    if(augmente(h) == 1){
      printf("            -----Augmentation de la table-----\n");
      affiche(h);
      printf("\n");

    }
    else{
      printf("L'augmentation a échoué");
    }
  }
   }
}

/* fonctionqui effectue une approche similaire à augmente mais pour réduire la table.*/
int diminue(TableH *h){
  Cellule *courant;
  Cellule **temp = h->t;
  int i;
  h->taille /=2;
  h->t = (Cellule **)calloc(h->taille, sizeof(Cellule *));
  if (h->t == NULL){
    return 0;
  }
h->nb_elem = 0;
    for(i = 0; i< h->taille*2; i++){
      if(temp[i] != NULL){
        courant = temp[i];
        while(courant != NULL){
          insertion(h, courant->nom, courant->prenom, courant->tel);
          courant = courant->s;
        }
      }
    }
    for(i =0; i < h->taille/2; i++){
      supprime_liste(temp[i]);
    }
   free(temp);
    return 1;

}

/*fonction supprime qu'on duplique en une fonctio
int supprime2 qui adaptée au taux de compression*/
int supprime2(TableH *h, char *nom, char *prenom, double seuil){
     supprime(h, nom, prenom);
  double taux_cmp = (double)h->nb_elem/h->taille;
  if(taux_cmp  < seuil){
    printf("Le taux de compression est de %.2lf pourcents->\n", taux_cmp*100);
      if(diminue(h) == 1 && h->taille != 8){
      printf("         ------Diminution de la table------\n");
      affiche(h);
      }
    else{
      printf("La diminution a échoué\n");
    }
  }
}

/*fonction qui calcule et retourne le ratio du nombre de listes chaînées utilisées dans la table*/
double ratio(TableH *h){
  int nb_listes = 0, i;
  double ratio;
  for (i =0; i< h->taille; i++){
    if( h->t[i] != NULL){
      nb_listes++;
    }
  }
  ratio = (double)nb_listes/h->taille;
  return ratio;
}

int main() {
  char nom[64], prenom[64], tel[13];
  TableH h;
  //le fichier txt a été modifié car tous les numéros de l'original était au mauvais format
  FILE *f = fopen("liste_noms.txt", "r");
  if (f != NULL) {
    initialisation(&h,8);
    while (fscanf(f, "%s %s %s", nom, prenom, tel) != EOF) {
      insertion2(&h, nom, prenom, tel, 0.5);
    }
    fclose(f);
  }

  // Test rapide de  la fonction de recherche;
  char *tell;
  tell = recherche(&h, "Leclerc", "Antonin");
  if (tell != NULL){
    printf("Le numero de Leclerc Antonin est %s\n", tell); 
  }
  else{
    printf("numero non trouvée\n");
  }

  /*Supprimons la table jusqu'à ce qu'il ait une diminution c'est à dire un taux de compression inférieur à 1/8 */
  supprime2(&h, "Leclerc", "Antonin",0.125);
  supprime2(&h, "Allard", "Maxence",0.125);
  supprime2(&h, "Garcon", "Heloise",0.125);
  supprime2(&h, "Dupond", "Brigitte",0.125);
  supprime2(&h, "Baudin", "Odile",0.125);
  supprime2(&h, "Pan", "Mireille",0.125);
  supprime2(&h, "Mullins", "Florence",0.125);
  supprime2(&h, "Lestrange", "Raoul",0.125);
  supprime2(&h, "Gardinier", "Angele",0.125);
  supprime2(&h, "Salmon", "Philippine", 0.125);
  supprime2(&h, "Lachance", "Pauline", 0.125);

  printf("Le ratio actuel est %.4lf\n", ratio(&h));
  supprime_tout(&h);
  return 0;
}