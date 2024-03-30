#include "fonctions.h"


int lecture_csv(char *nomFichier,
                lignedechaqueparking *tableau_enregistrement) {
  FILE *file = fopen(nomFichier, "r");
  if (!file) {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }

  char line[MAX_CHARS];
  int index = 0;
  fgets(line, MAX_CHARS, file); // Ignorer la première ligne (en-tête)

  while (fgets(line, MAX_CHARS, file) && index < MAX_LIGNES) {
    lignedechaqueparking data;
    char *token; // le pointeur//
    /*les strtok contiennent en parametre les pointeurs et les differents
     * separateurs*/

    token = strtok(line, ";");
    /*le pointeur token va prendre l'adresse de la ligne désignée*/
    // data.identifiant = atoi(token);//
    /*le atoi est utilisé pour transformer en entier*/
    strcpy(data.identifiant, token);
    /*la premiere valeur de la ligne sera affectée à l'identifiant de ladite
     * ligne considérée comme une structure*/

    token = strtok(NULL, ";");

    strcpy(data.nom, token);

    token = strtok(NULL, ";");
    strcpy(data.adresse, token);

    token = strtok(NULL, ";");
    strcpy(data.ville, token);

    token = strtok(NULL, ";");
    strcpy(data.etat, token);

    token = strtok(NULL, ";");
    data.places_disponibles = atoi(token);

    token = strtok(NULL, ";");
    data.capacite_max = atoi(token);

    token = strtok(NULL, ";");
    strcpy(data.date_mise_a_jour, token);

    token = strtok(NULL, ";\n");
    strcpy(data.affichage_panneaux, token);

    *(tableau_enregistrement + index++) = data;
    /*enfin la case du tableau d'indice index++ qui est bien sur une structure
     * va contenir maintenant dans chacun de ses champs sa valeur*/
  }
  fclose(file);
  return index;
}

void mettre_a_jour(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement) {
  int i;
  FILE *fichier = fopen("exemple.csv", "w+");
  if (fichier == NULL) {
    printf("Erreur d'ouverture\n");
    exit(1);
  }
  // Réecriture des éléments du fichier csv partant du tableau de structures
  fprintf(fichier, "Identifiant;Nom;Adresse;Ville;État;Places disponibles;Capacité max;Date de mise à jour;Affichage panneaux\n");
  for (i = 0; i < nb_enregistrement; i++) {
    fprintf(fichier, "%s;%s;%s;%s;%s;%d;%d;%s;%s\n", (tableau_enregistrement + i) -> identifiant,(tableau_enregistrement + i) -> nom,(tableau_enregistrement + i) -> adresse,(tableau_enregistrement + i) -> ville,(tableau_enregistrement + i) -> etat,(tableau_enregistrement + i) -> places_disponibles,(tableau_enregistrement + i) -> capacite_max,(tableau_enregistrement + i) -> date_mise_a_jour ,(tableau_enregistrement + i) -> affichage_panneaux);
  }
  fclose(fichier);
}


void ecriture_du_client(clients *client) {
  
  // ouverture en mode écriture
  FILE *fichier = fopen("client.txt", "a");
  if (fichier == NULL) {
    printf("Erreur d'ouverture \n");
    exit(1);
  }
  fprintf(fichier, "%s; %s; date et heure entree: %d-%d-%d %d:%d; date et heure sortie: %d-%d-%d %d:%d ; montant: %d\n",
  client -> plaque_d_immatriculation,
  client->numero_du_parking,
  client->date_heure_entree->tm_year + 1900,
  client->date_heure_entree->tm_mday,
  client->date_heure_entree->tm_mon + 1,
  client->date_heure_entree->tm_hour, 
  client->date_heure_entree->tm_min,
  client->date_heure_sortie->tm_year + 1900,
  client->date_heure_sortie->tm_mday, 
  client->date_heure_sortie->tm_mon +1,
  client->date_heure_sortie->tm_hour,
  client->date_heure_sortie->tm_min,
  client->montant);

  fclose(fichier);
}





