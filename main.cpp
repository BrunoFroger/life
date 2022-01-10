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

Humain *ptr = NULL;
Humain *ptr1 = NULL;

void chargeFichier(FILE *file){
    printf("lancement de la boucle de lecture du fichier\n");
    char ligne[500];
    while (!feof(file)){
        ligne[0] = '\0';
        fgets(ligne, 500, file);
        printf("-----------------\n");
        printf("analyse de la ligne %s\n", ligne);
        if (strlen(ligne) > 0){
            ptr = new Humain(ligne);
            printf("%s ajouté en pos %d\n", ptr->getNom(), indexHumain);
        }
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    printf("Debut du programme %s\n", argv[0]);
    // creation d'un humain
    printf("creation de dieu\n");
    Humain *dieu = new Humain(HOMME, "dieu", "", 0);
    
    /*
    Humain *adam = dieu->naissance(HOMME, "adam");
    Humain *pierre = adam->naissance(HOMME, "pierre");
    Humain *eve = dieu->naissance(FEMME, "eve");
    Humain *paul = eve->naissance(HOMME, "paul");
    adam->mariage(eve);
    Humain *marie = adam->naissance(FEMME, "marie");
    Humain *joseph = adam->naissance(HOMME, "joseph");
    Humain *jesus = marie->naissance(HOMME, "jesus");
    dieu->descendance();
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
    bool fin = false;
    char nom[50];
    char parent[50], enfant[50];
    char pere[50], mere[50];
    char genre;
    bool trouve;
    char nomFichier[50];
    bool listeAuto=false;
    FILE *file;
    while (!fin){
        printf("--------------------------------\n");
        printf("   boucle d'evolution\n");
        printf("  1 : affichage arbre genealogique global\n");
        printf("  2 : affichage infos d'une personne\n");
        printf("  3 : mariage\n");
        printf("  4 : naissance\n");
        printf("  5 : liste des humains crees\n");
        printf("  6 : statistiques\n");
        printf("  a : affiche liste auto %d\n", listeAuto);
        printf("  c : charge population depuis le disque\n");
        printf("  s : sauvegarde des donnees sur disque\n");
        printf("  v : faire vieillir la population d'un an\n");
        printf("  q : quitte le programme\n");
        printf("  > ");
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
                                    nomDuPere = ptr->getConjoint();
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
            case 's': // sauvegarde d'un fichier de données
                printf("nom du fichier de sauvegarde : ");
                scanf("%s", nomFichier);
                file = fopen(nomFichier, "w");
                if (file != NULL){
                    printf("lancement de la boucle de sauvegarde\n");
                    for (int i = 1 ; i < indexHumain ; i ++ ){
                        ptr = listeHumains[i];
                        ptr->sauve(file);
                    }
                    fclose(file);
                } else {
                    printf("Impossible d'ouvrir %s\n", nomFichier);
                }
                break;
            case 'v': // lancement d'une evolution d'une année pour chaque humain
                for (int i = 0 ; i < indexHumain ; i++){
                    ptr = listeHumains[i];
                    ptr->vieillir();
                }
                if (listeAuto) afficheListeHumains();
                break;
            case 'q': // quitter
                fin=true;
                break;
            default:
                printf("commande inconnue\n");
                break;
        }
        if (car != 10) car = getchar(); // suppression du retour chariot
    }
}