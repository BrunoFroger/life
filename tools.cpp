//-----------------------------------
//
//      tools.cpp
//
//-----------------------------------

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include "tools.hpp"
#include "humain.hpp"
#include "variables.hpp"
#include "compteBancaire.hpp"

char listePrenomsHomme[][20] = {
    "Adam", "Joseph", "Pierre", "Paul", "Louis", "Vincent", "Louis",
    "Andre", "Michel", "Jean", "Jacques", "Bernard", "Marcel", "bernard",
    "Daniel", "Roger", "Alain", "Henri", "Georges", "Nicolas", "jules"
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

//-------------------------------------------
//
//          getRandom
//
//-------------------------------------------
int getRandom(int range){
    //printf("genere nombre aleatoire entre 0 et %d\n", range);
    srand(clock());
    int tmp = rand() % ((range) * 10);
    tmp /= 10;
    return tmp;
    //range += 1;
    //return (rand() * 10) % range;
}

//-------------------------------------------
//
//          getPrenomMasculin
//
//-------------------------------------------
char *getPrenomMasculin(void){
    int nbPrenomMasculin = sizeof(listePrenomsHomme) / 20;
    //printf("nombre de prenoms masculin disponibles : %d\n", nbPrenomMasculin);
    return listePrenomsHomme[rand() % nbPrenomMasculin];
}

//-------------------------------------------
//
//          getPrenomFeminin
//
//-------------------------------------------
char *getPrenomFeminin(void){
    int nbPrenomFeminin = sizeof(listePrenomsFemme) / 20;
    //printf("nombre de prenoms feminin disponibles : %d\n", nbPrenomFeminin);
    return listePrenomsFemme[rand() % nbPrenomFeminin];
}

//-------------------------------------------
//
//          getNomFamille
//
//-------------------------------------------
char *getNomFamille(void){
    int nbNomFamille = sizeof(listeNomFamille) / 20;
    //printf("nombre de noms de famille disponibles : %d\n", nbNomFamille);
    return listeNomFamille[rand() % nbNomFamille];
}

//-------------------------------------------
//
//          getRandomGenre
//
//-------------------------------------------
int getRandomGenre(void){
    int tmp = rand() % 20;
    tmp /= 10;
    tmp += 1;
    return tmp;
}

//-------------------------------------------
//
//          getRandomEnfant
//
//-------------------------------------------
enfantDieu child;
enfantDieu getRandomEnfant(void){

    /*
    child.genre = rand() % 20;
    printf("child.genre : %d\n", child.genre);
    child.genre /= 10;
    printf("child.genre : %d\n", child.genre);
    child.genre += 1;
    printf("child.genre : %d\n", child.genre);
    */
   child.genre = getRandomGenre();
    strcpy(child.nom, getNomFamille());
    
    switch(child.genre){
        case HOMME:
            strcpy(child.prenom, getPrenomMasculin());
            break;
        case FEMME:
            strcpy(child.prenom, getPrenomFeminin());
            break;
    }
    printf("enfant retourne : %s %s (%d)\n", child.nom, child.prenom, child.genre);

    return child;
}

//-------------------------------------------
//
//          afficheListeHumains
//
//-------------------------------------------
void afficheListeHumains(void){
    Humain *ptr;
    printf("nombres d'humains crees : %d\n", indexHumain);
    printf("+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    printf("|                   nom | status| genre | age  | solde banque |                      employeur |                       conjoint |                 pere |                 mere | nb enfants |\n");
    printf("+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    for (int i = 0 ; i < indexHumain ; i++){
        ptr = listeHumains[i];
        if (vivantsSeulement && (ptr->getStatus() == 'X')) {
            //printf("on imprime pas les morts \n");
            continue;
        }
        char genre = ptr->getGenreTexte()[0];
        char status = ptr->getStatus();
        char employeur[50]="";
        if (ptr->getEmployeur() != NULL){
            strcpy(employeur, ptr->getEmployeur());
        }
        char conjoint[50]="";
        if (ptr->getConjoint() != NULL){
            strcpy(conjoint, ptr->getConjoint()->getNomComplet());
        }
        char pere[50]="";
        if (ptr->getPere() != NULL){
            strcpy(pere, ptr->getPere()->getNomComplet());
        }
        char mere[50]="";
        if (ptr->getMere() != NULL){
            strcpy(mere, ptr->getMere()->getNomComplet());
        }
        printf("| %20s  |", ptr->getNomComplet());
        printf("   %c   |", status);
        printf("   %c   |", genre);
        printf(" %3d  |", ptr->getAge());
        printf("    %8d  |", ptr->getSoldeBancaire());
        printf(" %30s |", employeur);
        printf(" %30s |", conjoint);
        printf(" %20s |", pere);
        printf(" %20s |", mere);
        printf("    %2d      |",  ptr->getNbEnfants());
        if (ptr->getNbEnfants() != 0){
            for (int ii = 0 ; ii < ptr->getNbEnfants() ; ii++){
                printf(" %s,", ptr->getEnfant(ii)->getPrenom());
            }
        }
        printf("\n");
    }
    printf("+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    printf("\n");
}

//-------------------------------------------
//
//          afficheListeComptesBancaires
//
//-------------------------------------------
void afficheListeComptesBancaires(void){
    printf("+-------------------------------------------+\n");
    printf("|      Comptes bancaires                    |\n");
    printf("+------------------------+---------+--------+\n");
    printf("|             nom Client | num cpt |  solde |\n");
    printf("+------------------------+---------+--------+\n");
    for (int i = 0 ; i < nbComptesBancaires ; i++){
        if (listeComptesBancaires[i]->getNumCompte() != -1){
            CompteBancaire *item = listeComptesBancaires[i];
            printf("|   %20s |  %06d | %6d |\n", item->getNomClient(), item->getNumCompte(), item->getSolde());
        }
    }
    printf("+------------------------+--------+--------+\n");
}

//-------------------------------------------
//
//          afficheListeEntreprises
//
//-------------------------------------------
void afficheListeEntreprises(void){
    printf("+----------------------------------------------------+\n");
    printf("|      Entreprises                                   |\n");
    printf("+------------------------+-------------+-------------+\n");
    printf("|                   nom  |    typeProd |  nb salarie |\n");
    printf("+------------------------+-------------+-------------+\n");
    for (int i = 0 ; i < nbEntreprises ; i++){
        Entreprise *item = listeEntreprises[i];
        char typeProd[20];
        strcpy(typeProd, item->getTypeProd());
        printf("|   %20s |  %10s |      %6d |\n", item->getNom(), typeProd, item->getNbSalaries());
    }
    printf("+------------------------+-------------+-------------+\n");
}