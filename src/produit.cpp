//-----------------------------------
//
//      produit.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "../inc/produit.hpp"

//-------------------------------------------
//
//          Produit::Produit
//
//-------------------------------------------
Produit::Produit(char *nom, int type, int producteur_id, int stockInitial, int stockMini, int prix, int coutFabrication, int dureeVie, int delaiFab, int indiceNecessite){
    debugProduit = true;
    if (debugProduit) printf("Produit::Produit => creation du produit %s en position %d\n", nom, nbProduits);
    this->id = nbProduits;
    strcpy(this->nom, nom);
    this->type = type;
    this->producteurId = producteur_id;
    this->stock = stockInitial;
    this->stockMini = stockMini;
    this->prix = prix;
    this->coutFabrication = coutFabrication;
    this->dureeVie = dureeVie;
    this->delaiFabrication = delaiFab;
    this->indiceNecessite = indiceNecessite;
    Entreprise *ptrEnt;
    ptrEnt = getEntrepriseById(producteur_id);
    if (ptrEnt != NULL){
        ptrEnt->addProduit(this);
    }
    listeProduits[nbProduits]=this;
    nbProduits++;
}

//-------------------------------------------
//
//          Produit::~Produit
//
//-------------------------------------------
Produit::~Produit(void){
    nbProduits--;
}

//-------------------------------------------
//
//          Produit::getNom
//
//-------------------------------------------
char *Produit::getNom(void){
    return this->nom;
}

//-------------------------------------------
//
//          Produit::getStock
//
//-------------------------------------------
int Produit::getStock(void){
    return this->stock;
}

//-------------------------------------------
//
//          Produit::getStockMini
//
//-------------------------------------------
int Produit::getStockMini(void){
    return this->stockMini;
}

//-------------------------------------------
//
//          Produit::getPrix
//
//-------------------------------------------
int Produit::getPrix(void){
    return this->prix;
}

//-------------------------------------------
//
//          Produit::getId
//
//-------------------------------------------
int Produit::getId(void){
    return this->id;
}

//-------------------------------------------
//
//          Produit::getProducteurId
//
//-------------------------------------------
int Produit::getProducteurId(void){
    return this->producteurId;
}

//-------------------------------------------
//
//          Produit::getQuantiteAProduire
//
//-------------------------------------------
int Produit::getQuantiteAProduire(void){
    if (stockMini > stock){
        return (stockMini - stock);
    }
    return 0;
}

//-------------------------------------------
//
//          Produit::getNbPointsDeVie
//
//-------------------------------------------
int Produit::getNbPointsDeVie(void){
    return nbPointsDeVie;
}

//-------------------------------------------
//
//          Produit::getCoutProduction
//
//-------------------------------------------
int Produit::getCoutProduction(void){
    return coutFabrication;
}

//-------------------------------------------
//
//          Produit::sauve
//
//-------------------------------------------
void Produit::sauve(FILE *fichier){
    if (debugProduit) printf("Produit::sauve => debut\n");
    fprintf(fichier, "produit %d %d %d %s %d %d %d %d %d %d %d\n", this->id, this->type, this->producteurId, this->nom, 
        this->prix, this->stock, this->stockMini, this->coutFabrication, this->dureeVie, this->delaiFabrication, this->indiceNecessite);
    if (debugProduit) printf("Produit::sauve => fin\n");
}

//-------------------------------------------
//
//          Produit::sauveJson
//
//-------------------------------------------
void Produit::sauveJson(FILE *fic){
    //if (debugProduit) printf("Humain::sauveJson => Sauvegarde de %s\n", this->getNomComplet());
    fprintf(fic, "      { \"id\": %d, ", this->id);
    fprintf(fic, "\"type\": \"%d\" ,", this->type);
    fprintf(fic, "\"producteurId\": \"%d\" ,", this->producteurId);
    fprintf(fic, "\"nom\": \"%s\" ,", this->nom);
    fprintf(fic, "\"prix\": %d ,", this->prix);
    fprintf(fic, "\"stock\": %d ,", this->stock);
    fprintf(fic, "\"stockMini\": %d ,", this->stockMini);
    fprintf(fic, "\"coutFabrication\": %d ,", this->coutFabrication);
    fprintf(fic, "\"dureeVie\": %d ,", this->dureeVie);
    fprintf(fic, "\"delaiFabrication\": %d ,", delaiFabrication);
    fprintf(fic, "\"indiceNecessite\": %d", this->indiceNecessite);
    fprintf(fic, " },");
    fprintf(fic, "\n");
    fflush(fic);
}

//-------------------------------------------
//
//          Produit::getTypeProd
//
//-------------------------------------------
char *Produit::getTypeProd(void){
    switch (this->type){
        case PRODUIT_ALIMENTAIRE:
            strcpy(tmpString, "Alimentaire");
            break;
        case PRODUIT_SERVICES:
            strcpy(tmpString, "Service");
            break;
        case PRODUIT_VETEMENTS:
            strcpy(tmpString, "Vetement");
            break;
        case PRODUIT_AUTOMOBILE:
            strcpy(tmpString, "Automobile");
            break;
        case PRODUIT_MAISON:
            strcpy(tmpString, "Maison");
            break;
        case PRODUIT_LOISIR:
            strcpy(tmpString, "Loisir");
            break;
        case PRODUIT_EQUIP_MAISON:
            strcpy(tmpString, "Equip maison");
            break;
        default:
            strcpy(tmpString, "");
            break;
    }
    return tmpString;
}

//-------------------------------------------
//
//          Produit::getindiceNecessite
//
//-------------------------------------------
int Produit::getindiceNecessite(void){
    return indiceNecessite;
}

//-------------------------------------------
//
//          Commande::traitement
//
//-------------------------------------------
void Produit::boucleTraitement(void){
    //if (debugProduit) printf("Produit::boucleTraitement => boucleTraitement %s : debut\n", this->nom);
}

//-------------------------------------------
//
//          Commande::miseAJourStock
//
//-------------------------------------------
void Produit::miseAJourStock(int quantite){
    if (debugProduit) printf("Produit::miseAJourStock => modifie le stock de %d\n", quantite);
    this->stock += quantite;
}
