//-----------------------------------
//
//      commande.cpp
//
//-----------------------------------

#include <stdio.h>
#include <string>
#include <iostream>

#include "variables.hpp"

//-------------------------------------------
//
//          Commande::~Commande
//
//-------------------------------------------
Commande::~Commande(void){
    nbCommandes--;
}

//-------------------------------------------
//
//          Commande::Commande
//
//-------------------------------------------
Commande::Commande(Produit *produit, int qte, Humain *client){
    this->produit = produit;
    this->client = client;
    this->quantite = qte;
    Entreprise *ptrEntreprise;
    for (int i = 0; i < MAX_ENTREPRISES ; i++){
        ptrEntreprise = listeEntreprises[i];
        if (ptrEntreprise->isInCatalogue(produit)){
            this->fabricant = ptrEntreprise;
            this->status = COMMANDE_EN_COURS;
            nbCommandes++;
            return;
        }
    }
    // on a pas trouvé d'entreprise qui a ce produit en stock
    // il faut creer une entreprise qui fabrique ce produit
    printf("Commande::Commande => ERREUR : aucune entreprise ne fabrique ce produit %s\n", produit->getNom());
}

//-------------------------------------------
//
//          Commande::getStatus
//
//-------------------------------------------
int Commande::getStatus(void){
    return status;
}

//-------------------------------------------
//
//          Commande::traitement
//
//-------------------------------------------
void Commande::boucleTraitement(void){
    printf("Commande::boucleTraitement => boucleTraitement : debut\n");
    switch(this->status){
        case COMMANDE_INITIALISEE:
            printf("Commande::boucleTraitement => boucleTraitement : commande initialisee\n");
            // recherche d'une entreprise capable de founir ce produit
            // boucle sur les entreprises
            Entreprise *ptrEntreprise;
            Produit *ptrProduit;
            for (int i = 0 ; i < MAX_ENTREPRISES ; i++){
                ptrEntreprise = listeEntreprises[i];
                // boucle sur les produits de cette entreprise
                if (ptrEntreprise->produitEnStock(this->produit)){
                    // le produit est en stock, on accepte la commande
                    this->status = COMMANDE_EN_COURS;
                }
            }
            break;
        case COMMANDE_EN_COURS:
            printf("Commande::boucleTraitement => boucleTraitement : commande en cours\n");
            printf(" ..... TODO .....\n");
            break;
        case COMMANDE_DISPONIBLE:
            printf("Commande::boucleTraitement => boucleTraitement : commande disponible\n");
            printf(" ..... TODO .....\n");
            break;
        case COMMANDE_LIVREE:
            printf("Commande::boucleTraitement => boucleTraitement : commande livree\n");
            printf(" ..... TODO .....\n");
            break;
        default:
            printf("Commande::boucleTraitement => ERREUR : status incorrect %d\n", this->status);
    }
}

//-------------------------------------------
//
//          Commande::getStatusString
//
//-------------------------------------------
char *Commande::getStatusString(void){
    switch(status){
        case COMMANDE_INITIALISEE:
            return "INIT";
            break;
        case COMMANDE_EN_COURS:
            return "EN COURS";
            break;
        case COMMANDE_DISPONIBLE:
            return "DISPO";
            break;
        case COMMANDE_LIVREE:
            return "LIVREE";
            break;
    }
    return "INCONNU";
}

//-------------------------------------------
//
//          Commande::getClient
//
//-------------------------------------------
Humain *Commande::getClient(void){
    return this->client;
}

//-------------------------------------------
//
//          Commande::getFabricant
//
//-------------------------------------------
Entreprise *Commande::getFabricant(void){
    return this->fabricant;
}

//-------------------------------------------
//
//          Commande::getClient
//
//-------------------------------------------
Produit *Commande::getProduit(void){
    return this->produit;
}

//-------------------------------------------
//
//          Commande::getQuantite
//
//-------------------------------------------
int Commande::getQuantite(void){
    return this->quantite;
}

//-------------------------------------------
//
//          Commande::sauve
//
//-------------------------------------------
void Commande::sauve(FILE *fichier){
    printf("Commande::sauve => debut\n");
    printf("Commande::sauve => fin\n");
}