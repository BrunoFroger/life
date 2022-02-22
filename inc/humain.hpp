//-----------------------------------
//
//      humain.hpp
//
//-----------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #include <string>

    #include "variables.hpp"
    #include "statistiques.hpp"
    #include "compteBancaire.hpp"
    #include "entreprise.hpp"
    #include "produit.hpp"

    // genre humain
    #define HOMME 1
    #define FEMME 2
    #define INCONNU 3

    #define POINTS_DE_VIE_INITIAL   100

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
    class Humain;

    typedef struct{
        Produit *produit;
        int dateAchat;
        int duree;
    } produitClient;

    class Humain{

        public :
            Humain();
            Humain(Humain *pere, int genre, char *nom, char *prenom, int nbJours);
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
            int getNbJours();
            int getAge();
            char *getGenreTexte();
            bool addEnfant(Humain *enfant);
            void vieillir(void);
            int getSoldeBancaire(void);
            Entreprise *getEmployeur(void);
            bool estSalarie(void);
            bool credite(int montant);
            bool commandeEnCours;
            int getNumCompte();
            bool debite(int montant);
            void commande(Produit *produit, int quantite);
            void setEmployeur(Entreprise *ptrEntreprise);
            int getPointsDeVie(void);

        private :
            int id;         // id unique
            int genre;      // H ou F
            int nbJours;        // nb jours
            int age;        // nb jours
            int nbEnfants;
            char genreTexte[10];
            char nom[50];
            char prenom[50];
            int status;     // celibataire, marie, veuf, mort, ...
            int pointsDeVie;
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
            produitClient *mesProduits[MAX_ACHAT_CLIENT];
            void setListeProduitEnManque(void);
            Produit *listeProduitsEnManque[MAX_ACHAT_CLIENT];
            void gereCommandesEnCours(void);
    };

#endif