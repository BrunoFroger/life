//-----------------------------------
//
//      commande.hpp
//
//-----------------------------------

#include <stdio.h>
#include <string>


#ifndef __COMMANDE__
#define __COMMANDE__

    #define COMMANDE_IMPOSSIBLE     -1
    #define COMMANDE_INITIALISEE    0
    #define COMMANDE_EN_COURS       1
    #define COMMANDE_EN_ATTENTE     2
    #define COMMANDE_DISPONIBLE     3
    #define COMMANDE_LIVREE         4
    #define COMMANDE_SOLDEE         5

    #include "variables.hpp"
    #include "produit.hpp"
    #include "humain.hpp"
    #include "entreprise.hpp"

    class Humain;
    class Entreprise;
    class Produit;


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
            void changeStatus(int nouveauStatus);

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