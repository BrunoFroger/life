//-----------------------------------
//
//      tools.cpp
//
//-----------------------------------

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include "../inc/tools.hpp"
#include "../inc/humain.hpp"
#include "../inc/variables.hpp"
#include "../inc/compteBancaire.hpp"

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
//          getstringBoolean
//
//-------------------------------------------
char *getstringBoolean(bool val){
    if (val){
        strcpy(tmpString, "true");
    } else {
        strcpy(tmpString, "false");
    }
    return tmpString;
}
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
    //printf("enfant retourne : %s %s (%d)\n", child.nom, child.prenom, child.genre);

    return child;
}

//-------------------------------------------
//
//          afficheListeHumains
//
//-------------------------------------------
void afficheListeHumains(void){
    Humain *ptr;
    printf("nombres d'humains crees : %d\n", nbHumains);
    printf("+------+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    printf("|  id  |                   nom | status| genre | age  | solde banque |                      employeur |                       conjoint |                 pere |                 mere | nb enfants |\n");
    printf("+------+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    for (int i = 0 ; i < nbHumains ; i++){
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
        printf("| %3d  |", ptr->getId());
        printf(" %20s  |", ptr->getNomComplet());
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
    printf("+------+-----------------------+-------+-------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
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
    printf("+------------------------+---------+--------+\n");
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

//-------------------------------------------
//
//          afficheListeProduits
//
//-------------------------------------------
void afficheListeProduits(void){
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|      produits                                                               |\n");
    printf("+-----------------------+-----------------------+---------+---------+---------+\n");
    printf("|           entreprise  |       nom du produit  |    prix |  stock  | stk min |\n");
    printf("+-----------------------+-----------------------+---------+---------+---------+\n");
    for (int i = 0 ; i < nbEntreprises ; i++){
        Entreprise *ptrEnt = listeEntreprises[i];
        structProduit *ptrProduit;
        int j=0;
        ptrProduit = ptrEnt->getProduit(j++);
        while (ptrProduit != NULL){
            printf("|  %20s |  %20s |  %6d |  %6d |  %6d |\n", ptrEnt->getNom(), 
                ptrProduit->nom, ptrProduit->prix, ptrProduit->stock, ptrProduit->stockMini);
            ptrProduit = ptrEnt->getProduit(j++);
        }
    }
    printf("+-----------------------+-----------------------+---------+---------+---------+\n");
}

//-------------------------------------------
//
//          afficheListeCommandes
//
//-------------------------------------------
/*void afficheListeCommandes(void){
    printf("+---------------------------------------------------------------------------------+\n");
    printf("|      commandes                                                                  |\n");
    printf("+-----------------------+-----------------------+-----------------------+---------+\n");
    printf("|           entreprise  |               client  |       nom du produit  |    qte  |\n");
    printf("+-----------------------+-----------------------+-----------------------+---------+\n");
    for (int i = 0 ; i < nbEntreprises ; i++){
        Entreprise *ptrEnt = listeEntreprises[i];
        structCommande *ptrCommande;
        int j=0;
        ptrCommande = ptrEnt->getCommande(j++);
        while (ptrCommande != NULL){
            printf("|  %20s |  %20s |  %20s |  %6d |\n", ptrEnt->getNom(), 
                ptrCommande->client->getNomComplet(), ptrCommande->nomProduit, ptrCommande->quantite);
            ptrCommande = ptrEnt->getCommande(j++);
        }
    }
    printf("+-----------------------+-----------------------+-----------------------+---------+\n");
}*/

//-------------------------------------------
//
//          getProducteur
//
//-------------------------------------------
Entreprise *getProducteur(char *produit){
    //printf("getProducteur => debut\n");
    Entreprise *ptrEntreprise;
    for (int i = 0 ; i < MAX_ENTREPRISES ; i++){
        ptrEntreprise = listeEntreprises[i];
        //printf("getProducteur => test entreprise %s\n", ptrEntreprise->getNom());
        if (ptrEntreprise->isInCatalogue(produit)){
            return ptrEntreprise;
        }
    }
    return NULL;
}

//-------------------------------------------
//
//          getEntrepriseById
//
//-------------------------------------------
Entreprise *getEntrepriseById(int id){
    //printf("getProducteur => debut\n");
    Entreprise *ptrEntreprise;
    for (int i = 0 ; i < nbEntreprises ; i++){
        ptrEntreprise = listeEntreprises[i];
        if (ptrEntreprise->getId() == id){
            return ptrEntreprise;
        }
    }
    return NULL;
}

//-------------------------------------------
//
//          getHumainById
//
//-------------------------------------------
Humain *getHumainById(int id){
    //printf("getProducteur => debut\n");
    Humain *ptr;
    for (int i = 0 ; i < nbHumains ; i++){
        ptr = listeHumains[i];
        if (ptr->getId() == id){
            return ptr;
        }
    }
    return NULL;
}