//-----------------------------------
//
//      entreprise.hpp
//
//-----------------------------------

#include <stdio.h>


#ifndef __ENTREPRISE__
#define __ENTREPRISE__

    #include "humain.hpp"
    #include "compteBancaire.hpp"  

    #define MAX_COMMANDES   200

    #define MAX_PRODUITS    10
    #define PROD_NOURITURE  1
    #define PROD_MAISON     2
    #define PROD_VOITURE    3

    #define MAX_SALARIE     50

    #define EMPLOYE     1
    #define CADRE       2
    #define PATRON      3

    #define SALAIRE_DEBUT_EMPLOYE   100
    #define SALAIRE_DEBUT_CADRE     150
    #define SALAIRE_DEBUT_PATRON    300

    class Humain;

    typedef struct{
        Humain *salarie;
        CompteBancaire *compteBancaire;
        int status;
        int remuneration;
        int derniereAugmentation; // nb periodes depuis derniere augmentation
        int productivite;   // nb unite de travail de ce salarie 
    } structSalarie;

    typedef struct{
        char nom[20];
        int prix;
        int stock;
        int stockMini;
        int coutFabrication;    // cout en unite de travail
    } structProduit;

    typedef struct{
        Humain *client;
        char nomProduit[20];
        int quantite;
    } structCommande;

    class Entreprise{

        public:
            Entreprise(char *nom, int typeProd, Humain *patron);
            bool commande(Humain *client, char *produit, int qte);
            int nbDisponibles(char *produit);
            int getPrix(char *produit);
            void addProduit(char *nom, int prix, int stock, int stockMini, int coutProd);
            void production(void);
            char *getNom(void);
            void embauche(Humain *personne, int status);
            void catalogue(void);
            char *getTypeProd(void);
            int getNbSalaries(void);
            void gereCommandes(void);
            void recrutement(int typeRecrutement);
            bool isInCatalogue(char *produit);
            structProduit *getProduit(int index);
            structCommande *getCommande(int index);
            bool credite(int montant);
            bool debite(int montant);

        private:
            char nom[50];
            Humain *patron;
            int typeProduction;
            int nbSalaries;
            int nbEmployes;
            int nbCadres;
            int effectifMax;
            int prixProduit;
            structProduit listeProduits[MAX_PRODUITS];
            structSalarie listeSalarie[MAX_SALARIE];
            void generePaye(void);
            char * getStatusString(int status);
            CompteBancaire *compteBancaire;
            structCommande listeCommandes[MAX_COMMANDES];
            void listeSalaries(void);
            int getProductionPossible(void);
    };

#endif