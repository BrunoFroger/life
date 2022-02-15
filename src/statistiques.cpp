//-----------------------------------
//
//      statistiques.cpp
//
//-----------------------------------

#include "../inc/variables.hpp"
#include "../inc/tools.hpp"

#define TAILLE_TABLEAU  85
#define NB_COLONNES     3
#define NB_LIGNES       40
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
char string1[40][200], string2[40][200], string3[40][200];
char blocs[NB_COLONNES][NB_LIGNES][200];
int numLigne1=0, numLigne2=0, numLigne3=0;
int numLignes[NB_COLONNES];
char displayNomFichier[50];

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
//          displayBloc
//
//-------------------------------------------
void displayBloc(void){
    int i = 0;
    //printf("display bloc : i=%d, numLigne1=%d, numLigne2=%d, numLigne3=%d\n", i, numLigne1, numLigne2, numLigne3);
    while (true){
        if (i < numLigne1){
            printf("%-*s",TAILLE_TABLEAU, string1[i]);
        } else if (i >= numLigne1) {
            printf("%-*s",TAILLE_TABLEAU, "  ");
        }

        if (i < numLigne2){
            printf("%-*s",TAILLE_TABLEAU, string2[i]);
        } else if (i >= numLigne2) {
            printf("%-*s",TAILLE_TABLEAU, "  ");
        }

        if (i < numLigne3) {
            printf("%-s", string3[i]);
        }

        if (( i >= numLigne1) && (i >= numLigne2)  && (i >= numLigne3) ) break;
        i++;
        printf("\n");
    }
    printf("\n");
    numLigne1=0;
    numLigne2=0;
    numLigne3=0;
    i=0;
}

