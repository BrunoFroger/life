//-----------------------------------
//
//      initMonde.cpp
//
//-----------------------------------

#include "../inc/initMonde.hpp"
#include "../inc/tools.hpp"

//-------------------------------------------
//
//          initMonde=>InitMonde
//
//-------------------------------------------
void resetMonde(void){
    // reset des humains
    for (int i = 0 ; i < MAX_HUMAINS ; i++){
        listeHumains[i] = NULL;
    }
    nbHumains=0;

    // reset des entreprises
    for (int i = 0 ; i < MAX_ENTREPRISES ; i++){
        listeEntreprises[i] = NULL;
    }
    nbEntreprises=0;

    // reset des produits
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        listeProduits[i] = NULL;
    }
    nbProduits=0;

    // reset des commandes
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        listeCommandes[i] = NULL;
    }
    nbCommandes=0;

    // reset des comptes bncaires
    for (int i = 0 ; i < MAX_COMPTES_BANCAIRES ; i++){
        listeComptesBancaires[i] = NULL;
    }
    nbComptesBancaires=0;
}

//-------------------------------------------
//
//          initMonde=>InitMonde
//
//-------------------------------------------
void initMonde(Humain *dieu){

    int i =0;

    // reset des tableau 
    resetMonde();

    // creation des humains
    enfantDieu enfant;
    printf("initMonde => generation des premiers humains\n");
    // creation des personnes directement issues de dieu
    for (i = 0 ; i < INIT_NB_HUMAINS ; i++){
        enfant = getRandomEnfant(getRandom(20) + 20); // creation d'adultes entre 20 et 40 ans
        new Humain(dieu, enfant.genre, enfant.nom, enfant.prenom, enfant.age);
    }
    afficheListeHumains();

    printf("initMonde => mariage d'une partie de la population\n");
    // creation des couples 1/3 celibataires ; 2/3 de maries
    int nbCouples = 0;
    Humain *ptrHomme, *ptrFemme;
    for (int i = 0 ; i < INIT_NB_HUMAINS ; i++){
        ptrHomme = listeHumains[i];
        if ( (ptrHomme->getGenreTexte()[0] == 'H') && (ptrHomme->getStatus() == 'C') ){
            //printf("homme disponible : %s,  genre = %c, status = %c\n", ptrHomme->getNomComplet(), ptrHomme->getGenreTexte()[0], ptrHomme->getStatus());
            // c'esrt un homme celibataire => on lui cherche une femme
            for (int j = (i + 1) ; j < INIT_NB_HUMAINS ; j++){
                ptrFemme = listeHumains[j];
                if ( (ptrFemme->getGenreTexte()[0] == 'F') && (ptrFemme->getStatus() == 'C') ){
                    //printf("femme disponible : %s,  genre = %c, status = %c\n", ptrFemme->getNomComplet(), ptrFemme->getGenreTexte()[0], ptrFemme->getStatus());
                    // c'est bien une femme, on peut les marier
                    ptrHomme->mariage(ptrFemme);
                    nbCouples++;
                    break;
                }
            }
        }
        if (nbCouples >= (INIT_NB_HUMAINS / 3)) break;
    }

    printf("initMonde => generation des enfants\n");
    // creation des enfants entre 1 et 3 enfnats par couples
    for (int i = 0 ; i < INIT_NB_HUMAINS ; i++){
        ptrHomme = listeHumains[i];
        if ( (ptrHomme->getGenreTexte()[0] == 'H') && (ptrHomme->getStatus() == 'M') ) {
            ptrHomme = listeHumains[i];
            // c'est un homme marie, on peut lui donner des enfants
            int nbEnfantsAGenerer = getRandom(4);
            printf("on genere %d enfants pour %s\n", nbEnfantsAGenerer, ptrHomme->getNomComplet());
            for (int j = 0 ; j < nbEnfantsAGenerer ; j++){
                int genre = getRandomGenre();
                if (genre == HOMME) {
                    ptrHomme->naissance(genre, ptrHomme->getNom(), getPrenomMasculin());
                } else {
                    ptrHomme->naissance(genre, ptrHomme->getNom(), getPrenomFeminin());
                }
            }
        }
    }

    // creation des entreprises initiales
    Entreprise *epicerie, *entrepreneur, *garage, *vetements, *electroMenager;
    //Entreprise(char *nom, int typeProd, Humain *patron, int effectifMax);
    listeEntreprises[nbEntreprises] = epicerie = new Entreprise((char *)"epicerie", PRODUIT_ALIMENTAIRE, dieu, 10);
    listeEntreprises[nbEntreprises] = entrepreneur = new Entreprise((char *)"entrepreneur", PRODUIT_MAISON, dieu, 50);
    listeEntreprises[nbEntreprises] = vetements = new Entreprise((char *)"vetements", PRODUIT_VETEMENTS, dieu, 2);
    listeEntreprises[nbEntreprises] = garage = new Entreprise((char *)"garage", PRODUIT_AUTOMOBILE, dieu, 5);
    listeEntreprises[nbEntreprises] = electroMenager = new Entreprise((char *)"electroMenager", PRODUIT_EQUIP_MAISON, dieu, 5);

    // creation des produits de base
    //Produit(char *nom, int type, int producteur_id, int stockInitial, int stockMini, int prix, int coutFabrication, int dureeVie, int delaiFab, int indiceNecessite);
    listeProduits[nbProduits] = new Produit((char *)"viande", P_ALI_VIANDE, epicerie->getId(), 10, 5, 10, 4, 7, 1, 0);
    listeProduits[nbProduits] = new Produit((char *)"legume", P_ALI_LEGUME, epicerie->getId(), 10, 5, 10, 4, 7, 1, 0);
    listeProduits[nbProduits] = new Produit((char *)"laitage", P_ALI_LAITAGE, epicerie->getId(), 10, 5, 10, 4, 7, 1, 0);
    listeProduits[nbProduits] = new Produit((char *)"fruit", P_ALI_FRUITS, epicerie->getId(), 10, 5, 10, 4, 7, 1, 0);
    listeProduits[nbProduits] = new Produit((char *)"boisson", P_ALI_BOISSON, epicerie->getId(), 20, 5, 2, 1, 50, 2, 0);

    listeProduits[nbProduits] = new Produit((char *)"basket", P_VET_CHAUSSURE, vetements->getId(), 5, 2, 50, 20, 400, 20, 5);
    listeProduits[nbProduits] = new Produit((char *)"pull", P_VET_CHAUSSURE, vetements->getId(), 5, 2, 40, 15, 500, 20, 5);
    listeProduits[nbProduits] = new Produit((char *)"pantalon", P_VET_CHAUSSURE, vetements->getId(), 5, 2, 50, 20, 500, 20, 5);
    listeProduits[nbProduits] = new Produit((char *)"blouson", P_VET_CHAUSSURE, vetements->getId(), 5, 2, 50, 20, 1000, 30, 5);
    listeProduits[nbProduits] = new Produit((char *)"manteau", P_VET_CHAUSSURE, vetements->getId(), 2, 1, 100, 40, 2000, 30, 10);
    listeProduits[nbProduits] = new Produit((char *)"impermeable", P_VET_CHAUSSURE, vetements->getId(), 2, 1, 100, 40, 2000, 30, 10);

    listeProduits[nbProduits] = new Produit((char *)"voiture", P_AUT_VOITURE, garage->getId(), 5, 2, 10000, 8000, 40000, 120, 20);
    listeProduits[nbProduits] = new Produit((char *)"moto", P_AUT_VOITURE, garage->getId(), 5, 2, 5000, 3500, 35000, 120, 100);

    listeProduits[nbProduits] = new Produit((char *)"frigo", P_EQU_MAI_FRIGO, electroMenager->getId(), 2, 1, 300, 80, 40000, 30, 25);
    listeProduits[nbProduits] = new Produit((char *)"gaziniere", P_EQU_MAI_GAZINIERE, electroMenager->getId(), 2, 1, 300, 80, 40000, 30, 25);
    listeProduits[nbProduits] = new Produit((char *)"laveLinge", P_EQU_MAI_LAVE_LINGE, electroMenager->getId(), 2, 1, 300, 80, 40000, 30, 40);
    listeProduits[nbProduits] = new Produit((char *)"laveVaiss", P_EQU_MAI_LAVE_VAISS, electroMenager->getId(), 2, 1, 300, 80, 40000, 30, 70);
    listeProduits[nbProduits] = new Produit((char *)"secheLinge", P_EQU_MAI_SECHE_LINGE, electroMenager->getId(), 2, 1, 300, 80, 40000, 30, 80);

    listeProduits[nbProduits] = new Produit((char *)"maison", P_MAI_MAISON, entrepreneur->getId(), 0, 0, 200000, 100000, 400000, 300, 200);
    listeProduits[nbProduits] = new Produit((char *)"appart_etudiant", P_MAI_APPART, entrepreneur->getId(), 0, 0, 20000, 10000, 400000, 300, 1000);

}