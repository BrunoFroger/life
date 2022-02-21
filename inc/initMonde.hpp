//-----------------------------------
//
//      initMonde.hpp
//
//-----------------------------------

#include <stdio.h>
#include <string>

#include "variables.hpp"

#ifndef __INIT_MONDE__
#define __INIT_MONDE__

    #include "humain.hpp"
    #include "entreprise.hpp"
    #include "produit.hpp"
    #include "commande.hpp"

    #define INIT_NB_HUMAINS 24
    
    extern void initMonde(Humain*dieu);
    extern void resetMonde(void);

#endif