void menu(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement , clients *client) {
  // Déclaration des variables
  int choix;

  // Affichage du menu
  printf("-----Menu-----:\n1.chercher un parking\n2.entrer dans un parking\n3.sortir du parking\n0.fin\nVeuillez entrer votre choix\n");

  // Lecture du choix de l'utilisateur
  scanf("%d", &choix);

  // Excecution de la fonction precedente en fonction du choix de l'utilisateur

  switch (choix) {
  case 1:
    chercherparking(tableau_enregistrement, nb_enregistrement, client);
    break;
  case 2:
    entrerparking(tableau_enregistrement, nb_enregistrement, client);
    break;
  case 3:
    sortirparking(tableau_enregistrement, nb_enregistrement, client);
    break;
  case 0:
    printf("AU revoir, merci de votre visite\n");
    break;
  default:
    printf("votre choix est mauvais: au revoir\n");
  }
 
}
void chercherparking(lignedechaqueparking *tableau_enregistrement,
                     int nb_enregistrement,clients *client) {
  // Déclaration des variables
  int choix;
  char nomdelaville[20];
  int i;
  printf("entrer le nom de votre ville\n");
  getchar();
  fgets(nomdelaville, 20, stdin);
  nomdelaville[strlen(nomdelaville) - 1] = '\0';

  // afficher un petit message d'accueil
  printf("les stations de la ville  %s sont :\n", nomdelaville);

  // Parcourir la liste de tous les parkings et afficher les informations
  // parkings de cette ville
  for (i = 0; i < nb_enregistrement; i++) {

    if (strcmp((tableau_enregistrement + i)->ville, nomdelaville) == 0 &&
        (tableau_enregistrement + i)->places_disponibles > 0) {

      printf("Identifiant: %s\n", (tableau_enregistrement + i)->identifiant);

      printf("Nom: %s\n", (tableau_enregistrement + i)->nom);
      printf("Adresse: %s\n", (tableau_enregistrement + i)->adresse);

      printf("État: %s\n", (tableau_enregistrement + i)->etat);

      printf("Places disponibles: %d\n",
             (tableau_enregistrement + i)->places_disponibles);

      printf("\n");
      // mettre une pause de une seconde avant l'étape suivante
      sleep(1);
    }
  }
  printf("Passons à l'étape suivante si vous voulez bien\n");

  // Retour au menu principal
  menu(tableau_enregistrement, nb_enregistrement,client);
}


void entrerparking (lignedechaqueparking *tableau_enregistrement,
                   int nb_enregistrement, clients *client) {
  // Déclaration des variables
  
  char plaque_d_immatriculation[11];
  int i;
  time_t temps = time(NULL);
  char identifiant[9];

  
  // Récupération de la date et heure d'entrée du client qui sert directement d'initialisation
  client -> date_heure_entree = localtime(&temps);

  // Saisie de l'identifiant du parking choisi

  printf("entrer donc l'identifiant du parking de votre choix\n");
  getchar();
  fgets(identifiant, 9, stdin);
  identifiant[(strlen(identifiant) - 1)] = '\0';
  strcpy(client->numero_du_parking, identifiant);

  // Recherche du parking correspondant à l'identifiant du parking choisi
  for (i = 0; i < nb_enregistrement; i++) {

    if (strcmp((tableau_enregistrement + i)->identifiant, identifiant) == 0) {
      if ((tableau_enregistrement + i)->places_disponibles > 0) {
        // Affichage des informations du parking 
        printf("Affichage panneaux: %s\n",
               (tableau_enregistrement + i)->affichage_panneaux);

        // Décrémentation du nombre de places du parking choisi
        (tableau_enregistrement + i)->places_disponibles -= 1;
        printf("\n");
        
        // Mise à jour de la date d'entree en enregistrant la date et heure en tant que chaine de caractere
      
      

        printf("Avant d'entrer S'il vous plait entrez votre plaque d'immatriculation\n");
        getchar();
        fgets(plaque_d_immatriculation, 11, stdin);
        plaque_d_immatriculation[strlen(plaque_d_immatriculation) - 1] = '\0';
        strcpy(client->plaque_d_immatriculation, plaque_d_immatriculation);
     printf("-----Bienvenue au %s-----\n",
               (tableau_enregistrement + i)->nom);
         /*  Mise à jour de la date et heure grace aux nouvelles informations d'entree, 
en formatant les informations de la date et l'heure dans le champ date_mise_a_jour */
sprintf((tableau_enregistrement+ i) -> date_mise_a_jour, "%d-%02d-%02d  %02d:%02d:00+01:00",
          client -> date_heure_entree->tm_year +1900, 
          client -> date_heure_entree->tm_mday,
          client -> date_heure_entree->tm_mon +1 ,
          client -> date_heure_entree->tm_hour,
          client -> date_heure_entree->tm_min);

      }
      // Message d'erreur si le parking est complet
      else {
        printf("Vous ne pouvez pas entrer , aucune places disponibles \n Aurevoir et merci");
      }
      break;
    }
   
  }

  mettre_a_jour(tableau_enregistrement, nb_enregistrement);
  menu(tableau_enregistrement, nb_enregistrement, client);
}




