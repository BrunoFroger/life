//-----------------------------------
//
//      tools.hpp
//
//-----------------------------------

#ifndef __TOOLS__
#define __TOOLS__
    #include "variables.hpp"
    #include "entreprise.hpp"
    #include "commande.hpp"
    #include "humain.hpp"
    #include "produit.hpp"

    typedef struct{
        char nom[20];
        char prenom[20];
        int genre;
        int age;
    }enfantDieu;

    class Humain;
    class Entreprise;
    class Commande;

    extern int getRandom(int range);
    extern enfantDieu getRandomEnfant(void);
    extern enfantDieu getRandomEnfant(int age);
    extern void afficheListeHumains(void);
    extern char *getPrenomMasculin(void);
    extern char *getPrenomFeminin(void);
    extern int getRandomGenre();
    extern void afficheListeComptesBancaires(void);
    extern void afficheListeEntreprises(void);
    extern void afficheListeProduits(void);
    extern void afficheListeCommandes(void);
    extern Entreprise *getProducteur(char *produit);
    extern char *getstringBoolean(bool val);
    extern Entreprise *getEntrepriseById(int id);
    extern Humain *getHumainById(int id);
    extern Produit *getProduitById(int id);
    extern Produit *getProduitByNom(char *nom);
    extern Commande *getCommandeById(int id);
    
#endif