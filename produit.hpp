//-----------------------------------
//
//      produit.hpp
//
//-----------------------------------



// definition des types de produits
#define PRODUIT_ALIMENTAIRE     100
#define PRODUIT_SERVICES        200
#define PRODUIT_VETEMENTS       300
#define PRODUIT_AUTOMOBILE      400
#define PRODUIT_MAISON          500
#define PRODUIT_LOISIR          600
#define PRODUIT_EQUIP_MAISON    700

// definition des produits
#define P_ALI_VIANDE            101
#define P_ALI_LEGUME            102
#define P_ALI_BOISSON           103
#define P_ALI_FRUITS            104
#define P_ALI_LAITAGE           105

#define P_SER_MEDECIN           201
#define P_SER_TAXI              202
#define P_SER_ASSURANCE         203

#define P_VET_PULL              301
#define P_VET_PANTALON          302
#define P_VET_VESTE             303
#define P_VET_CHAUSSURE         304

#define P_AUT_VOITURE           401
#define P_AUT_REPARATION        402
#define P_AUT_CARBURANT         403
#define P_AUT_ASSURANCE         404

#define P_EQU_MAI_FRIGO         701
#define P_EQU_MAI_GAZINIERE     702
#define P_EQU_MAI_LAVE_LINGE    702
#define P_EQU_MAI_LAVE_VAISS    703
#define P_EQU_MAI_SECHE_LINGE   704


#ifndef __PRODUIT__
#define __PRODUIT__

    #include <stdio.h>
    #include <string>

    #include "variables.hpp"
    
    class Produit {
        public:
            Produit(char *nom, int type, int stockInitial, int stockMini, int prix, int coutFabrication);
            ~Produit(void);
            char *getNom(void);
            int getPrix(void);
            int getStock(void);
            void sauve(FILE *fichier);

        private:
            int id;
            char nom[50];
            int type;
            int stock;
            int stockMini;
            int coutFabrication;
            int prix;
    };

#endif