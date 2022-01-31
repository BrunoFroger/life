//-----------------------------------
//
//      statistiques.cpp
//
//-----------------------------------

#include "variables.hpp"
#include "tools.hpp"
#include "humain.hpp"
#include "entreprise.hpp"
#include "compteBancaire.hpp"

#define NB_MAX_ENFANTS  1000

int nbEnfants = 0;
int listeEnfants[NB_MAX_ENFANTS];
int nbVivants=0;
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
int hommes00_20ans=0;
int hommes20_40ans=0;
int hommes40_60ans=0;
int hommes60_plus=0;
int femmes00_20ans=0;
int femmes20_40ans=0;
int femmes40_60ans=0;
int femmes60_plus=0;
bool display_stat_humain = true;
bool display_stat_variables = true;
bool display_stat_cptBanque = true;
bool display_stat_entreprises = true;
bool display_stat_produits = true;
bool display_stat_salaries = true;
bool display_stat_commandes = true;

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
//          displayDatas
//
//-------------------------------------------
void displayDatas(void){    
    char string1[40][200], string2[40][200];
    int numLigne1=0, numLigne2=0;
    if (display_stat_humain){
        sprintf(string1[numLigne1++], "+---------------------------------------------------+");
        sprintf(string1[numLigne1++], "|                statistiques                       |");
        sprintf(string1[numLigne1++], "+-------------------+---------------+---------------+");
        sprintf(string1[numLigne1++], "|        Item       +    nb total   +   nb vivants  |");
        sprintf(string1[numLigne1++], "+-------------------+---------------+---------------+");
        sprintf(string1[numLigne1++], "| population totale |  %5d        |  %5d        |", indexHumain - 1, nbVivants);
        sprintf(string1[numLigne1++], "| nb hommes         |  %5d        |  %5d        |", nbHommes, nbHommesVivants);
        sprintf(string1[numLigne1++], "| nb femmes         |  %5d        |  %5d        |", nbFemmes, nbFemmesVivantes);
        sprintf(string1[numLigne1++], "| nb couples        |  %5d        |               |", nbCouples);
        sprintf(string1[numLigne1++], "| nb celibataire    |  %5d        |               |", nbCelibataires);
        sprintf(string1[numLigne1++], "| nb divorces       |  %5d        |               |", nbDivorces);
        sprintf(string1[numLigne1++], "| nb veufs          |  %5d        |               |", nbveufs);
        sprintf(string1[numLigne1++], "| nb morts          |  %5d        |               |", nbMorts);
        sprintf(string1[numLigne1++], "| nb entreprises    |  %5d        |               |", nbEntreprises);
        sprintf(string1[numLigne1++], "| nb cpt bancaires  |  %5d        |               |", nbComptesBancaires);
        sprintf(string1[numLigne1++], "+-------------------+---------------+---------------+------------+");
        sprintf(string1[numLigne1++], "|        repartition par age                                     |");
        sprintf(string1[numLigne1++], "+------------+------------+------------+------------+------------+");
        sprintf(string1[numLigne1++], "|            |   00 - 20  |   20 - 40  |   40 - 60  |   60 et +  |");
        sprintf(string1[numLigne1++], "+------------+------------+------------+------------+------------+");
        sprintf(string1[numLigne1++], "|   total    |    %3d     |    %3d     |    %3d     |    %3d     |", nb00_20ans, nb20_40ans, nb40_60ans, nb60_plus);
        sprintf(string1[numLigne1++], "|   hommes   |    %3d     |    %3d     |    %3d     |    %3d     |", hommes00_20ans, hommes20_40ans, hommes40_60ans, hommes60_plus);
        sprintf(string1[numLigne1++], "|   femmes   |    %3d     |    %3d     |    %3d     |    %3d     |", femmes00_20ans, femmes20_40ans, femmes40_60ans, femmes60_plus);
        sprintf(string1[numLigne1++], "+------------+------------+------------+------------+------------+");
    }

    if (display_stat_variables){
        sprintf(string2[numLigne2++], "+----------------------------------+");
        sprintf(string2[numLigne2++], "|   variables d'affichage          |");
        sprintf(string2[numLigne2++], "+------------------+---------+-----+");
        sprintf(string2[numLigne2++], "|  variable        |  valeur | cde |");
        sprintf(string2[numLigne2++], "+------------------+---------+-----+");
        sprintf(string2[numLigne2++], "| stat humains     | %7s |   %c |",  getstringBoolean(display_stat_humain), 'A');
        sprintf(string2[numLigne2++], "| variables        | %7s |   %c |",  getstringBoolean(display_stat_variables), 'B');
        sprintf(string2[numLigne2++], "| stat cpt banque  | %7s |   %c |",  getstringBoolean(display_stat_cptBanque), 'C');
        sprintf(string2[numLigne2++], "| stat entreprises | %7s |   %c |",  getstringBoolean(display_stat_entreprises), 'D');
        sprintf(string2[numLigne2++], "| stat produits    | %7s |   %c |",  getstringBoolean(display_stat_produits), 'E');
        sprintf(string2[numLigne2++], "| stat salariés    | %7s |   %c |",  getstringBoolean(display_stat_salaries), 'F');
        sprintf(string2[numLigne2++], "| stat commandes   | %7s |   %c |",  getstringBoolean(display_stat_commandes), 'G');
        sprintf(string2[numLigne2++], "| aff menu auto    | %7s |   %c |",  getstringBoolean(menuOnOff), 'm');
        sprintf(string2[numLigne2++], "| aff stat auto    | %7s |   %c |",  getstringBoolean(statAuto), 'b');
        sprintf(string2[numLigne2++], "| aff liste auto   | %7s |   %c |",  getstringBoolean(listeAuto), 'a');
        sprintf(string2[numLigne2++], "+------------------+---------+-----+");
    }
    int i = 0;
    while (true){
        if (i < numLigne1) printf("%-80s    ",string1[i]);
        if (i < numLigne2) printf("%s", string2[i]);
        if (( i >= numLigne1) && (i > numLigne2) ) break;
        i++;
        printf("\n");
    }

    // affichage des comptes bancaires
    numLigne1=0;
    numLigne2=0;
    if (display_stat_cptBanque){
        sprintf(string1[numLigne1++], "+-------------------------------------------+");
        sprintf(string1[numLigne1++], "|      Comptes bancaires                    |");
        sprintf(string1[numLigne1++], "+------------------------+---------+--------+");
        sprintf(string1[numLigne1++], "|             nom Client | num cpt |  solde |");
        sprintf(string1[numLigne1++], "+------------------------+---------+--------+");
        for (int i = 0 ; i < nbComptesBancaires ; i++){
            if (listeComptesBancaires[i]->getNumCompte() != -1){
                CompteBancaire *item = listeComptesBancaires[i];
                sprintf(string1[numLigne1++], "|   %20s |  %06d | %6d |", item->getNomClient(), item->getNumCompte(), item->getSolde());
            }
        }
        sprintf(string1[numLigne1++], "+------------------------+---------+--------+");
    }

    if (display_stat_commandes){
        sprintf(string2[numLigne2++], "+---------------------------------------------------------------------------------+");
        sprintf(string2[numLigne2++], "|      commandes                                                                  |");
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+-----------------------+---------+");
        sprintf(string2[numLigne2++], "|           entreprise  |               client  |       nom du produit  |    qte  |");
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+-----------------------+---------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *ptrEnt = listeEntreprises[i];
            structCommande *ptrCommande;
            int j=0;
            ptrCommande = ptrEnt->getCommande(j++);
            while (ptrCommande != NULL){
                sprintf(string2[numLigne2++], "|  %20s |  %20s |  %20s |  %6d |", ptrEnt->getNom(), 
                    ptrCommande->client->getNomComplet(), ptrCommande->nomProduit, ptrCommande->quantite);
                ptrCommande = ptrEnt->getCommande(j++);
            }
        }
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+-----------------------+---------+");
    }
    i=0;
    while (true){
        if (i < numLigne1) printf("%-80s    ",string1[i]);
        if (i < numLigne2) {
            if (i >= numLigne1) printf("%-80s    "," ");
            printf("%s", string2[i]);
        }
        if (( i >= numLigne1) && (i > numLigne2) ) break;
        i++;
        printf("\n");
    }

    // affichage des entreprises
    numLigne1=0;
    numLigne2=0;
    if (display_stat_entreprises){
        sprintf(string1[numLigne1++], "+------------------------------------------------------------------+");
        sprintf(string1[numLigne1++], "|      Entreprises                                                 |");
        sprintf(string1[numLigne1++], "+------------------------+-------------+-------------+-------------+");
        sprintf(string1[numLigne1++], "|                   nom  |    typeProd |  nb salarie | effectif max|");
        sprintf(string1[numLigne1++], "+------------------------+-------------+-------------+-------------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *item = listeEntreprises[i];
            char typeProd[20];
            strcpy(typeProd, item->getTypeProd());
            sprintf(string1[numLigne1++], "|   %20s |  %10s |      %6d |      %6d |", 
                    item->getNom(), typeProd, item->getNbSalaries(), item->getEffectifMax());
            if (display_stat_salaries){
                for (int j = 0 ; j < item->getNbSalaries() ; j++){
                    structSalarie *employe = item->getSalarie(j);
                    
                }
            }
        }
        sprintf(string1[numLigne1++], "+------------------------+-------------+-------------+-------------+");
    }
    // affichage des produits
    if (display_stat_produits){
        sprintf(string2[numLigne2++], "+-----------------------------------------------------------------------------+");
        sprintf(string2[numLigne2++], "|      produits                                                               |");
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+---------+---------+---------+");
        sprintf(string2[numLigne2++], "|           entreprise  |       nom du produit  |    prix |  stock  | stk min |");
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+---------+---------+---------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *ptrEnt = listeEntreprises[i];
            structProduit *ptrProduit;
            int j=0;
            ptrProduit = ptrEnt->getProduit(j++);
            while (ptrProduit != NULL){
                sprintf(string2[numLigne2++], "|  %20s |  %20s |  %6d |  %6d |  %6d |", ptrEnt->getNom(), 
                    ptrProduit->nom, ptrProduit->prix, ptrProduit->stock, ptrProduit->stockMini);
                ptrProduit = ptrEnt->getProduit(j++);
            }
        }
        sprintf(string2[numLigne2++], "+-----------------------+-----------------------+---------+---------+---------+");
    }
    i=0;
    while (true){
        if (i < numLigne1) printf("%-80s    ",string1[i]);
        if (i < numLigne2) {
            if (i >= numLigne1) printf("%-80s    "," ");
            printf("%s", string2[i]);
        }
        if (( i >= numLigne1) && (i > numLigne2) ) break;
        i++;
        printf("\n");
    }



    // affichage des salaries
    numLigne1=0;
    numLigne2=0;
    if (display_stat_salaries){
        sprintf(string1[numLigne1++], "+--------------------------------------------------------------------+");
        sprintf(string1[numLigne1++], "|       liste des salaries de                                        |");
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+");
        sprintf(string1[numLigne1++], "|         entreprise   |                nom   |   fonction | salaire |");
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *ptrEnt = listeEntreprises[i];
            structSalarie *ptrSalarie;
            for (int j = 0 ; j < ptrEnt->getNbSalaries() ; j++){
                structSalarie *ptrSalarie = ptrEnt->getSalarie(j);
                sprintf(string1[numLigne1++], "| %20s | %20s | %10s |   %5d |", ptrEnt->getNom(), ptrSalarie->salarie->getNomComplet(), 
                    ptrEnt->getStatusString(ptrSalarie->status), ptrSalarie->remuneration);
            }
        }
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+\n");
    }
    i=0;
    while (true){
        if (i < numLigne1) printf("%-80s    ",string1[i]);
        if (i < numLigne2) {
            if (i >= numLigne1) printf("%-80s    "," ");
            printf("%s", string2[i]);
        }
        if (( i >= numLigne1) && (i > numLigne2) ) break;
        i++;
        printf("\n");
    }
}

//-------------------------------------------
//
//          statistiques
//
//-------------------------------------------
void statistiques(void){
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
                if (ptr->getGenreTexte()[0] == 'H'){
                    hommes00_20ans++;
                } else {
                    femmes00_20ans++;
                }
            } else if( age <= 40 ){ 
                nb20_40ans++;
                if (ptr->getGenreTexte()[0] == 'H'){
                    hommes20_40ans++;
                } else {
                    femmes20_40ans++;
                }
            } else if ( age <= 60) {
                if (ptr->getGenreTexte()[0] == 'H'){
                    hommes40_60ans++;
                } else {
                    femmes40_60ans++;
                }
                nb40_60ans++;
            } else{
                nb60_plus++;
                if (ptr->getGenreTexte()[0] == 'H'){
                    hommes60_plus++;
                } else {
                    femmes60_plus++;
                }
            }
        }
    }
    nbVivants = indexHumain - 1 - nbMorts;
    nbHommesVivants = nbHommes - nbHommesMorts;
    nbFemmesVivantes = nbFemmes - nbFemmesMortes;
    nbCouples /= 2; // divise par 2 car on compte les deux membres du couple marie

    displayDatas();

}