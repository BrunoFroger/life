//-----------------------------------
//
//      main.cpp
//
//-----------------------------------

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "../inc/life.hpp"

Humain *ptr = NULL;
Humain *ptr1 = NULL;
Entreprise *ptrEnt;
Produit *ptrProduit;
Commande *ptrCommande;
bool fin = false;
char nom[50];
char parent[50], enfant[50];
char pere[50], mere[50];
char genre;
bool trouve;
int nb_valeurs = 10;
int valeur_basse = 0;
int valeur_haute = 100;
bool dataSauvegardees = true;
FILE *file, *fileJson;
char saisie[50];
char prompt[50];
char promptDate[50];
int idx;
Humain *dieu;

//-------------------------------------------
//
//          setPrompt
//
//-------------------------------------------
void setPrompt(char *texte){
    if (strlen(texte) > 0){
        sprintf(prompt, "life (%s) > ", nomFichier);
    } else {
        sprintf(prompt, "life > ");
    }
}

//-------------------------------------------
//
//          setPrompt
//
//-------------------------------------------
char *updatePrompt(void){
    sprintf(promptDate, "%s : %s", getDate(nbJours), prompt);
    return promptDate;
}

//-------------------------------------------
//
//          sauveFichier
//
//-------------------------------------------
void sauveFichier(){
    printf("nom du fichier de sauvegarde (%s): ", nomFichier);
    scanf("%s", saisie);
    if (strlen(saisie) > 0){
        strcpy(nomFichier, saisie);
        strcpy(nomFichierJson, saisie);
        strcat(nomFichierJson, ".json");
        setPrompt(saisie);
    }
    file = fopen(nomFichier, "w");
    fileJson = fopen(nomFichierJson, "w");
    if (file != NULL){
        fputs("{\n", fileJson);
        printf("lancement de la boucle de sauvegarde des %d humains\n", nbHumains - 1);
        // on commence a 1 car on ne sauveagrde pas dieu
        fputs(" \"humain\": [\n", fileJson);
        for (int i = 1 ; i < nbHumains ; i ++ ){
            ptr = listeHumains[i];
            ptr->sauve(file);
            ptr->sauveJson(fileJson);
        }
        fputs(" ],\n", fileJson);
        fflush(fileJson);
        printf("lancement de la boucle de sauvegarde des %d entreprises\n", nbEntreprises);
        Entreprise *ptrEnt;
        fputs(" \"entreprise\": [\n", fileJson);
        for (int i = 0 ; i < nbEntreprises ; i ++ ){
            ptrEnt = listeEntreprises[i];
            ptrEnt->sauve(file);
            ptrEnt->sauveJson(fileJson);
        }
        fputs(" ],\n", fileJson);
        fflush(fileJson);
        printf("lancement de la boucle de sauvegarde des %d produits\n", nbProduits);
        Produit *ptrProd;
        fputs(" \"produits\": [\n", fileJson);
        for (int i = 0 ; i < MAX_PRODUITS ; i ++ ){
            ptrProd = listeProduits[i];
            if (ptrProd != NULL){
                ptrProd->sauve(file);
                ptrProd->sauveJson(fileJson);
            }
        }
        fputs(" ],\n", fileJson);
        fflush(fileJson);
        printf("lancement de la boucle de sauvegarde des %d Commandes\n", nbCommandes);
        Commande *ptrCde;
        fputs(" \"commande\": [\n", fileJson);
        for (int i = 0 ; i < MAX_COMMANDES ; i ++ ){
            ptrCde = listeCommandes[i];
            if (ptrCde != NULL){
                ptrCde->sauve(file);
                ptrCde->sauveJson(fileJson);
            }
        }
        fputs(" ]\n", fileJson);
        fputs("}\n", fileJson);
        fflush(fileJson);
        fclose(file);
        dataSauvegardees = true;
    } else {
        printf("Impossible d'ouvrir %s\n", nomFichier);
    }
}

