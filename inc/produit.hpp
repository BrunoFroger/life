//-----------------------------------
//
//      produit.hpp
//
//-----------------------------------


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

#define P_MAI_LOYER             501
#define P_MAI_CREDIT            502
#define P_MAI_CAHAUFFAGE        503
#define P_MAI_ACHAT_MEUBLES     504
#define P_MAI_REPARATIONS       505
#define P_MAI_ASSURANCE         506
#define P_MAI_MAISON            510
#define P_MAI_APPART            511
#define P_MAI_RENOV             520

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
            Produit(char *nom, int type, int producteur_id, int stockInitial, int stockMini, int prix, int coutFabrication, int dureeVie, int delaiFab, int indiceNecessite);
            ~Produit(void);
            char *getNom(void);
            int getPrix(void);
            int getStock(void);
            int getStockMini(void);
            void sauve(FILE *fichier);
            void sauveJson(FILE *fic);
            int getId(void);
            int getProducteurId(void);
            char *getTypeProd(void);
            int getQuantiteAProduire(void);
            int getindiceNecessite(void);
            void boucleTraitement(void);

        private:
            int id;
            char nom[50];
            int producteurId;
            int type;
            int stock;
            int stockMini;
            int coutFabrication;
            int prix;
            int delaiFabrication;
            int dureeVie;
            int indiceNecessite;        // 0 indispensable puis increment si moins indispensable
    };

#endif