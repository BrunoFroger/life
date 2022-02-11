//-----------------------------------
//
//      produit.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "humain.hpp"
#include "variables.hpp"
#include "statistiques.hpp"
#include "tools.hpp"

int lastIdProduit=0;

//-------------------------------------------
//
//          Produit::Produit
//
//-------------------------------------------
Produit::Produit(char *nom, int type, int stockInitial, int stockMini, int prix, int coutFabrication){
    this->id = lastIdProduit++;
    strcpy(this->nom, nom);
    this->type = type;
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
//          Produit::getPrix
//
//-------------------------------------------
int Produit::getPrix(void){
    return this->prix;
}

//-------------------------------------------
//
//          Produit::sauve
//
//-------------------------------------------
void Produit::sauve(FILE *fichier){
    printf("Produit::sauve => debut\n");
    printf("Produit::sauve => fin\n");
}