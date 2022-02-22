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
/*
#include "../inc/humain.hpp"
#include "../inc/variables.hpp"
#include "../inc/compteBancaire.hpp"
*/
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
    //if (debugTools) printf("genere nombre aleatoire entre 0 et %d\n", range);
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
    //if (debugTools) printf("nombre de prenoms masculin disponibles : %d\n", nbPrenomMasculin);
    return listePrenomsHomme[rand() % nbPrenomMasculin];
}

//-------------------------------------------
//
//          getPrenomFeminin
//
//-------------------------------------------
char *getPrenomFeminin(void){
    int nbPrenomFeminin = sizeof(listePrenomsFemme) / 20;
    //if (debugTools) printf("nombre de prenoms feminin disponibles : %d\n", nbPrenomFeminin);
    return listePrenomsFemme[rand() % nbPrenomFeminin];
}

//-------------------------------------------
//
//          getNomFamille
//
//-------------------------------------------
char *getNomFamille(void){
    int nbNomFamille = sizeof(listeNomFamille) / 20;
    //if (debugTools) printf("nombre de noms de famille disponibles : %d\n", nbNomFamille);
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
    child.genre = getRandomGenre();
    strcpy(child.nom, getNomFamille());
    child.nbJours = 0;
    
    switch(child.genre){
        case HOMME:
            strcpy(child.prenom, getPrenomMasculin());
            break;
        case FEMME:
            strcpy(child.prenom, getPrenomFeminin());
            break;
    }
    if (debugTools) printf("enfant retourne : %s %s (%d)\n", child.nom, child.prenom, child.genre);

    return child;
}
//-------------------------------------------
//
//          getRandomEnfant
//
//-------------------------------------------
enfantDieu getRandomEnfant(int nbJours){

    child = getRandomEnfant();
    child.nbJours = nbJours;
    if (debugTools) printf("Enfant de dieu initialise a l'age de %d\n", child.nbJours);
    return child;
}