//-------------------------------------------
//
//          chargeFichier
//
//-------------------------------------------
void chargeFichier(FILE *file){
    //printf("main:chargeFichier => lancement de la boucle de lecture du fichier\n");
    char ligne[500];
    int ligne_id, ligne_genre, ligne_age, ligne_typeProd, ligne_effectMax, ligne_idPere;
    int ligne_type, ligne_entrepriseId, ligne_prix, ligne_stock, ligne_stockMini, ligne_coutFabrication, ligne_dureeVie, ligne_delaiFab, ligne_indNeccess;
    int idHumain;
    char ligne_nom[50], ligne_prenom[50], typeLigne[25];
    printf("life:chargeFichier => ------- boucle init ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        fgets(ligne, 500, file);
        ligne[strlen(ligne)-1]='\0';    // suppression du RC
        //printf("main:chargeFichier => ----------------\n");
        if (strlen(ligne) > 0){
            sscanf(ligne, "%s ", typeLigne);
            //printf("main:chargeFichier => analyse de la ligne %s", ligne);
            if (strcmp(typeLigne,"humain") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %s %s %d %d %d", typeLigne, &ligne_id, ligne_prenom, ligne_nom, &ligne_genre, &ligne_age, &ligne_idPere);
                if (ligne_id != nbHumains){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbHumains);
                } else {
                    ptr = new Humain(getHumainById(ligne_idPere), ligne_genre, ligne_nom, ligne_prenom, ligne_age);
                    //printf("main:chargeFichier => Humain %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"entreprise") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %s %d %d %d", typeLigne, &ligne_id, ligne_nom, &idHumain, &ligne_typeProd, &ligne_effectMax);
                if (ligne_id != nbEntreprises){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbEntreprises);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrEnt = new Entreprise(ligne);
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"produit") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %d %d %s %d %d %d %d %d %d %d", typeLigne, &ligne_id, &ligne_type, &ligne_entrepriseId, ligne_nom, &ligne_prix, &ligne_stock, &ligne_stockMini, &ligne_coutFabrication, &ligne_dureeVie, &ligne_delaiFab, &ligne_indNeccess);
                if (ligne_id != nbProduits){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbProduits);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrProduit = new Produit(ligne_nom, ligne_type, ligne_entrepriseId, ligne_stock, ligne_stockMini, ligne_prix, ligne_coutFabrication, ligne_dureeVie, ligne_delaiFab, ligne_indNeccess);
                    listeProduits[nbProduits-1] = ptrProduit;
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"commande") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "commande %d ", &ligne_id);
                if (ligne_id != nbCommandes){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbCommandes);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrCommande = new Commande(ligne);
                    listeCommandes[nbCommandes - 1] = ptrCommande;
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else {
                //printf(" main:chargeFichier => boucle init : on ne traite pas ligne <%s>", ligne);
            }
        }
    }
    fseek(file, 0, 0);
    printf("life:chargeFichier => -------  boucle restore ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        int indexRestore = -1;
        fgets(ligne, 500, file);
        //printf("main:chargeFichier => -----------------\n");
        if (strlen(ligne) > 0){
            sscanf(ligne, "%s %d", typeLigne, &ligne_id);
            //sscanf(ligne, "humain %d", &ligne_id);
            int j = 0;
            if (strcmp(typeLigne, "humain") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                //printf("main::chargeFichier => humain detecte\n");
                ptr = listeHumains[j];
                while (ptr->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptr->getId(), ligne_id);
                    ptr = listeHumains[++j];
                    indexRestore = j;
                    if (j > nbHumains){
                        printf("ERREUR : la ligne <%s> ne reference pas un humain initialis??\n", ligne);
                        return;
                    }
                }
                //printf("main:chargeFichier => indexRestore(%d), ligne(%s)\n", indexRestore, ligne);
                ptr->restore(ligne);
            } else if (strcmp(typeLigne, "entreprise") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                //printf("main::chargeFichier => entreprise detecte\n");
                ptrEnt = listeEntreprises[j];
                while (ptrEnt->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptrEnt->getId(), ligne_id);
                    ptrEnt = listeEntreprises[++j];
                    indexRestore = j;
                    if (j > nbEntreprises){
                        printf("ERREUR : la ligne <%s> ne reference pas une entreprise initialis??\n", ligne);
                        return;
                    }
                }
                ptrEnt->restore(ligne);
                //printf("main:chargeFichier => indexRestore(%d), ligne(%s)\n", indexRestore, ligne);
            } else if (strcmp(typeLigne,"salarie") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                ptrEnt = listeEntreprises[j];
                while (ptrEnt->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptrEnt->getId(), ligne_id);
                    ptrEnt = listeEntreprises[++j];
                    indexRestore = j;
                    if (j > nbEntreprises){
                        printf("ERREUR : la ligne <%s> ne reference pas une entreprise initialis??\n", ligne);
                        return;
                    }
                }
                ptrEnt->restore(ligne);
                //printf("main:chargeFichier =>  restore salarie ...... TODO ......\n");
                //printf("main:chargeFichier => salarie %s cree en pos %d\n");
            } else if (strcmp(typeLigne,"produit") == 0) {
                // rien a faire
            } else if (strcmp(typeLigne,"commande") == 0) {
                // rien a faire
            } else {
                printf("life:chargeFichier =>   ERREUR type de ligne <%s> inconnu\n", typeLigne);
                return;
            }
        }
    }
    dataSauvegardees = true;
    setPrompt(nomFichier);
    fclose(file);
}

