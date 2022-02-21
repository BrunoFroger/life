//-----------------------------------
//
//      banque.hpp
//
//-----------------------------------

#ifndef __BANQUE__
#define __BANQUE__

    #include "variables.hpp"

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