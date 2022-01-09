//-----------------------------------
//
//      statistiques.cpp
//
//-----------------------------------

#include "variables.hpp"
#include "humain.hpp"

#define NB_MAX_ENFANTS  1000

int nbEnfants = 0;
int listeEnfants[NB_MAX_ENFANTS];


void statistiques(void){

    int nbHommes=0;
    int nbFemmes=0;
    int nbCouples=0;
    int nbCelibataires=0;
    int nbDivorces=0;
    int nbveufs=0;
    int nbMorts=0;
    Humain *ptr;

    for (int i = 1 ; i < indexHumain ; i++){
        ptr = listeHumains[i];
        if (strcmp(ptr->getGenreTexte(),"Homme") == 0) nbHommes++;
        if (strcmp(ptr->getGenreTexte(),"Femme") == 0) nbFemmes++;
        if (ptr->getStatus() == 'M') nbCouples++;
        if (ptr->getStatus() == 'C') nbCelibataires++;
        if (ptr->getStatus() == 'D') nbDivorces++;
        if (ptr->getStatus() == 'V') nbveufs++;
        if (ptr->getStatus() == 'X') nbMorts++;
    }
    nbCouples /= 2; // divise par 2 car on compte les deux membres du couple marie
    printf("+-----------------------------------+\n");
    printf("|           statistiques            |\n");
    printf("+-------------------+---------------+\n");
    printf("| population totale |  %5d        |\n", indexHumain - 1);
    printf("| nb hommes         |  %5d        |\n", nbHommes);
    printf("| nb femmes         |  %5d        |\n", nbFemmes);
    printf("| nb couples        |  %5d        |\n", nbCouples);
    printf("| nb celibataire    |  %5d        |\n", nbCelibataires);
    printf("| nb divirces       |  %5d        |\n", nbDivorces);
    printf("| nb veufs          |  %5d        |\n", nbveufs);
    printf("| nb morts          |  %5d        |\n", nbMorts);
    printf("+-------------------+---------------+\n");

}