//-------------------------------------------
//
//          displayDatas
//
//-------------------------------------------
void displayDatas(void){    
    if (display_stat_humain){
        sprintf(string1[numLigne1++], "+---------------------------------------------------+");
        sprintf(string1[numLigne1++], "|    statistiques %-25s         |", displayNomFichier);
        sprintf(string1[numLigne1++], "+-------------------+---------------+---------------+");
        sprintf(string1[numLigne1++], "|        Item       +    nb total   +   nb vivants  |");
        sprintf(string1[numLigne1++], "+-------------------+---------------+---------------+");
        sprintf(string1[numLigne1++], "| population totale |  %5d        |  %5d        |", nbHumains - 1, nbVivants);
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
    // affichage des comptes bancaires
    if (display_stat_cptBanque){
        sprintf(string3[numLigne3++], "+-------------------------------------------+");
        sprintf(string3[numLigne3++], "|      Comptes bancaires                    |");
        sprintf(string3[numLigne3++], "+------------------------+---------+--------+");
        sprintf(string3[numLigne3++], "|             nom Client | num cpt |  solde |");
        sprintf(string3[numLigne3++], "+------------------------+---------+--------+");
        for (int i = 0 ; i < nbComptesBancaires ; i++){
            if (listeComptesBancaires[i]->getNumCompte() != -1){
                CompteBancaire *item = listeComptesBancaires[i];
                sprintf(string3[numLigne3++], "|   %20s |  %06d | %6d |", item->getNomClient(), item->getNumCompte(), item->getSolde());
            }
        }
        sprintf(string3[numLigne3++], "+------------------------+---------+--------+");
    }
    displayBloc();


    // affichage des entreprises
    if (display_stat_entreprises){
        sprintf(string2[numLigne2++], "+----------------------------------------------------+");
        sprintf(string2[numLigne2++], "|      Entreprises                                   |");
        sprintf(string2[numLigne2++], "+------------------------+-------------+-------------+");
        sprintf(string2[numLigne2++], "|                   nom  |  nb salarie | effectif max|");
        sprintf(string2[numLigne2++], "+------------------------+-------------+-------------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *item = listeEntreprises[i];
            sprintf(string2[numLigne2++], "|   %20s |      %6d |      %6d |", 
                    item->getNom(), item->getNbSalaries(), item->getEffectifMax());
        }
        sprintf(string2[numLigne2++], "+------------------------+-------------+-------------+");
    }

    // affichage des salaries
    if (display_stat_salaries){
        sprintf(string1[numLigne1++], "+--------------------------------------------------------------------+");
        sprintf(string1[numLigne1++], "|       liste des salaries par entreprise                            |");
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+");
        sprintf(string1[numLigne1++], "|         entreprise   |                nom   |   fonction | salaire |");
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+");
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *ptrEnt = listeEntreprises[i];
            for (int j = 0 ; j < ptrEnt->getNbSalaries() ; j++){
                structSalarie *ptrSalarie = ptrEnt->getSalarie(j);
                sprintf(string1[numLigne1++], "| %20s | %20s | %10s |   %5d |", ptrEnt->getNom(), ptrSalarie->salarie->getNomComplet(), 
                    ptrEnt->getStatusString(ptrSalarie->status), ptrSalarie->remuneration);
            }
        }
        sprintf(string1[numLigne1++], "+----------------------+----------------------+------------+---------+\n");
    }
    displayBloc();


    // affichage des produits
    if (display_stat_produits){
        sprintf(string1[numLigne1++], "+-----------------------------------------------------------------------------+");
        sprintf(string1[numLigne1++], "|      produits                                                               |");
        sprintf(string1[numLigne1++], "+-----------------------+-----------------------+---------+---------+---------+");
        sprintf(string1[numLigne1++], "|           entreprise  |       nom du produit  |    prix |  stock  | stk min |");
        sprintf(string1[numLigne1++], "+-----------------------+-----------------------+---------+---------+---------+");
        /*
        for (int i = 0 ; i < nbEntreprises ; i++){
            Entreprise *ptrEnt = listeEntreprises[i];
            structProduit *ptrProduit;
            int j=0;
            ptrProduit = ptrEnt->getProduit(j++);
            while (ptrProduit != NULL){
                sprintf(string1[numLigne1++], "|  %20s |  %20s |  %6d |  %6d |  %6d |", ptrEnt->getNom(), 
                    ptrProduit->nom, ptrProduit->prix, ptrProduit->stock, ptrProduit->stockMini);
                ptrProduit = ptrEnt->getProduit(j++);
            }
        }*/
        Produit *ptrProduit;
        Entreprise *ptrEntreprise;
        for (int i = 0 ; i < MAX_PRODUITS ; i++){
            ptrProduit = listeProduits[i];
            if (ptrProduit != NULL){
                ptrEntreprise = getEntrepriseById(ptrProduit->getProducteurId());
                sprintf(string1[numLigne1++], "|  %20s |  %20s |  %6d |  %6d |  %6d |", ptrEntreprise->getNom(), 
                    ptrProduit->getNom(), ptrProduit->getPrix(), ptrProduit->getStock(), ptrProduit->getStockMini());
            }
        }
        sprintf(string1[numLigne1++], "+-----------------------+-----------------------+---------+---------+---------+");
    }
    if (display_stat_commandes){
        sprintf(string2[numLigne2++], "+----------------------------------------------------------------------------------------------------------+");
        sprintf(string2[numLigne2++], "|      commandes                                                                                           |");
        sprintf(string2[numLigne2++], "+-----------+-----------------------+-----------------------+-----------------------+---------+------------+");
        sprintf(string2[numLigne2++], "|  num cde  |           entreprise  |               client  |       nom du produit  |    qte  |     status |");
        sprintf(string2[numLigne2++], "+-----------+-----------------------+-----------------------+-----------------------+---------+------------+");
        Commande *ptrCommande;
        //printf("nbCommandes = %d\n", nbCommandes);
        for (int i = 0 ; i < MAX_COMMANDES ; i++){
            //printf("test commande %d\n", i);
            ptrCommande = listeCommandes[i];
            //printf("ptrCommande initialise\n");
            if (ptrCommande != NULL){
                //printf("ptrCommande != null\n");
                sprintf(string2[numLigne2++], "|  %5d    |  %20s |  %20s |  %20s |  %6d | %10s |", ptrCommande->getNumero(), ptrCommande->getFabricant()->getNom(), 
                    ptrCommande->getClient()->getNomComplet(), ptrCommande->getProduit()->getNom(), 
                    ptrCommande->getQuantite(), ptrCommande->getStatusString());
            }
        }
        sprintf(string2[numLigne2++], "+-----------+-----------------------+-----------------------+-----------------------+---------+------------+");
    }
    displayBloc();
}

//-------------------------------------------
//
//          statistiques
//
//-------------------------------------------
void statistiques(void){
    Humain *ptr;
    if (strlen(nomFichier) > 0){
        sprintf(displayNomFichier, "fichier %s", nomFichier);
    } else {
        strcpy(displayNomFichier, "");
    }
    for (int i = 1 ; i < nbHumains ; i++){
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
    nbVivants = nbHumains - 1 - nbMorts;
    nbHommesVivants = nbHommes - nbHommesMorts;
    nbFemmesVivantes = nbFemmes - nbFemmesMortes;
    nbCouples /= 2; // divise par 2 car on compte les deux membres du couple marie

    displayDatas();

}