//-----------------------------------
//
//      humain.hpp
//
//-----------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #include <string>
    #include "entreprise.hpp"

    // genre humain
    #define HOMME 1
    #define FEMME 2
    #define INCONNU 3

    #define MAX_ENFANTS 15

    // status 
    #define CELIBATAIRE 0
    #define MARIE       1
    #define DIVORCE     2
    #define VEUF        3
    #define MORT        4

    class Entreprise;
    class CompteBancaire;

    class Humain{

        public :
            Humain();
            Humain(int genre, char *nom, char *prenom, int age);
            Humain(char *datas);
            ~Humain();
            void restore(char *datas);
            void sauve(FILE *fic);
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
            int id;
            int genre;
            int age;
            int nbEnfants;
            char genreTexte[10];
            char nom[50];
            char prenom[50];
            int status;
            Humain *conjoint;
            Humain *pere;
            Humain *mere;
            Humain *enfants[MAX_ENFANTS];
            void descendance(int level);
            void setGenreTexte();
            Entreprise *employeur;
            CompteBancaire *compteBancaire;
    };

#endif