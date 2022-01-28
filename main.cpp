//-----------------------------------
//
//      main.cpp
//
//-----------------------------------

#include <iostream>

#include "humain.hpp"
#include "variables.hpp"
#include "statistiques.hpp"
#include "tools.hpp"
#include "entreprise.hpp"
#include "evolution.hpp"

Humain *ptr = NULL;
Humain *ptr1 = NULL;
bool fin = false;
char nom[50];
char parent[50], enfant[50];
char pere[50], mere[50];
char genre;
bool trouve;
char nomFichier[50];
int nb_valeurs = 10;
int valeur_basse = 0;
int valeur_haute = 100;

//-------------------------------------------
//
//          chargeFichier
//
//-------------------------------------------
void chargeFichier(FILE *file){
    //printf("main:chargeFichier => lancement de la boucle de lecture du fichier\n");
    char ligne[500];
    int ligne_id, ligne_genre, ligne_age;
    char ligne_nom[50], ligne_prenom[50];
    int index = 0;
    //printf("------- boucle init ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        fgets(ligne, 500, file);
        //printf("main:chargeFichier => ----------------\n");
        if (strlen(ligne) > 0){
            //printf("main:chargeFichier => analyse de la ligne %s\n", ligne);
            sscanf(ligne, "humain %d %s %s %d %d", &ligne_id, ligne_prenom, ligne_nom, &ligne_genre, &ligne_age);
            if (ligne_id != indexHumain){
                //printf("main:chargeFichier => ERREUR : ligne <%s> non attendue id=%d au lieu de %d\n", ligne, ligne_id, index);
            } else {
                ptr = new Humain(ligne_genre, ligne_nom, ligne_prenom, ligne_age);
                //printf("main:chargeFichier => %s cree en pos %d\n", ptr->getNomComplet(), indexHumain - 1);
            }
        }
    }
    fseek(file, 0, 0);
    //printf("main:chargeFichier => -------  boucle restore ----------\n");
    while (!feof(file)){
        ligne[0] = '\0';
        int indexRestore = -1;
        fgets(ligne, 500, file);
        //printf("main:chargeFichier => -----------------\n");
        //printf("main:chargeFichier => analyse ligne %s\n", ligne);
        if (strlen(ligne) > 0){
            sscanf(ligne, "humain %d", &ligne_id);
            int j = 0;
            ptr = listeHumains[j];
            while (ptr->getId() != ligne_id) {
                //printf("main:chargeFichier => test correspondance id ptr->getId()=%d, ligne_id=%d\n ", ptr->getId(), ligne_id);
                ptr = listeHumains[++j];
                indexRestore = j;
                if (j > indexHumain){
                    printf("ERREUR : la ligne <%s> ne reference pas un humain initialisé\n", ligne);
                    return;
                }
            }
            //printf("main:chargeFichier => indexRestore(%d), ligne(%s)\n", indexRestore, ligne);
            ptr->restore(ligne);
        }
    }

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
    printf("  1 : affichage arbre genealogique global\n");
    printf("  2 : affichage infos d'une personne\n");
    printf("  3 : mariage\n");
    printf("  4 : naissance\n");
    printf("  5 : liste des humains crees\n");
    printf("  6 : statistiques\n");
    printf("  a : affiche liste auto %d\n", listeAuto);
    printf("  b : affiche stat auto %d\n", statAuto);
    printf("  c : charge population depuis le disque\n");
    printf("  d : affiche seulement les vivants %d\n", vivantsSeulement);
    printf("  e : liste des comptes bancaires\n");
    printf("  f : liste des entreprises\n");
    printf("  g : liste des produits\n");
    printf("  h : liste des commandes en cours\n");
    printf("  m : menu On/Off %d\n", menuOnOff);
    printf("  s : sauvegarde des donnees sur disque\n");
    printf("  v : faire vieillir la population d'un an\n");
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
    printf("  > ");
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
    printf("Debut du programme %s\n", argv[0]);
    // creation d'un humain
    printf("creation de dieu\n");
    Humain *dieu = new Humain(HOMME, "dieu", "", 0);
    printf("creation de l'entreprise de production alimentaire\n");
    Entreprise *supermarche = new Entreprise("supermarche", PROD_NOURITURE, dieu);
    supermarche->addProduit("nourriture", 2, 10, 5, 1);
    supermarche->addProduit("vetements", 10, 10, 3, 5);
    supermarche->addProduit("boisson", 1, 10, 3, 2);
    
    /*
    Humain *adam = dieu->naissance(HOMME, "martin", "adam");
    Humain *pierre = adam->naissance(HOMME, "martin", "pierre");
    Humain *eve = dieu->naissance(FEMME, "dupond", "eve");
    Humain *paul = eve->naissance(HOMME, "dupond", "paul");
    adam->mariage(eve);
    Humain *marie = adam->naissance(FEMME, "martin", "marie");
    Humain *joseph = adam->naissance(HOMME, "martin", "joseph");
    Humain *jesus = marie->naissance(HOMME, "martin", "jesus");
    //dieu->descendance();
    */
    

    // analyse des parametres pour eventuellment charger un fichier de donnees
    if (argc > 1){
        printf("ouverture du fichier %s\n", argv[1]);
        FILE *fic = fopen(argv[1], "r");
        if (fic == NULL){
            printf("impossible d'ouvrir le fichier %s\n", argv[1]);
        } else {
            chargeFichier(fic);
        }
    }

    // boucle d'evolution
    FILE *file;
    while (!fin){
        int car = getchar();
        switch(car){
            case '1': // descendance personne
                dieu->descendance();
                break;
            case '2': // infos sur une personne 
                printf("nom de la personne : ");
                scanf("%s", nom);
                for (int i = 0 ; i < indexHumain ; i ++ ){
                    ptr = listeHumains[i];
                    if (ptr != NULL){
                        if (strcmp(ptr->getNom(), nom) == 0){
                            ptr->displayInfos();
                        }
                    }
                }
                break;
            case '3': // mariage
                printf("nom de l'homme : ");
                scanf("%s", pere);
                trouve = false;
                for (int i = 0 ; i < indexHumain ; i ++ ){
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
                            break;
                        }
                    }
                }
                if (trouve){
                    printf("nom de la femme : ");
                    scanf("%s", mere);
                    for (int i = 0 ; i < indexHumain ; i ++ ){
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
                                break;
                            }
                        }
                    }
                }
                break;
            case '4': // naissance
                printf("nom d'un des parent : ");
                scanf("%s", parent);
                trouve = false;
                char *nomDuPere;
                for (int i = 0 ; i < indexHumain ; i ++ ){
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
                            break;
                        case 'F' : 
                        case 'f' :
                            ptr->naissance(FEMME, nomDuPere, enfant);
                            printf("naissance de %s OK\n", enfant);
                            break;
                        default :
                            printf("Genre %c indefini\n", genre);
                            break;
                    }
                }
                break;
            case '5': // Liste des humains crees
                afficheListeHumains();
                break;
            case '6' : // statistiques
                statistiques();
                break;
            case 'a' : // bascule affiche liste automatiquement
                listeAuto = !listeAuto;
                break;
            case 'b' : // bascule affiche liste automatiquement
                statAuto = !statAuto;
                break;
            case 'c': // chargement d'un fichier de données
                printf("nom du fichier de charger : ");
                scanf("%s", nomFichier);
                file = fopen(nomFichier, "r");
                if (file != NULL){
                    chargeFichier(file);
                } else {
                    printf("Impossible d'ouvrir %s\n", nomFichier);
                }
                break;
            case 'd' : // bascule affiche vivants seulement
                vivantsSeulement = !vivantsSeulement;
                printf("affichage des vivants seulement : %d\n", vivantsSeulement);
                break;
            case 'e' : // bascule affiche liste des comptes bancaires
                afficheListeComptesBancaires();
                break;
            case 'f' : // bascule affiche liste des comptes bancaires
                afficheListeEntreprises();
                break;
            case 'g' : // bascule affiche liste des produits disponibles
                afficheListeProduits();
                break;
            case 'h' : // bascule affiche liste des produits disponibles
                afficheListeCommandes();
                break;
            case 'm' : // bascule affiche meno on off
                menuOnOff = !menuOnOff;
                break;
            case 's': // sauvegarde d'un fichier de données
                printf("nom du fichier de sauvegarde : ");
                scanf("%s", nomFichier);
                file = fopen(nomFichier, "w");
                if (file != NULL){
                    printf("lancement de la boucle de sauvegarde des %d humains\n", indexHumain);
                    for (int i = 1 ; i < indexHumain ; i ++ ){
                        ptr = listeHumains[i];
                        ptr->sauve(file);
                    }
                    printf("lancement de la boucle de sauvegarde des %d entreprises\n", nbEntreprises);
                    Entreprise *ptrEnt;
                    for (int i = 0 ; i < nbEntreprises ; i ++ ){
                        ptrEnt = listeEntreprises[i];
                        ptrEnt->sauve(file);
                    }
                    fclose(file);
                } else {
                    printf("Impossible d'ouvrir %s\n", nomFichier);
                }
                break;
            case 'v': // lancement d'une evolution d'une année pour chaque humain/entreprise
                evolution();
                break;
            case 'q': // quitter
                fin=true;
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
                if (listeAuto) afficheListeHumains();
                if (statAuto) statistiques();
                if (menuOnOff) afficheMenu();
                break;
            default:
            printf("%c est pas une commande connue (? pour liste des commandes disponibles\n", car);
                break;
        }
        if (car != 10) car = getchar(); // suppression du retour chariot
    }
}