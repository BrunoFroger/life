//-----------------------------------
//
//      produit.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "../inc/variables.hpp"
#include "../inc/statistiques.hpp"
#include "../inc/tools.hpp"

int lastIdProduit=0;

//-------------------------------------------
//
//          Produit::Produit
//
//-------------------------------------------
Produit::Produit(char *nom, int type, int producteur_id, int stockInitial, int stockMini, int prix, int coutFabrication){
    //printf("Produit::Produit => creation du produit %d\n", nbProduits);
    this->id = lastIdProduit++;
    strcpy(this->nom, nom);
    this->type = type;
    this->producteurId = producteur_id;
    this->stock = stockInitial;
    this->stockMini = stockMini;
    this->prix = prix;
    this->coutFabrication = coutFabrication;
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
    if (stockMini < stock){
        return (stockMini - stock);
    }
    return 0;
}

//-------------------------------------------
//
//          Produit::sauve
//
//-------------------------------------------
void Produit::sauve(FILE *fichier){
    printf("Produit::sauve => debut\n");
    fprintf(fichier, "produit %d %d %d %s %d %d %d %d\n", this->id, this->type, this->producteurId, this->nom, this->prix, this->stock, this->stockMini, this->coutFabrication);
    printf("Produit::sauve => fin\n");
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