void sortirparking(lignedechaqueparking *tableau_enregistrement,
                   int nb_enregistrement, clients *client) {
  // Déclaration des variables
  int i;
  // allocation dynamique de la memoire à la structure client->date_heure_sortie pour son initialisation et éviter que le programme ne se plante
  client->date_heure_sortie = (struct tm *)malloc(sizeof(struct tm));
  int nb_heures_passees;
  char plaque_d_immatriculation[11];


  // Demande d'entrée de la plaque d'immatriculation
  printf("Avant de sortir , veuillez s'il vous plait entrer votre plaque d'immatriculation \n");
  getchar();
  fgets(plaque_d_immatriculation, 11, stdin);
  plaque_d_immatriculation[strlen(plaque_d_immatriculation) - 1] = '\0';

  srand(time(NULL));
  nb_heures_passees = rand() % 24 + 1;
  client->montant = 4 * nb_heures_passees;
  printf("ça fera %d euros s'il vous plait", client->montant);
  printf("\n");

    client->date_heure_sortie->tm_year = client->date_heure_entree->tm_year;
client->date_heure_sortie->tm_mon = client->date_heure_entree->tm_mon;
client->date_heure_sortie->tm_min= client->date_heure_entree->tm_min;


  // Si l'heure est après minuit , mettre à jour la date de sortie aussi
  if ((client->date_heure_entree->tm_hour) + nb_heures_passees > 24) {

    client->date_heure_sortie->tm_hour =
        (client->date_heure_entree->tm_hour + nb_heures_passees) - 24;

    client->date_heure_sortie->tm_mday = client->date_heure_entree->tm_mday + 1;
  }

  else {
    client->date_heure_sortie->tm_hour =
        ( client->date_heure_entree->tm_hour) + nb_heures_passees;
    client->date_heure_sortie->tm_mday =  client->date_heure_entree->tm_mday;
  }

  // Augmente le nombres de places disponibles dans le parking
  for (i = 0; i < nb_enregistrement; i++) {

    if (strcmp((tableau_enregistrement + i) -> identifiant,
               client -> numero_du_parking) == 0) {

      (tableau_enregistrement + i) -> places_disponibles += 1;
    /*  Mise à jour de la date et heure  grace aux nouvelles informations de sorties, 
en formatant les informations de la date et l'heure dans le champ date_mise_a_jour */
sprintf((tableau_enregistrement+ i) -> date_mise_a_jour, "%d-%02d-%02d  %02d:%02d:00+01:00",
          client -> date_heure_sortie->tm_year  + 1900 , 
          client -> date_heure_sortie->tm_mday,
          client -> date_heure_sortie->tm_mon +1 ,
          client -> date_heure_sortie->tm_hour,
          client -> date_heure_sortie->tm_min);

      break;
    }
  }
  ecriture_du_client(client);
  mettre_a_jour(tableau_enregistrement, nb_enregistrement);
  menu(tableau_enregistrement, nb_enregistrement,client);
  
free(client->date_heure_sortie);
  
}


