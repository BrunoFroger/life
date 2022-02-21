//-----------------------------------
//
//      statistiques.hpp
//
//-----------------------------------


#ifndef __STATISTIQUES__
#define __STATISTIQUES__

    #include <stdio.h>

    #include "variables.hpp"
    #include "compteBancaire.hpp"
    #include "entreprise.hpp"
    #include "produit.hpp"
    #include "commande.hpp"
    #include "humain.hpp"

    extern void statistiques(void);
    extern int getNbVivants(void);

    extern bool display_stat_humain;
    extern bool display_stat_variables;
    extern bool display_stat_cptBanque;
    extern bool display_stat_entreprises;
    extern bool display_stat_produits;
    extern bool display_stat_salaries;
    extern bool display_stat_commandes;

#endif