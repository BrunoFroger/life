//-----------------------------------
//
//      variables.hpp
//
//-----------------------------------

#include "humain.hpp"

#ifndef __VARIABLES__
#define __VARIABLES__

    #define MAX_HUMAINS         250
    #define MIN_HUMAINS         15
    #define AGE_DEBUT_MARIAGE   20
    //#define AGE_FIN_MARIAGE     100
    #define DIFF_AGE_MARIAGE    5
    #define AGE_DEBUT_NAISSANCE 25
    #define AGE_FIN_NAISSANCE   40

    #define PROBA_ACCIDENT      100
    #define PROBA_MARIAGE       3
    #define PROBA_NAISSANCE     2

    typedef Humain *ptrHumain;
    extern ptrHumain listeHumains[];
    extern int indexHumain;
#endif