//-------------------------------------------
//
//          chargeFichierJson
//
//-------------------------------------------
void chargeFichierJson(FILE *file){
    //printf("main:chargeFichierJson => lancement de la boucle de lecture du fichier Json\n");
    char ligne[500];
    int ligne_id, ligne_genre, ligne_age, ligne_typeProd, ligne_effectMax, ligne_idPere;
    int ligne_type, ligne_entrepriseId, ligne_prix, ligne_stock, ligne_stockMini, ligne_coutFabrication, ligne_dureeVie, ligne_delaiFab, ligne_indNeccess;
    int idHumain;
    char ligne_nom[50], ligne_prenom[50], typeLigne[25];
    printf("life:chargeFichierJson => ------- boucle init ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        fgets(ligne, 500, file);
        ligne[strlen(ligne)-1]='\0';    // suppression du RC
        //printf("main:chargeFichier => ----------------\n");
        if (strlen(ligne) > 0){
            sscanf(ligne, "%s ", typeLigne);
            //printf("main:chargeFichier => analyse de la ligne %s", ligne);
            if (strcmp(typeLigne,"humain") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %s %s %d %d %d", typeLigne, &ligne_id, ligne_prenom, ligne_nom, &ligne_genre, &ligne_age, &ligne_idPere);
                if (ligne_id != nbHumains){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbHumains);
                } else {
                    ptr = new Humain(getHumainById(ligne_idPere), ligne_genre, ligne_nom, ligne_prenom, ligne_age);
                    //printf("main:chargeFichier => Humain %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"entreprise") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %s %d %d %d", typeLigne, &ligne_id, ligne_nom, &idHumain, &ligne_typeProd, &ligne_effectMax);
                if (ligne_id != nbEntreprises){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbEntreprises);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrEnt = new Entreprise(ligne);
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"produit") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "%s %d %d %d %s %d %d %d %d %d %d %d", typeLigne, &ligne_id, &ligne_type, &ligne_entrepriseId, ligne_nom, &ligne_prix, &ligne_stock, &ligne_stockMini, &ligne_coutFabrication, &ligne_dureeVie, &ligne_delaiFab, &ligne_indNeccess);
                if (ligne_id != nbProduits){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbProduits);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrProduit = new Produit(ligne_nom, ligne_type, ligne_entrepriseId, ligne_stock, ligne_stockMini, ligne_prix, ligne_coutFabrication, ligne_dureeVie, ligne_delaiFab, ligne_indNeccess);
                    listeProduits[nbProduits-1] = ptrProduit;
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else if (strcmp(typeLigne,"commande") == 0){
                //printf("main:chargeFichier => traitement de la ligne %s", ligne);
                sscanf(ligne, "commande %d ", &ligne_id);
                if (ligne_id != nbCommandes){
                    printf("life:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, nbCommandes);
                } else {
                    //printf("main:chargeFichier =>  restore entreprise ...... TODO ......\n");
                    ptrCommande = new Commande(ligne);
                    listeCommandes[nbCommandes - 1] = ptrCommande;
                    //printf("main:chargeFichier => Entreprise %s cree en pos %d\n", ptr->getNomComplet(), nbHumains - 1);
                }
            } else {
                //printf(" main:chargeFichier => boucle init : on ne traite pas ligne <%s>", ligne);
            }
        }
    }
    fseek(file, 0, 0);
    printf("life:chargeFichier => -------  boucle restore ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        int indexRestore = -1;
        fgets(ligne, 500, file);
        //printf("main:chargeFichier => -----------------\n");
        if (strlen(ligne) > 0){
            sscanf(ligne, "%s %d", typeLigne, &ligne_id);
            //sscanf(ligne, "humain %d", &ligne_id);
            int j = 0;
            if (strcmp(typeLigne, "humain") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                //printf("main::chargeFichier => humain detecte\n");
                ptr = listeHumains[j];
                while (ptr->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptr->getId(), ligne_id);
                    ptr = listeHumains[++j];
                    indexRestore = j;
                    if (j > nbHumains){
                        printf("ERREUR : la ligne <%s> ne reference pas un humain initialis??\n", ligne);
                        return;
                    }
                }
                //printf("main:chargeFichier => indexRestore(%d), ligne(%s)\n", indexRestore, ligne);
                ptr->restore(ligne);
            } else if (strcmp(typeLigne, "entreprise") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                //printf("main::chargeFichier => entreprise detecte\n");
                ptrEnt = listeEntreprises[j];
                while (ptrEnt->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptrEnt->getId(), ligne_id);
                    ptrEnt = listeEntreprises[++j];
                    indexRestore = j;
                    if (j > nbEntreprises){
                        printf("ERREUR : la ligne <%s> ne reference pas une entreprise initialis??\n", ligne);
                        return;
                    }
                }
                ptrEnt->restore(ligne);
                //printf("main:chargeFichier => indexRestore(%d), ligne(%s)\n", indexRestore, ligne);
            } else if (strcmp(typeLigne,"salarie") == 0){
                //printf("main:chargeFichier => complement traitement de la ligne %s", ligne);
                ptrEnt = listeEntreprises[j];
                while (ptrEnt->getId() != ligne_id) {
                    //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptrEnt->getId(), ligne_id);
                    ptrEnt = listeEntreprises[++j];
                    indexRestore = j;
                    if (j > nbEntreprises){
                        printf("ERREUR : la ligne <%s> ne reference pas une entreprise initialis??\n", ligne);
                        return;
                    }
                }
                ptrEnt->restore(ligne);
                //printf("main:chargeFichier =>  restore salarie ...... TODO ......\n");
                //printf("main:chargeFichier => salarie %s cree en pos %d\n");
            } else if (strcmp(typeLigne,"produit") == 0) {
                // rien a faire
            } else if (strcmp(typeLigne,"commande") == 0) {
                // rien a faire
            } else {
                printf("life:chargeFichier =>   ERREUR type de ligne <%s> inconnu\n", typeLigne);
                return;
            }
        }
    }
    dataSauvegardees = true;
    setPrompt(nomFichier);
    fclose(file);
}

