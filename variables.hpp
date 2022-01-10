//-----------------------------------
//
//      variables.hpp
//
//-----------------------------------

#include "humain.hpp"

#ifndef __VARIABLES__
#define __VARIABLES__

    #define MAX_HUMAINS   250

    typedef Humain *ptrHumain;
    extern ptrHumain listeHumains[];
    extern int indexHumain;
#endif