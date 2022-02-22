//-----------------------------------
//
//      variables.hpp
//
//-----------------------------------


#ifndef __VARIABLES__
#define __VARIABLES__

    #define MAX_ENTREPRISES     25
    #define MAX_PRODUITS        1000
    #define MAX_COMMANDES       1000
    #define MAX_HUMAINS         10000
    #define MAX_COMPTES_BANCAIRES MAX_ENTREPRISES+MAX_HUMAINS

    #include "humain.hpp"
    #include "produit.hpp"
    #include "commande.hpp"
    #include "entreprise.hpp"
    #include "compteBancaire.hpp"

    #define MIN_HUMAINS         15
    #define AGE_DEBUT_MARIAGE   20
    //#define AGE_FIN_MARIAGE     100
    #define DIFF_AGE_MARIAGE    10
    #define AGE_DEBUT_NAISSANCE 22
    #define AGE_FIN_NAISSANCE   45

    #define PROBA_ACCIDENT      100
    #define PROBA_MARIAGE       3
    #define PROBA_NAISSANCE     2

    
    extern int nbJours;
    extern Humain *listeHumains[];
    extern Entreprise *listeEntreprises[];
    extern CompteBancaire *listeComptesBancaires[];
    extern Commande *listeCommandes[];
    extern Produit *listeProduits[];
    extern int nbHumains;
    extern bool vivantsSeulement;
    extern int nbEntreprises;
    extern int nbComptesBancaires;
    extern int nouveauNumeroCommande;
    extern int nbProduits;
    extern int nbCommandes;
    extern char nomFichier[];
    extern char nomFichierJson[];
    extern char tmpString[];
    extern char tmpString1[];

    extern bool listeAuto;
    extern bool statAuto;
    extern bool menuOnOff;

    extern bool debugHumain;
    extern bool debugCommande;
    extern bool debugEntreprise;
    extern bool debugProduit;
    extern bool debugStats;
    extern bool debugCptBancaire;
    extern bool debugTools;
#endif