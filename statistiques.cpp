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
int nbVivants=0;


//-------------------------------------------
//
//          getNbVivants
//
//-------------------------------------------
int getNbVivants(void){
    return nbVivants;
}

//-------------------------------------------
//
//          statistiques
//
//-------------------------------------------
void statistiques(void){

    int nbHommes=0;
    int nbHommesMorts=0;
    int nbHommesVivants=0;
    int nbFemmes=0;
    int nbFemmesMortes=0;
    int nbFemmesVivantes=0;
    int nbCouples=0;
    int nbCelibataires=0;
    int nbDivorces=0;
    int nbveufs=0;
    int nbMorts=0;
    int nb00_20ans=0;
    int nb20_40ans=0;
    int nb40_60ans=0;
    int nb60_plus=0;
    Humain *ptr;

    for (int i = 1 ; i < indexHumain ; i++){
        ptr = listeHumains[i];
        if (strcmp(ptr->getGenreTexte(),"Homme") == 0) {
            nbHommes++;
            if (ptr->getStatus() == 'X') {
                nbHommesMorts++;
            }
        }
        if (strcmp(ptr->getGenreTexte(),"Femme") == 0) {
            nbFemmes++;
            if (ptr->getStatus() == 'X') {
                nbFemmesMortes++;
            }
        }
        if (ptr->getStatus() == 'M') nbCouples++;
        if (ptr->getStatus() == 'C') nbCelibataires++;
        if (ptr->getStatus() == 'D') nbDivorces++;
        if (ptr->getStatus() == 'V') nbveufs++;
        if (ptr->getStatus() == 'X') nbMorts++;
        int age = ptr->getAge();
        if (ptr->getStatus() != 'X'){
            if (age <= 20) {
                nb00_20ans++;
            } else if( age <= 40 ){ 
                nb20_40ans++;
            } else if ( age <= 60) {
                nb40_60ans++;
            } else{
                nb60_plus++;
            }
        }
    }
    nbVivants = indexHumain - 1 - nbMorts;
    nbHommesVivants = nbHommes - nbHommesMorts;
    nbFemmesVivantes = nbFemmes - nbFemmesMortes;
    nbCouples /= 2; // divise par 2 car on compte les deux membres du couple marie

    printf("+---------------------------------------------------+\n");
    printf("|                statistiques                       |\n");
    printf("+-------------------+---------------+---------------+\n");
    printf("|        Item       +    nb total   +   nb vivants  |\n");
    printf("+-------------------+---------------+---------------+\n");
    printf("| population totale |  %5d        |  %5d        |\n", indexHumain - 1, nbVivants);
    printf("| nb hommes         |  %5d        |  %5d        |\n", nbHommes, nbHommesVivants);
    printf("| nb femmes         |  %5d        |  %5d        |\n", nbFemmes, nbFemmesVivantes);
    printf("| nb couples        |  %5d        |               |\n", nbCouples);
    printf("| nb celibataire    |  %5d        |               |\n", nbCelibataires);
    printf("| nb divorces       |  %5d        |               |\n", nbDivorces);
    printf("| nb veufs          |  %5d        |               |\n", nbveufs);
    printf("| nb morts          |  %5d        |               |\n", nbMorts);
    printf("| nb entreprises    |  %5d        |               |\n", nbEntreprises);
    printf("| nb cpt bancaires  |  %5d        |               |\n", nbComptesBancaires);
    printf("+-------------------+---------------+---------------+\n");
    printf("|        repartition par age                        |\n");
    printf("+------------+------------+------------+------------+\n");
    printf("|   00 - 20  |   20 - 40  |   40 - 60  |   60 et +  |\n");
    printf("+------------+------------+------------+------------+\n");
    printf("|    %3d     |    %3d     |    %3d     |    %3d     |\n", nb00_20ans, nb20_40ans, nb40_60ans, nb60_plus);
    printf("+------------+------------+------------+------------+\n");

}