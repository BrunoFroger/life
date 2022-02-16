//-----------------------------------
//
//      humain.hpp
//
//-----------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #include <string>
    #include "variables.hpp"

    // genre humain
    #define HOMME 1
    #define FEMME 2
    #define INCONNU 3

    #define MAX_ENFANTS 15
    #define MAX_ACHAT_CLIENT    250

    // status 
    #define CELIBATAIRE 0
    #define MARIE       1
    #define DIVORCE     2
    #define VEUF        3
    #define MORT        4

    class Entreprise;
    class CompteBancaire;
    class Produit;

    typedef struct{
        Produit *produit;
        int dateAchat;
        int duree;
    } produitClient;

    class Humain{

        public :
            Humain();
            Humain(Humain *pere, int genre, char *nom, char *prenom, int age);
            Humain(char *datas);
            ~Humain();
            void restore(char *datas);
            void sauve(FILE *fic);
            void sauveJson(FILE *fic);
            void boucleTraitement(void);
            void displayInfos(void);
            void mariage(Humain *conjoint);
            Humain *naissance(int genre, char *nom, char *prenom);
            void descendance();
            void deces(void);
            int getId();
            int getNbEnfants();
            char getStatus();
            char *getNom();
            char *getNomComplet();
            char *getPrenom();
            Humain *getConjoint();
            Humain *getPere();
            Humain *getMere();
            Humain *getEnfant(int index);
            int getAge();
            char *getGenreTexte();
            bool addEnfant(Humain *enfant);
            void vieillir(void);
            int getSoldeBancaire(void);
            char *getEmployeur(void);
            bool estSalarie(void);
            bool credite(int montant);
            bool commandeEnCours;
            int getNumCompte();
            bool debite(int montant);

        private :
            int id;         // id unique
            int genre;      // H ou F
            int age;        // nb jours
            int nbEnfants;
            char genreTexte[10];
            char nom[50];
            char prenom[50];
            int status;     // celibataire, marie, veuf, mort, ...
            Humain *conjoint;
            Humain *pere;
            Humain *mere;
            Humain *enfants[MAX_ENFANTS];
            void descendance(int level);
            void setGenreTexte();
            Entreprise *employeur;
            CompteBancaire *compteBancaire;
            void testMariage(void);
            void testNaissance(void);
            void achats(void);
            produitClient *listeProduitsHumain[MAX_ACHAT_CLIENT];
            void setListeProduitEnManque(void);
            Produit *listeProduitsEnManque[MAX_ACHAT_CLIENT];
    };

#endif