void modifier_parking(lignedechaqueparking *tableau_enregistrement, int nb_enregistrement){
  // déclaration des variables
  char Identifiant[9];
  int index_identifiant = -1;
  int i;
  // l'administrateur doit entrer l'identifiant du parking qu'il souhaite modifier
  printf("entrer l'identifiant du parking à modifier ");
  getchar();
  fgets(Identifiant, 9 , stdin);
  Identifiant[strlen(Identifiant)-1] = '\0';

  // verifions si l'identifiant existe ou pas 
  for (i = 0; i < nb_enregistrement; i++) {  
     if (strcmp((tableau_enregistrement + i)->identifiant,Identifiant)){
       index_identifiant = i;
       break;
     } 
}
  //Si l'identifiant existe, on peur modifier les donnees du parking
  if(index_identifiant != -1){
    printf("Maintenant entrez les nouvelles informations pour le parking\n");
    printf("Nom ? \n");
    getchar();
    fgets((tableau_enregistrement + index_identifiant)->adresse, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant)->adresse[nb_enregistrement -1 ] = '\0';
    
    printf("Adresse ? \n");
    getchar();
     fgets((tableau_enregistrement + index_identifiant)->adresse, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant)->adresse[nb_enregistrement -1 ] = '\0';
    
    printf("Ville ? \n");
     fgets((tableau_enregistrement + index_identifiant)->ville, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant)->ville[nb_enregistrement -1 ] = '\0';
    
    printf("Etat \n");
    getchar();
     fgets((tableau_enregistrement + index_identifiant)->etat, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant)->etat[nb_enregistrement -1 ] = '\0';
    printf(" Places disponibles ?\n");
     scanf("%d", &(tableau_enregistrement + index_identifiant) -> places_disponibles);
    
    printf("Capacités max ?\n");
    scanf("%d",&(tableau_enregistrement + index_identifiant)-> capacite_max);
    
    printf("entrer la date et heure de mise à jour en format < année-mois-jour heure:minutes >  \n");
    getchar();
     fgets((tableau_enregistrement + index_identifiant) -> date_mise_a_jour, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant) -> date_mise_a_jour[nb_enregistrement -1 ] = '\0';
    
    printf("Affichages panneaux ?\n");
    getchar();
     fgets((tableau_enregistrement + index_identifiant) -> affichage_panneaux, MAX_CHARS, stdin);
    (tableau_enregistrement + index_identifiant) -> affichage_panneaux[nb_enregistrement -1 ] = '\0';

    // Dès qu'il a finit , on doit mettre à jour le fichier csv contenant les parkings 
    mettre_a_jour(tableau_enregistrement, nb_enregistrement);
  
}
  
    // affichage d'un message d'erreur si l'idenfiant n'existe pas
  else{
    printf("il n'existe pas d'identifiant de ce nom");
  }
}