//-------------------------------------------
//
//          afficheMenu
//
//-------------------------------------------
void afficheMenu(void){
    printf("--------------------------------\n");
    printf("   boucle d'evolution\n");
    printf("  a : affiche liste auto %d\n", listeAuto);
    printf("  b : affiche stat auto %d\n", statAuto);
    printf("  c : charge population depuis le disque\n");
    printf("  d : affiche seulement les vivants %d\n", vivantsSeulement);
    printf("  e : liste des comptes bancaires\n");
    printf("  f : liste des entreprises\n");
    printf("  g : liste des produits\n");
    printf("  h : liste des commandes en cours\n");
    printf("  i : liste des salaries des entreprises\n");
    printf("  j : affichage arbre genealogique global\n");
    printf("  k : affichage infos d'une personne\n");
    printf("  l : mariage\n");
    printf("  m : menu On/Off %d\n", menuOnOff);
    printf("  n : naissance\n");
    printf("  o : liste des humains crees\n");
    printf("  p : statistiques\n");
    printf("  r : reset datas et chargement population par defaut\n");
    printf("  s : sauvegarde des donnees sur disque\n");
    printf("  v : faire vieillir la population\n");
    printf("  q : quitte le programme\n");
    printf("  z : test generateur de nombre aleatoire\n");
    printf("  A : stats : affiche infos Humains %s\n", getstringBoolean(display_stat_humain));
    printf("  B : stats : affiche infos variables %s\n", getstringBoolean(display_stat_variables));
    printf("  C : stats : affiche infos comptes bancaires %s\n", getstringBoolean(display_stat_cptBanque));
    printf("  D : stats : affiche infos entreprises %s\n", getstringBoolean(display_stat_entreprises));
    printf("  E : stats : affiche infos produits des entreprises %s\n", getstringBoolean(display_stat_produits));
    printf("  G : stats : affiche infos salaries des entreprises %s\n", getstringBoolean(display_stat_salaries));
    printf("  F : stats : affiche infos commandes en cours %s\n", getstringBoolean(display_stat_commandes));
    printf("  ? : affiche ce menu\n");
}

