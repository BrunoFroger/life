//-----------------------------------
//
//      banque.hpp
//
//-----------------------------------

#include "humain.hpp"
#include "entreprise.hpp"

#ifndef __BANQUE__
#define __BANQUE__

    class CompteBancaire{

        public:
            CompteBancaire(char *nomClient);
            void credite(int montant);
            bool debite(int montant);
            int getSolde(void);
            int getNumCompte(void);
            char *getNomClient(void);

        private:
            int numCompte;
            char nomClient[50];
            int solde;
    };

#endif