void editer_client(clients *nouveau_client){
  FILE *fichier = fopen("client.txt", "r");
  // le fichier prov.txt est un fichier provisoire qui va permettre de stocker provisoire les nouvelles informations du client dont la plaque d'immatriculation a été lu;
  FILE *provisoire = fopen("prov.txt", "w");
  char ligne[MAX_LIGNES];
  //declaration du pointeur plaque_d_immatriculation qui par va etre utlisé pour la verification de correspondance entre celle lue et ceux du fichier
  char *plaque_d_immatriculation ;
  // trouve sera utilisé pour verifier si le client dont la plaque a été lu est bien present dans le fichier
  int trouve = 0;

  if (!fichier || !provisoire){
    printf("erreur d'ouverture d'un des fichier");
    exit(1);
    
  }
  while (fgets(ligne, MAX_LIGNES,fichier)){
    plaque_d_immatriculation = strtok(ligne, ";");
    // comparaison avec la plaque lue pour verifier la presence du client dans le fichier
    if(strcmp(plaque_d_immatriculation, nouveau_client->plaque_d_immatriculation) == 0){
      fprintf(provisoire, "%s; %s; date et heure entree: %d-%d-%d %d:%d; date et heure sortie: %d-%d-%d %d:%d ; montant: %d\n",
  nouveau_client -> plaque_d_immatriculation,
  nouveau_client->numero_du_parking,
  nouveau_client->date_heure_entree->tm_year ,
  nouveau_client->date_heure_entree->tm_mday,
  nouveau_client->date_heure_entree->tm_mon ,
  nouveau_client->date_heure_entree->tm_hour, 
  nouveau_client->date_heure_entree->tm_min,
  nouveau_client->date_heure_sortie->tm_year ,
  nouveau_client->date_heure_sortie->tm_mday, 
  nouveau_client->date_heure_sortie->tm_mon ,
  nouveau_client->date_heure_sortie->tm_hour,
  nouveau_client->date_heure_sortie->tm_min,
  nouveau_client->montant);
  // pour changer la valeur et montrer que le client a été trouvé
      trouve = 1;
}
    else{
      fprintf(provisoire, "%s\n", ligne);
    }
    }
  if (trouve == 0 ){
    printf("Client introuvable\n");
  }
    fclose(fichier);
    fclose(provisoire);
// supprimer client.txt
  remove("client.txt");
  // renommer prov.txt en client.txt pour recuperer l'ancien nom
  rename("prov.txt", "client.txt");
  
  }

void remplir_nouvelles_infos_client(){
  /* initialisation du nouveau client en lui allouant de la memoire , pareil pour les champs de date et heure d'entree et sortie à cause du grand nombre de lectures sinon un on aurait core dumped */
   clients *nouveau_client = (clients *)malloc(sizeof(clients));
   nouveau_client->date_heure_entree = (struct tm *)malloc(sizeof(struct tm));
  nouveau_client->date_heure_sortie = (struct tm *)malloc(sizeof(struct tm));
 
  printf("entrer la plaque d'immatriculation du client\n");
  getchar();
  fgets(nouveau_client->plaque_d_immatriculation, 11, stdin );
  nouveau_client->plaque_d_immatriculation[strlen(nouveau_client->plaque_d_immatriculation)-1] = '\0';
  printf("entrer le numero du parking du client\n");
  getchar();
   fgets(nouveau_client->numero_du_parking , 9, stdin );
  nouveau_client->numero_du_parking[strlen(nouveau_client->numero_du_parking)-1] = '\0';
    printf("entrer la date et l'heure en format annee-mois-jour heure:minutes");
  scanf("%d-%d-%d %d:%d",&nouveau_client->date_heure_entree->tm_year,&nouveau_client->date_heure_entree->tm_mon, &nouveau_client->date_heure_entree->tm_mday, &nouveau_client->date_heure_entree->tm_hour,&nouveau_client->date_heure_entree->tm_min);

  printf("Maintenant faites pareil pour la lecture de la date et l'heure de sortie\n");
 scanf("%d-%d-%d %d:%d",&nouveau_client->date_heure_sortie->tm_year,&nouveau_client->date_heure_sortie->tm_mon, &nouveau_client->date_heure_sortie->tm_mday, &nouveau_client->date_heure_sortie->tm_hour,&nouveau_client->date_heure_sortie->tm_min);
  printf("Enfin entrer le montant à payer de ce client\n");
  scanf("%d",&nouveau_client->montant);

  // appel de la fonction editer_fonction pour editer le client si il existe
  editer_client(nouveau_client);
  free(nouveau_client);
}