//-------------------------------------------
//
//          resetFlagsDebug
//
//-------------------------------------------
void resetFlagsDebug(void){ 
    debugHumain=false;
    debugCommande=false;
    debugEntreprise=false;
    debugProduit=false;
    debugStats=false;
    debugCptBancaire=false;
}

//-------------------------------------------
//
//          traiteCommande
//
//-------------------------------------------
void traiteCommande(char car){ 
    switch(car){
        case 'a' : // bascule affiche liste automatiquement
            listeAuto = !listeAuto;
            break;
        case 'b' : // bascule affiche liste automatiquement
            statAuto = !statAuto;
            break;
        case 'c': // chargement d'un fichier de donn??es
            printf("nom du fichier de charger : ");
            scanf("%s", nomFichier);
            file = fopen(nomFichier, "r");
            if (file != NULL){
                chargeFichier(file);
            } else {
                printf("Impossible d'ouvrir %s\n", nomFichier);
            }
            dataSauvegardees=true;
            break;
        case 'd' : // bascule affiche vivants seulement
            vivantsSeulement = !vivantsSeulement;
            printf("affichage des vivants seulement : %d\n", vivantsSeulement);
            break;
        case 'e' : // affiche liste des comptes bancaires
            afficheListeComptesBancaires();
            break;
        case 'f' : // affiche liste des comptes bancaires
            afficheListeEntreprises();
            break;
        case 'g' : // affiche liste des produits disponibles
            afficheListeProduits();
            break;
        case 'h' : // affiche liste des commandes disponibles
            afficheListeCommandes();
            break;
        case 'i' : // affiche liste des salarie des entreprises
            Entreprise *ptrEnt;
            for (int i = 0 ; i < MAX_ENTREPRISES ; i++){
                ptrEnt = listeEntreprises[i];
                if (ptrEnt != NULL){
                    ptrEnt->listeSalaries();
                }
            }
            break;
        case 'j': // descendance personne
            dieu->descendance();
            break;
        case 'k': // infos sur une personne 
            printf("nom de la personne : ");
            scanf("%s", nom);
            for (int i = 0 ; i < nbHumains ; i ++ ){
                ptr = listeHumains[i];
                if (ptr != NULL){
                    if (strcmp(ptr->getNom(), nom) == 0){
                        ptr->displayInfos();
                    }
                }
            }
            break;
        case 'l': // mariage
            printf("nom de l'homme : ");
            scanf("%s", pere);
            trouve = false;
            for (int i = 0 ; i < nbHumains ; i ++ ){
                ptr = listeHumains[i];
                if (ptr != NULL){
                    if (strcmp(ptr->getNom(), pere) == 0) {
                        if (ptr->getStatus() == 'M'){
                            printf("ERREUR : cet homme est deja marie\n");
                            break;
                        }
                        if (ptr->getStatus() == 'X'){
                            printf("ERREUR : cet homme est mort\n");
                            break;
                        }
                        printf("mariage possible pour %s\n", ptr->getNom());
                        trouve=true;
                        dataSauvegardees=false;
                        break;
                    }
                }
            }
            if (trouve){
                printf("nom de la femme : ");
                scanf("%s", mere);
                for (int i = 0 ; i < nbHumains ; i ++ ){
                    ptr1 = listeHumains[i];
                    if (ptr1 != NULL){
                        if (strcmp(ptr1->getNom(), mere) == 0) {
                            if (ptr1->getStatus() == 'M'){
                                printf("ERREUR : cet femme est deja mariee\n");
                                break;
                            }
                            if (ptr1->getStatus() == 'X'){
                                printf("ERREUR : cet femme est morte\n");
                                break;
                            }
                            printf("mariage possible pour %s\n", ptr1->getNom());
                            ptr1->mariage(ptr);
                            dataSauvegardees=false;
                            break;
                        }
                    }
                }
            }
            break;
        case 'm' : // bascule affiche meno on off
            menuOnOff = !menuOnOff;
            break;
        case 'n': // naissance
            printf("nom d'un des parent : ");
            scanf("%s", parent);
            trouve = false;
            char *nomDuPere;
            for (int i = 0 ; i < nbHumains ; i ++ ){
                ptr = listeHumains[i];
                if (ptr != NULL){
                    if (strcmp(ptr->getNom(), parent) == 0) {
                        trouve = true;
                        printf("le parent %s existe\n", ptr->getNom());
                        if (ptr->getGenreTexte()[0] == 'H'){
                            nomDuPere = ptr->getNom();
                        } else {
                            if (ptr->getConjoint() != NULL){
                                nomDuPere = ptr->getConjoint()->getNom();
                            }
                        }
                        break;
                    }
                }
            }
            if (! trouve) {
                printf("%s ne corresponds pas a un nom de personne connue\n", parent);
            } else {
                printf("on ajoute un enfant a %s\n", ptr->getNom());
                printf("prenom de l'enfant : ");
                scanf("%s", enfant);
                // todo verifier que le nom n'existe pas
                getchar();
                printf("genre de l'enfant [H/F] : ");
                scanf("%c", &genre);
                switch (genre){
                    case 'H' :
                    case 'h' : 
                        ptr->naissance(HOMME, nomDuPere, enfant);
                        printf("naissance de %s OK\n", enfant);
                        dataSauvegardees=false;
                        break;
                    case 'F' : 
                    case 'f' :
                        ptr->naissance(FEMME, nomDuPere, enfant);
                        dataSauvegardees=false;
                        printf("naissance de %s OK\n", enfant);
                        break;
                    default :
                        printf("Genre %c indefini\n", genre);
                        break;
                }
            }
            break;
        case 'o': // Liste des humains crees
            afficheListeHumains();
            break;
        case 'p' : // statistiques
            statistiques();
            break;
        case 'q': // quitter
            /*if (! dataSauvegardees){
                printf("les donn??es n'ont pas ??t??es sauvegard??es ; voulez vous les sauver [OUI/non] ? ");
                fflush(stdout);
                fflush(stdin);
                car = getchar();
                //if (car != 10) { 
                    if ((car == 'n') || (car == 'N')){
                        fin=true;
                        break;
                    }
                //}
                printf("on veut sauver le fichier (printf a supprimer)\n");
                //sauveFichier();
                dataSauvegardees=true;
            }*/
            fin=true;
            break;
        case 'r': // reset datas et chargement population par defaut
            initMonde(dieu);
            break;
        case 's': // sauvegarde d'un fichier de donn??es
            sauveFichier();
            dataSauvegardees=true;
            break;
        case 'v': // lancement d'une evolution d'une ann??e pour chaque humain/entreprise
            evolution();
            dataSauvegardees=false;
            break;
        case 'z': // test generateur de nombre aleatoire
            printf("valeur basse : "); scanf("%d", &valeur_basse);
            printf("valeur haute : "); scanf("%d", &valeur_haute);
            printf("test generateur de nombre aleatoire sur %d valeurs entre %d et %d\n", nb_valeurs, valeur_basse, valeur_haute);
            for (int i = 0 ; i < nb_valeurs ; i++){
                printf("%d\t", getRandom(valeur_haute - valeur_basse) + valeur_basse);
            }
            printf("\n");
            break;
        case 'A' : // bascule stat affihe humains
            display_stat_humain = !display_stat_humain;
            break;
        case 'B' : // bascule stat affihe variables
            display_stat_variables = !display_stat_variables;
            break;
        case 'C' : // bascule stat affihe comptes bancaires
            display_stat_cptBanque = !display_stat_cptBanque;
            break;
        case 'D' : // bascule stat affihe liste entreprises
            display_stat_entreprises = !display_stat_entreprises;
            break;
        case 'E' : // bascule stat affihe liste des produits par entreprises
            display_stat_produits = !display_stat_produits;
            break;
        case 'F' : // bascule stat affihe liste salaries par entreprises
            display_stat_salaries = !display_stat_salaries;
            break;
        case 'G' : // bascule stat affihe liste commandes en cours
            display_stat_commandes = !display_stat_commandes;
            break;
        case '?': // affichage du menu
            afficheMenu();
            break;
        case '\n':
            break;
        default:
            printf("%c est pas une commande connue (? pour liste des commandes disponibles\n", car);
            break;
    }
}

