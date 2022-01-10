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

char listePrenomsHomme[][20] = {
    "Adam", "Joseph", "Pierre", "Paul", "Louis", "Vincent", "Louis",
    "Andre", "Michel", "Jean", "Jacques", "Bernard", "Marcel",
    "Daniel", "Roger", "Alain", "Henri", "Georges", "Nicolas"   
};
char listePrenomsFemme[][20] = {
    "Eve", "Marie", "Lucie", "Janette", "Elise", "Julie", "Louise",
    "Jeanne", "Nathalie", "Sylvie", "Anne", "Denise", "Nicole",
    "Helene", "Christine", "Madeleine", "Suzanne", "Monique", "Brigitte",
    "Sandrine", "Stephanie", "Celine", "Aurelie", "Julie", "Laura", "Lea"
};
char listeNomFamille[][20] = {
    "Dupont", "Durand", "Chevalier", "Morin", "Legrand", "Roche", "Riviere", "Carre",
    "Collet", "Poirier", "Aubry", "Fontaine", "Caron", "Colin", "Leclerc", "Duval",
    "Leconte", "Mercier", "Breton", "Leger", "Cordier", "Masson", "Picard", "Lacroix", 
    "Lucas", "Garnier", "Riviere", "Blanchard", "Blanc", "Duval", "Dupuis", "Moulin"
};

int getRandom(int range){
    return rand()%range;
}

enfantDieu child;
enfantDieu getRandomEnfant(void){

    int nbPrenomMasculin = sizeof(listePrenomsHomme) / 20;
    printf("nombre de prenoms masculin disponibles : %d\n", nbPrenomMasculin);
    int nbPrenomFeminin = sizeof(listePrenomsFemme) / 20;
    printf("nombre de prenoms feminin disponibles : %d\n", nbPrenomFeminin);
    int nbNomFamille = sizeof(listeNomFamille) / 20;
    printf("nombre de noms de famille disponibles : %d\n", nbNomFamille);

    int genre = rand() % 1 + 1;
    strcpy(child.nom, listeNomFamille[rand() % nbNomFamille]);

    switch(genre){
        case HOMME:
            strcpy(child.prenom, listePrenomsHomme[rand() % nbPrenomMasculin]);
            break;
        case FEMME:
            strcpy(child.prenom, listePrenomsFemme[rand() % nbPrenomFeminin]);
            break;
    }
    printf("enfant retourne : %s %s (%d)\n", child.nom, child.prenom, child.genre);

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