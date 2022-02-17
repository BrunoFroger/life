//-----------------------------------
//
//      entreprise.hpp
//
//-----------------------------------

// definition des types de production
#define PRODUIT_ALIMENTAIRE     100
#define PRODUIT_SERVICES        200
#define PRODUIT_VETEMENTS       300
#define PRODUIT_AUTOMOBILE      400
#define PRODUIT_MAISON          500
#define PRODUIT_LOISIR          600
#define PRODUIT_EQUIP_MAISON    700


#ifndef __ENTREPRISE__
#define __ENTREPRISE__

    #include <stdio.h>
    #include <string>
    #include "variables.hpp"
    #include "produit.hpp"


    #define MAX_SALARIE     50
    #define AGE_DEBUT_ACTIVITE    20
    #define AGE_RETRAITE    65

    #define EMPLOYE     1
    #define EMPLSUPP    4
    #define CADRE       2
    #define PATRON      3

    #define SALAIRE_DEBUT_EMPLOYE   100
    #define SALAIRE_DEBUT_EMPLSUPP  150
    #define SALAIRE_DEBUT_CADRE     200
    #define SALAIRE_DEBUT_PATRON    400

    #define PRODUCTIVITE_EMPLOYE    10
    #define PRODUCTIVITE_EMPLSUPP   15
    #define PRODUCTIVITE_CADRE      3
    #define PRODUCTIVITE_PATRON     1

    class Humain;
    class CompteBancaire;

    typedef struct{
        Humain *salarie;
        int status;
        int remuneration;
        int derniereAugmentation; // nb periodes depuis derniere augmentation
        int productivite;   // nb unite de travail de ce salarie 
    } structSalarie;

    /*
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
    */

    class Entreprise{

        public:
            Entreprise(char *nom, int typeProd, Humain *patron, int effectifMax);
            Entreprise(char *datas);
            ~Entreprise(void);
            void restore(char *datas);
            void init(void);
            bool commande(Humain *client, char *produit, int qte);
            int nbDisponibles(char *produit);
            int nbDisponibles(Produit *produit);
            int getPrix(char *produit);
            void addProduit(Produit *addProduit);
            void production(void);
            char *getNom(void);
            void embauche(Humain *personne, int status);
            void supprimeSalarie(Humain *personne);
            void catalogue(void);
            char *getTypeProd(void);
            int getNbSalaries(void);
            int getId(void);
            void gereCommandes(void);
            void gereRecrutement(int typeRecrutement);
            bool isInCatalogue(Produit *produit);
            //structProduit *getProduit(int index);
            bool credite(int montant);
            structSalarie *getSalarie(int index);
            void verseSalaires(void);
            void sauve(FILE *fic);
            void sauveJson(FILE *fic);
            void listeSalaries(void);
            char * getStatusString(int status);
            int getEffectifMax(void);
            bool produitEnStock(Produit *produit);
            void boucleTraitement(void);
            Humain *getPatron(void);
            

        private:
            int id;
            char nom[50];
            Humain *patron;
            int typeProduction;
            int nbSalaries;
            int nbEmployes;
            int nbCadres;
            int effectifMax;
            Produit *listeProduit[MAX_PRODUITS];
            //structProduit listeProduits[MAX_PRODUITS];
            structSalarie listeSalarie[MAX_SALARIE];
            void generePaye(void);
            CompteBancaire *compteBancaire;
            //structCommande listeCommandes[MAX_COMMANDES];
            int getProductionPossible(void);
            bool debite(int montant);
            void checkPatron(void);
    };

#endif