//-------------------------------------------
//-------------------------------------------
//
//          main
//
//-------------------------------------------
//-------------------------------------------
int main(int argc, char **argv)
{
    printf("**********************************************\n");
    printf("**********************************************\n");
    printf("****                                      ****\n");
    printf("****     Debut du programme %-10s    ****\n", argv[0]);
    printf("****                                      ****\n");
    printf("**********************************************\n");
    printf("**********************************************\n");
    // creation d'un humain
    
    // init date de debut du monde
    initDate(2000, 1,1);
    resetMonde();
    //printf("creation de dieu\n");
    strcpy(tmpString,"dieu");
    strcpy(tmpString1,"");
    dieu = new Humain(0, HOMME, tmpString, tmpString1, 0);
    idx = dieu->getId();
    strcpy(tmpString,"");
    setPrompt(tmpString);

    // analyse des parametres pour eventuellment charger un fichier de donnees ou initialiser le monde par defaut
    if (argc > 1){
        if (strcmp(argv[1], "init") == 0){
            initMonde(dieu);
        } else {
            printf("ouverture du fichier %s\n", argv[1]);
            FILE *fic = fopen(argv[1], "r");
            if (fic == NULL){
                printf("impossible d'ouvrir le fichier %s\n", argv[1]);
            } else {
                strcpy(nomFichier, argv[1]);
                chargeFichier(fic);
            }
        }
    }

    // boucle d'evolution
    while (!fin){
        resetFlagsDebug();
        updatePrompt();
        if (listeAuto) afficheListeHumains();
        if (statAuto) statistiques();
        if (menuOnOff) afficheMenu();
        printf("%s", promptDate);
        fflush(stdin);
        char saisie[20];
        char car;
        int nbRepetitions = 0;
        int i = 0;
        while ((car = fgetc(stdin)) != '\n'){
            saisie[i++] = car;
            saisie[i] = '\0';
        }
        for (int i = 0 ; i < (int)strlen(saisie) ; i++){
            car = saisie[i];
            if ((car >= '0') && (car <='9')){
                nbRepetitions *= 10;
                nbRepetitions += (car - '0');
                continue;
            }
            if (nbRepetitions == 0) nbRepetitions = 1;
            for (int j = 0 ; j < nbRepetitions ; j++){
                traiteCommande(car);
            }
            nbRepetitions=0;
        }
    }
}