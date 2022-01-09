//-----------------------------------
//
//      tools.cpp
//
//-----------------------------------

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include "tools.hpp"
#include "humain.hpp"
#include "variables.hpp"

enfantDieu listePrenoms[8];
bool listePrenomsOK=false;

void initListePrenoms(){
    printf("init listes prenoms pour dieu \n");
    strcpy(listePrenoms[0].nom,"adam");
    listePrenoms[0].genre=HOMME;
    strcpy(listePrenoms[1].nom,"eve");
    listePrenoms[1].genre=FEMME;
    strcpy(listePrenoms[2].nom,"joseph");
    listePrenoms[2].genre=HOMME;
    strcpy(listePrenoms[3].nom,"marie");
    listePrenoms[3].genre=FEMME;
    strcpy(listePrenoms[4].nom,"pierre");
    listePrenoms[4].genre=HOMME;
    strcpy(listePrenoms[5].nom,"lucie");
    listePrenoms[5].genre=FEMME;
    strcpy(listePrenoms[6].nom,"paul");
    listePrenoms[6].genre=HOMME;
    strcpy(listePrenoms[7].nom,"elise");
    listePrenoms[7].genre=FEMME;
}
int getRandom(int range){
    return rand()%range;
}

enfantDieu child;
enfantDieu getRandomEnfant(void){
    if (! listePrenomsOK){
        initListePrenoms();
        listePrenomsOK=true;
    }

    int valeur = rand() % 8;
    printf("get nom enfant aleatoire %d\n", valeur);
    strcpy(child.nom,listePrenoms[valeur].nom);
    child.genre=listePrenoms[valeur].genre;
    printf("enfant retourne : %s,%d\n", child.nom, child.genre);

    return child;
}

void afficheListeHumains(void){
    Humain *ptr;
    printf("nombres d'humains crees : %d\n", indexHumain);
    printf("+-----------------------+-------+-------+------+----------------------+----------------------+----------------------+------------+\n");
    printf("|                   nom | status| genre | age  |             conjoint |                 pere |                 mere | nb enfants |\n");
    printf("+-----------------------+-------+-------+------+----------------------+----------------------+----------------------+------------+\n");
    for (int i = 0 ; i < indexHumain ; i++){
        ptr = listeHumains[i];
        char genre = ptr->getGenreTexte()[0];
        char status = ptr->getStatus();
        printf("| %20s  |   %c   |   %c   | %3d  | %20s | %20s | %20s |    %2d      |",
        ptr->getNom(), status, genre, ptr->getAge(), ptr->getConjoint(), ptr->getPere(), 
        ptr->getMere(), ptr->getNbEnfants() );
        if (ptr->getNbEnfants() != 0){
            for (int ii = 0 ; ii < ptr->getNbEnfants() ; ii++){
                printf(" %s,", ptr->getEnfant(ii));
            }
        }
        printf("\n");
    }
    printf("+-----------------------+-------+-------+------+----------------------+----------------------+----------------------+------------+\n");
    printf("\n");
}