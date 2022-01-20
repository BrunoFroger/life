//-----------------------------------
//
//      variables.cpp
//
//-----------------------------------

#include "variables.hpp"

Humain *listeHumains[MAX_HUMAINS];
Entreprise *listeEntreprises[MAX_ENTREPRISES];
CompteBancaire *listeComptesBancaires[MAX_COMPTES_BANCAIRES];

int indexHumain=0;
bool vivantsSeulement=true;
int nbEntreprises=0;
int nbComptesBancaires;

bool listeAuto=false;
bool statAuto=false;
bool menuOnOff=false;