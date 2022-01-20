//-----------------------------------
//
//      variables.hpp
//
//-----------------------------------

#include "humain.hpp"
#include "entreprise.hpp"

#ifndef __VARIABLES__
#define __VARIABLES__

    #define MAX_ENTREPRISES     25
    #define MAX_HUMAINS         10000
    #define MIN_HUMAINS         15
    #define AGE_DEBUT_MARIAGE   20
    //#define AGE_FIN_MARIAGE     100
    #define DIFF_AGE_MARIAGE    10
    #define AGE_DEBUT_NAISSANCE 22
    #define AGE_FIN_NAISSANCE   45

    #define PROBA_ACCIDENT      100
    #define PROBA_MARIAGE       3
    #define PROBA_NAISSANCE     2

    #define MAX_COMPTES_BANCAIRES MAX_ENTREPRISES+MAX_HUMAINS
    //typedef Humain *ptrHumain;
    extern Humain *listeHumains[];
    extern Entreprise *listeEntreprises[];
    extern CompteBancaire *listeComptesBancaires[];
    extern int indexHumain;
    extern bool vivantsSeulement;
    extern int nbEntreprises;
    extern int nbComptesBancaires;

    extern bool listeAuto;
    extern bool statAuto;
    extern bool menuOnOff;
#endif