//-------------------------------------------
//
//          afficheListeHumains
//
//-------------------------------------------
void afficheListeHumains(void){
    debugTools=true;
    Humain *ptr;
    if (debugTools) printf("nombres d'humains crees : %d\n", nbHumains);
    if (debugTools) printf("+------+-----------------------+-------+-------+------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    if (debugTools) printf("|  id  |                   nom | status| genre | age  |Pt vie| solde banque |                      employeur |                       conjoint |                 pere |                 mere | nb enfants |\n");
    if (debugTools) printf("+------+-----------------------+-------+-------+------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    for (int i = 0 ; i < nbHumains ; i++){
        ptr = listeHumains[i];
        if (vivantsSeulement && (ptr->getStatus() == 'X')) {
            //if (debugTools) printf("on imprime pas les morts \n");
            continue;
        }
        char genre = ptr->getGenreTexte()[0];
        char status = ptr->getStatus();
        char employeur[50]="";
        if (ptr->getEmployeur() != NULL){
            strcpy(employeur, ptr->getEmployeur()->getNom());
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
        if (debugTools) printf("| %3d  |", ptr->getId());
        if (debugTools) printf(" %20s  |", ptr->getNomComplet());
        if (debugTools) printf("   %c   |", status);
        if (debugTools) printf("   %c   |", genre);
        if (debugTools) printf(" %3d  |", ptr->getAge());
        if (debugTools) printf(" %3d  |", ptr->getPointsDeVie());
        if (debugTools) printf("    %8d  |", ptr->getSoldeBancaire());
        if (debugTools) printf(" %30s |", employeur);
        if (debugTools) printf(" %30s |", conjoint);
        if (debugTools) printf(" %20s |", pere);
        if (debugTools) printf(" %20s |", mere);
        if (debugTools) printf("    %2d      |",  ptr->getNbEnfants());
        if (ptr->getNbEnfants() != 0){
            for (int ii = 0 ; ii < ptr->getNbEnfants() ; ii++){
                if (debugTools) printf(" %s,", ptr->getEnfant(ii)->getPrenom());
            }
        }
        if (debugTools) printf("\n");
    }
    if (debugTools) printf("+------+-----------------------+-------+-------+------+------+--------------+--------------------------------+--------------------------------+----------------------+----------------------+------------+\n");
    if (debugTools) printf("\n");
}

//-------------------------------------------
//
//          afficheListeComptesBancaires
//
//-------------------------------------------
void afficheListeComptesBancaires(void){
    debugTools=true;
    if (debugTools) printf("+-------------------------------------------+\n");
    if (debugTools) printf("|      Comptes bancaires                    |\n");
    if (debugTools) printf("+------------------------+---------+--------+\n");
    if (debugTools) printf("|             nom Client | num cpt |  solde |\n");
    if (debugTools) printf("+------------------------+---------+--------+\n");
    for (int i = 0 ; i < nbComptesBancaires ; i++){
        if (listeComptesBancaires[i]->getNumCompte() != -1){
            CompteBancaire *item = listeComptesBancaires[i];
            if (debugTools) printf("|   %20s |  %06d | %6d |\n", item->getNomClient(), item->getNumCompte(), item->getSolde());
        }
    }
    if (debugTools) printf("+------------------------+---------+--------+\n");
}

//-------------------------------------------
//
//          afficheListeEntreprises
//
//-------------------------------------------
void afficheListeEntreprises(void){
    debugTools=true;
    if (debugTools) printf("+--------------------------------------+\n");
    if (debugTools) printf("|      Entreprises     (%3d)           |\n", nbEntreprises);
    if (debugTools) printf("+------------------------+-------------+\n");
    if (debugTools) printf("|                   nom  |  nb salarie |\n");
    if (debugTools) printf("+------------------------+-------------+\n");
    Entreprise *item;
    for (int i = 0 ; i < MAX_ENTREPRISES ; i++){
        item = listeEntreprises[i];
        if (item != NULL){
            if (debugTools) printf("|   %20s |      %6d |\n", item->getNom(), item->getNbSalaries());
        }
    }
    if (debugTools) printf("+------------------------+-------------+\n");
}

//-------------------------------------------
//
//          afficheListeProduits
//
//-------------------------------------------
void afficheListeProduits(void){
    debugTools=true;
    if (debugTools) printf("+-----------------------------------------------------------------------------+\n");
    if (debugTools) printf("|      produits                                                               |\n");
    if (debugTools) printf("+-----------------------+-----------------------+---------+---------+---------+\n");
    if (debugTools) printf("|           entreprise  |       nom du produit  |    prix |  stock  | stk min |\n");
    if (debugTools) printf("+-----------------------+-----------------------+---------+---------+---------+\n");
    Produit *ptrProduit;
    Entreprise *ptrEnt;
    for (int i = 0 ; i < nbEntreprises ; i++){
        ptrEnt = listeEntreprises[i];
        int j=0;
        ptrProduit = listeProduits[j];
        while (ptrProduit != NULL){
            if (ptrEnt->isInCatalogue(ptrProduit)){
                if (debugTools) printf("|  %20s |  %20s |  %6d |  %6d |  %6d |\n", ptrEnt->getNom(), 
                    ptrProduit->getNom(), ptrProduit->getPrix(), ptrProduit->getStock(), ptrProduit->getStockMini());
            }
            ptrProduit = listeProduits[++j];
        }
    }
    if (debugTools) printf("+-----------------------+-----------------------+---------+---------+---------+\n");
}

//-------------------------------------------
//
//          afficheListeCommandes
//
//-------------------------------------------
void afficheListeCommandes(void){
    debugTools=true;
    if (debugTools) printf("+---------------------------------------------------------------------------------+\n");
    if (debugTools) printf("|      commandes                                                                  |\n");
    if (debugTools) printf("+-----------------------+-----------------------+-----------------------+---------+\n");
    if (debugTools) printf("|           entreprise  |               client  |       nom du produit  |    qte  |\n");
    if (debugTools) printf("+-----------------------+-----------------------+-----------------------+---------+\n");
    for (int i = 0 ; i < nbCommandes ; i++){
        Commande *ptrCommande = listeCommandes[i];
        while (ptrCommande != NULL){
            if (debugTools) printf("|  %20s |  %20s |  %20s |  %6d |\n", ptrCommande->getFabricant()->getNom(), 
                ptrCommande->getClient()->getNomComplet(), ptrCommande->getProduit()->getNom(), ptrCommande->getQuantite());
            ptrCommande = listeCommandes[++i];
        }
    }
    if (debugTools) printf("+-----------------------+-----------------------+-----------------------+---------+\n");
}

//-------------------------------------------
//
//          getEntrepriseById
//
//-------------------------------------------
Entreprise *getEntrepriseById(int id){
    //if (debugTools) printf("tools::getEntrepriseById => debut (%d)\n", id);
    Entreprise *ptrEntreprise;
    for (int i = 0 ; i < nbEntreprises ; i++){
        ptrEntreprise = listeEntreprises[i];
        if (ptrEntreprise->getId() == id){
            //if (debugTools) printf("tools::getEntrepriseById => entreprise trouvee");
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
    if (debugTools) printf("tools::getHumainById => debut (%d)\n", id);
    Humain *ptr;
    for (int i = 0 ; i < nbHumains ; i++){
        ptr = listeHumains[i];
        if (ptr->getId() == id){
            return ptr;
        }
    }
    return NULL;
}

//-------------------------------------------
//
//          getProduitById
//
//-------------------------------------------
Produit *getProduitById(int id){
    //debugTools=true;
    if (debugTools) printf("tools::getProduitById => debut (%d) : ", id);
    Produit *ptr;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptr = listeProduits[i];
        if (ptr != NULL){
            if (ptr->getId() == id){
                //if (debugTools) printf("OK (%s)\n", ptr->getNom());
                debugTools=false;
                return ptr;
            }
        }
    }
    //if (debugTools) printf("KO\n");
    debugTools=false;
    return NULL;
}

//-------------------------------------------
//
//          getProduitByNom
//
//-------------------------------------------
Produit *getProduitByNom(char *nom){
    if (debugTools) printf("tools::getProduitByNom => debut (%s) parmi %d produits disponible : ", nom, nbProduits);
    Produit *ptr;
    for (int i = 0 ; i < nbProduits ; i++){
        ptr = listeProduits[i];
        if (ptr != NULL){
            if (strcmp(ptr->getNom(),nom) == 0){
                if (debugTools) printf("=> OK (%s)\n", ptr->getNom());
                return ptr;
            }
        }
    }
    if (debugTools) printf("=> KO\n");
    return NULL;
}

//-------------------------------------------
//
//          getCommandeById
//
//-------------------------------------------
Commande *getCommandeById(int id){
    if (debugTools) printf("getProducteur => debut\n");
    Commande *ptr;
    for (int i = 0 ; i < nbCommandes ; i++){
        ptr = listeCommandes[i];
        if (ptr->getNumero() == id){
            return ptr;
        }
    }
    return NULL;
}