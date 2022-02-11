//-----------------------------------
//
//      banque.cpp
//
//-----------------------------------




#include <stdio.h>

#include "../inc/compteBancaire.hpp"
#include "../inc/variables.hpp"

int prochainNumeroCompte=1;

//-------------------------------------------
//
//          CompteBancaire::CompteBancaire
//
//-------------------------------------------
CompteBancaire::CompteBancaire(char *client){
    //printf("Creation de compte bancaire pour <%s>\n", client);
    this->numCompte = nbComptesBancaires;
    strcpy(this->nomClient,client);
    this->solde = 0;
    listeComptesBancaires[nbComptesBancaires] = this;
    nbComptesBancaires++;
}

//-------------------------------------------
//
//          CompteBancaire::credite
//
//-------------------------------------------
void CompteBancaire::credite(int montant){
    this->solde += montant;
}

//-------------------------------------------
//
//          CompteBancaire::debite
//
//-------------------------------------------
bool CompteBancaire::debite(int montant){
    if (solde > montant){
        this->solde -= montant;
        return true;
    }
    return false;
}

//-------------------------------------------
//
//          CompteBancaire::getSolde
//
//-------------------------------------------
int CompteBancaire::getSolde(void){
    return this->solde;
}

//-------------------------------------------
//
//          CompteBancaire::getNumCompte
//
//-------------------------------------------
int CompteBancaire::getNumCompte(void){
    return this->numCompte;
}

//-------------------------------------------
//
//          CompteBancaire::getNomClient
//
//-------------------------------------------
char *CompteBancaire::getNomClient(void){
    return this->nomClient;
}