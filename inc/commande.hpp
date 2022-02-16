//-----------------------------------
//
//      commande.hpp
//
//-----------------------------------

#include <stdio.h>
#include <string>


#ifndef __COMMANDE__
#define __COMMANDE__

    #define COMMANDE_INITIALISEE    0
    #define COMMANDE_EN_COURS       1
    #define COMMANDE_DISPONIBLE     2
    #define COMMANDE_LIVREE         3

    #include "variables.hpp"
    //#include "entreprise.hpp"
    //#include "humain.hpp"
    #include "produit.hpp"

    class Commande {
        public:
            Commande(Produit *produit, int quantité, Humain *client);
            Commande(char *datas);
            ~Commande(void);
            int getStatus(void);
            void boucleTraitement(void);
            Humain *getClient(void);
            Entreprise *getFabricant(void);
            Produit *getProduit(void);
            int getQuantite(void);
            char *getStatusString(void);
            void sauve(FILE *fichier);
            void sauveJson(FILE *fic);
            int getNumero();

        private:
            int numero;
            int status;
            int quantite;
            Humain *client;
            Entreprise *fabricant;
            Produit *produit;
            void displayCommande(void);
    };


#endif