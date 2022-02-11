//-----------------------------------
//
//      variables.cpp
//
//-----------------------------------

#include "variables.hpp"

Humain *listeHumains[MAX_HUMAINS];
Entreprise *listeEntreprises[MAX_ENTREPRISES];
CompteBancaire *listeComptesBancaires[MAX_COMPTES_BANCAIRES];
Commande *listeCommandes[MAX_COMMANDES];
Produit *listeProduits[MAX_PRODUITS];

int nbHumains=0;
bool vivantsSeulement=true;
int nbEntreprises=0;
int nbComptesBancaires;
int nouveauNumeroCommande=1;
int nbCommandes=0;
int nbProduits=0;
char nomFichier[50];

bool listeAuto=false;
bool statAuto=false;
bool menuOnOff=false;