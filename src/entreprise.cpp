//-----------------------------------
//
//      entreprise.cpp
//
//-----------------------------------

#include <string.h>
#include "../inc/variables.hpp"
#include "../inc/entreprise.hpp"
#include "../inc/compteBancaire.hpp"
#include "../inc/tools.hpp"



//-------------------------------------------
//
//          Entreprise::init
//
//-------------------------------------------
void Entreprise::init(void){
    // initialise liste des salaries
    for (int i = 0 ; i < MAX_SALARIE ; i++){
        listeSalarie[i].salarie = NULL;
        listeSalarie[i].status = 0;
        listeSalarie[i].remuneration = 0;
        listeSalarie[i].derniereAugmentation = 0;
        listeSalarie[i].productivite = 0;
    }
    // initialise liste des produits
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        strcpy(listeProduits[i].nom,"");
        listeProduits[i].prix = 0;
        listeProduits[i].stock = 0;
        listeProduits[i].stockMini = 0;
        listeProduits[i].coutFabrication = 0;
    }
    // initialise liste des produits
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        listeProduit[i] = NULL;
    }
}

//-------------------------------------------
//
//          Entreprise::~Entreprise
//
//-------------------------------------------
Entreprise::~Entreprise(void){
    nbEntreprises--;
}

//-------------------------------------------
//
//          Entreprise::Entreprise
//
//-------------------------------------------
Entreprise::Entreprise(char *datas){
    char dataNom[50]; 
    int dataId, dataIdPatron, dataTypeProd, dataEffectifMax;
    sscanf(datas,"entreprise %d %s %d %d %d", &dataId, dataNom, &dataIdPatron, &dataTypeProd, &dataEffectifMax);
    this->id = nbEntreprises;
    strcpy(this->nom,dataNom);
    this->patron = getHumainById(dataIdPatron);
    this->nbEmployes = 0;
    this->nbSalaries = 0;
    this->nbCadres = 0;
    embauche(patron, PATRON);
    this->compteBancaire = new CompteBancaire(this->nom);
    this->compteBancaire->credite(10000);
    listeEntreprises[nbEntreprises] = this;
    this->effectifMax = dataEffectifMax;
    nbEntreprises++;
}

//-------------------------------------------
//
//          Entreprise::restore
//
//-------------------------------------------
void Entreprise::restore(char *datas){
    char dataNom[50], typeLigne[25]; 
    int dataIdEnt, dataIdHumain, dataTypeProd, dataEffectifMax;
    int dataPrix, dataStock, dataStockMini, dataCoutFab;
    int dataStatus, dataRemuneration, dataDernAugment, dataProductivite;
    int i = 0;
    sscanf(datas,"%s ", typeLigne);
    if (strcmp(typeLigne, "entreprise") == 0){
        printf("Entreprise::restore => restaure une entreprise : %s", datas);
        sscanf(datas,"%s %d %s %d %d %d", typeLigne, &dataIdEnt, dataNom, &dataIdHumain, &dataTypeProd, &dataEffectifMax);
        printf("..... TODO .....\n");
    } else if (strcmp(typeLigne, "produit") == 0){
        printf("Entreprise::restore => restaure un produit : %s", datas);
        sscanf(datas,"%s %d %s %d %d %d %d", typeLigne, &dataIdEnt, dataNom, &dataPrix, &dataStock, &dataStockMini, &dataCoutFab);
        while (strcmp(listeProduits[i].nom,"") != 0) {
            i++;
        }
        structProduit *ptrProduit = &listeProduits[i];
        strcpy(ptrProduit->nom, dataNom);
        ptrProduit->prix = dataPrix;
        ptrProduit->stock = dataStock;
        ptrProduit->stockMini = dataStockMini;
        ptrProduit->coutFabrication = dataCoutFab;
        printf("Entreprise::restore => retaure le produit %s en position %d\n", ptrProduit->nom, i);
        printf("..... TODO .....\n");
    } else if (strcmp(typeLigne, "salarie") == 0){
        printf("Entreprise::restore => restaure un salarie : %s", datas);
        sscanf(datas,"%s %d %d %d %d %d %d", typeLigne, &dataIdEnt, &dataIdHumain, &dataStatus, &dataRemuneration, &dataDernAugment, &dataProductivite);
        while (i < nbSalaries){
            if (listeSalarie[i].salarie == NULL){
                break;
            } else if (listeSalarie[i].salarie->getId() == dataIdHumain){
                printf("Ce salarie est deja enregistre\n");
                return;
            }
            i++;
        }
        structSalarie *ptrSalarie = &listeSalarie[i];
        ptrSalarie->salarie = listeHumains[i];
        ptrSalarie->status = dataStatus;
        ptrSalarie->remuneration = dataRemuneration;
        ptrSalarie->derniereAugmentation = dataDernAugment;
        ptrSalarie->productivite = dataProductivite;
        nbSalaries++;
        printf("Entreprise::restore => retaure le salarie %s en position %d\n", ptrSalarie->salarie->getNomComplet(), i);
        printf("..... TODO .....\n");
    } else {
        printf("Entreprise::restore => ERREUR : type de ligne inconnu : %s\n ", typeLigne);
    }
}

//-------------------------------------------
//
//          Entreprise::Entreprise
//
//-------------------------------------------
Entreprise::Entreprise(char *nom, int typeProd, Humain *patron, int effectifMax){
    strcpy(this->nom,nom);
    this->typeProduction = typeProd;
    this->patron = patron;
    this->id = nbEntreprises;
    this->nbEmployes = 0;
    this->nbSalaries = 0;
    this->nbCadres = 0;
    embauche(patron, PATRON);
    this->compteBancaire = new CompteBancaire(this->nom);
    this->compteBancaire->credite(10000);
    listeEntreprises[nbEntreprises] = this;
    this->effectifMax = effectifMax;
    nbEntreprises++;
}

//-------------------------------------------
//
//          Entreprise::getNom
//
//-------------------------------------------
char *Entreprise::getNom(void){
    return this->nom;
}

//-------------------------------------------
//
//          Entreprise::getNbSalaries
//
//-------------------------------------------
int Entreprise::getNbSalaries(void){
    return nbSalaries;
}

//-------------------------------------------
//
//          Entreprise::getTypeProd
//
//-------------------------------------------
char *Entreprise::getTypeProd(void){
    switch (this->typeProduction){
        case PROD_NOURITURE:
            strcpy(tmpString, "Nouriture");
            break;
        case PROD_MAISON:
            strcpy(tmpString, "Maison");
            break;
        case PROD_VOITURE:
            strcpy(tmpString, "Voiture");
            break;
        default:
            strcpy(tmpString, "");
            break;
    }
    return tmpString;
}

//-------------------------------------------
//
//          Entreprise::catalogue
//
//-------------------------------------------
void Entreprise::catalogue(void){
    printf("+-------------------------------------------------+\n");
    printf("|  catalogue de l'entreprise %20s |\n", this->nom);
    printf("+---------------------------+-----------+---------+\n");
    printf("|            Nom du produit |     prix  |   stock |\n");
    printf("+---------------------------+-----------+---------+\n");
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        if (strcmp(this->listeProduits[i].nom,"") != 0){
            printf("|     %20s  |   %6d  |   %4d  |\n", this->listeProduits[i].nom, this->listeProduits[i].prix, this->listeProduits[i].stock);
        }
    }
    printf("+---------------------------+-----------+---------+\n");
}

//-------------------------------------------
//
//          Entreprise::getStatusString
//
//-------------------------------------------
char *Entreprise::getStatusString(int status){
    switch(status){
        case EMPLOYE:
            strcpy(tmpString, "Employe");
            break;
        case EMPLSUPP:
            strcpy(tmpString, "Empl supp");
            break;
        case CADRE:
            strcpy(tmpString, "Cadre");
            break;
        case PATRON:
            strcpy(tmpString, "Patron");
            break;
        default:
            strcpy(tmpString, "Inconnu");
            break;
    }
    return tmpString;
}

//-------------------------------------------
//
//          Entreprise::embauche
//
//-------------------------------------------
void Entreprise::embauche(Humain *personne, int status){
    for (int i = 0 ; i < MAX_SALARIE ; i++){
        structSalarie *ptrSalarie = &listeSalarie[i];
        if (ptrSalarie->salarie == NULL){
            switch(status){
                case EMPLOYE:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_EMPLOYE;
                    ptrSalarie->productivite = PRODUCTIVITE_EMPLOYE;
                    break;
                case EMPLSUPP:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_EMPLSUPP;
                    ptrSalarie->productivite = PRODUCTIVITE_EMPLSUPP;
                    break;
                case CADRE:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_CADRE;
                    ptrSalarie->productivite = PRODUCTIVITE_CADRE;
                    break;
                case PATRON:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_PATRON;
                    ptrSalarie->productivite = PRODUCTIVITE_PATRON;
                    break;
                default:
                    printf("Entreprise::embauche => embauche : Status %d incorrect pour %s\n", status, personne->getNomComplet());
                    return;
                    break;
            }
            ptrSalarie->salarie = personne;
            ptrSalarie->status = status;
            ptrSalarie->derniereAugmentation = 0;
            printf("Entreprise::embauche => Creation d'un salarie \"%s\" dans l'entreprise \"%s\" avec un status de %s en position %d\n", 
                ptrSalarie->salarie->getNomComplet(), this->nom, getStatusString(ptrSalarie->status), i);
            nbSalaries++;
            //listeSalaries();
            return;
        }
    }
}

//-------------------------------------------
//
//          Entreprise::addProduit
//
//-------------------------------------------
void Entreprise::addProduit(char *nom, int prix, int stock, int stockMini, int coutProd){
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        structProduit *item = &this->listeProduits[i];
        if (strcmp(item->nom,"") == 0){
            strcpy(item->nom, nom);
            item->prix = prix;
            item->stock = stock;
            item->stockMini = stockMini;
            item->coutFabrication = coutProd;
            printf("Entreprise::addProduit => (produit n° %d) ajout du produit %s au prix de %d, avec un stock de %d\n", i, item->nom, item->prix, item->stock);
            //this->catalogue();
            return;
        }
    }
}

//-------------------------------------------
//
//          Entreprise::getPrix
//
//-------------------------------------------
int Entreprise::getPrix(char *produit){
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        if (strcmp(produit, listeProduits[i].nom) == 0){
            return listeProduits[i].prix;
        }
    }
    return -1;
}

//-------------------------------------------
//
//          Entreprise::nbDisponibles
//
//-------------------------------------------
int Entreprise::nbDisponibles(char *produit){
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        if (strcmp(produit, listeProduits[i].nom) == 0){
            return listeProduits[i].stock;
        }
    }
    return -1;
}

//-------------------------------------------
//
//          Entreprise::getProductionPossible
//
//-------------------------------------------
int Entreprise::getProductionPossible(void){
    int productionPossible = 0;
    for (int i = 0 ; i < nbSalaries ; i++){
        structSalarie ptrSalarie;
        ptrSalarie = listeSalarie[i];
        productionPossible += ptrSalarie.productivite;
    }
    return productionPossible;
}

//-------------------------------------------
//
//          Entreprise::production
//
//-------------------------------------------
void Entreprise::production(void){
    //------
    // production
    //------
    printf("Entreprise::production => Boucle de production de l'entreprise %s (%d salarie)\n", this->nom, nbSalaries);
    listeSalaries();
    // calcul capacité  a produire
    int productionPossible = getProductionPossible();
    printf("Entreprise::production => la quantite de production possible est de %d\n", productionPossible);
    // determination de ce qu'il faut produire

    //------
    // traitement des commandes
    //------
    printf("Entreprise::production => traitement des commandes \n");
    printf("Entreprise::production => ..... TODO .....\n");


    //------
    // salaires
    //------
    printf("Entreprise::production => traitement des salaires des %d salaries\n", nbSalaries);
    for (int i = 0 ; i < nbSalaries ; i++){
        structSalarie *ptrSalarie = &listeSalarie[i];
        if (ptrSalarie->salarie != NULL){
            printf("Entreprise::production => traitement du salaire de %s\n",ptrSalarie->salarie->getNomComplet());
            if (strcmp(ptrSalarie->salarie->getNomComplet(), "dieu") != 0 ) {
                ptrSalarie->salarie->credite(ptrSalarie->remuneration);
            } else {
                printf("Entreprise::production => Dieu ne recois pas de salaire !\n");
            }
        } else {
            printf("Entreprise::production => ERREUR : structure salarie invalide\n");
        }
    }
    printf("Entreprise::production => ..... A verifier .....\n");

}

//-------------------------------------------
//
//          Entreprise::listeSalaries
//
//-------------------------------------------
void Entreprise::listeSalaries(void){
    printf("+---------------------------------------------+\n");
    printf("|       liste des salaries de %15s |\n", this->nom);
    printf("+----------------------+------------+---------+\n");
    printf("|                nom   |   fonction | salaire |\n");
    printf("+----------------------+------------+---------+\n");
    for (int i = 0 ; i < nbSalaries ; i++){
        structSalarie *ptrSalarie = &listeSalarie[i];
        printf("| %20s | %10s |   %5d |\n", ptrSalarie->salarie->getNomComplet(), 
            getStatusString(ptrSalarie->status), ptrSalarie->remuneration);
    }
    printf("+----------------------+------------+---------+\n");
}

//-------------------------------------------
//
//          Entreprise::getProduit
//
//-------------------------------------------
structProduit *Entreprise::getProduit(int index){
    if (strcmp(listeProduits[index].nom,"") != 0){
        return &listeProduits[index];
    } else {
        return NULL;
    }
}

//-------------------------------------------
//
//          Entreprise::produitEnStock
//
//-------------------------------------------
bool Entreprise::produitEnStock(Produit *produit){
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = this->listeProduit[i];
        if (ptrProduit == produit){
            return true;
        }
    }
    return false;
}

//-------------------------------------------
//
//          Entreprise::getSalarie
//
//-------------------------------------------
structSalarie *Entreprise::getSalarie(int index){
    if (strcmp(listeSalarie[index].salarie->getNomComplet(),"") != 0){
        return &listeSalarie[index];
    } else {
        return NULL;
    }
}

//-------------------------------------------
//
//          Entreprise::credite
//
//-------------------------------------------
bool Entreprise::credite(int montant){
    if (montant < 0){
        printf("ERREUR : debit impossible\n");
        return false;
    }
    this->compteBancaire->credite(montant);
    return true;
}

//-------------------------------------------
//
//          Entreprise::debite
//
//-------------------------------------------
bool Entreprise::debite(int montant){
    int solde = this->compteBancaire->getSolde();
    if (solde < montant){
        printf("ERREUR : impossible de debiter la somme de %d, solde insuffisant (%d)\n", montant, solde);
        return false;
    }
    this->compteBancaire->debite(montant);
    return true;
}

//-------------------------------------------
//
//          Entreprise::gereCommandes
//
//-------------------------------------------
void Entreprise::gereCommandes(void){
    printf("...TODO...\n");
    printf("Entreprise::gereCommandes => fin \n");
}

//-------------------------------------------
//
//          Entreprise::recrutement
//
//-------------------------------------------
void Entreprise::gereRecrutement(int typeRecrutement){
    printf("Analyse si besoin de recruter des salariés\n");
    for (int i = 0 ; i< MAX_PRODUITS ; i++){
        structProduit *ptrProduit = &listeProduits[i];
        if (strcmp(ptrProduit->nom, "") != 0 ){
            if (ptrProduit->stock <= ptrProduit->stockMini){
                int productionPossible = getProductionPossible();
                if (ptrProduit->coutFabrication > productionPossible){
                    printf("recrutement necessaire pour maintenir le stock de %s\n", ptrProduit->nom);
                    Humain *ptrHumain;
                    for (int i = 0 ; i < MAX_HUMAINS ; i++){
                        ptrHumain = listeHumains[i];
                        if (ptrHumain != NULL){
                            // on verifie si cette personne est employable
                            if ( (ptrHumain->getStatus() != MORT) &&
                                (ptrHumain->getAge() > AGE_DEBUT_ACTIVITE) &&
                                (ptrHumain->getAge() < AGE_RETRAITE ) &&
                                (ptrHumain->getEmployeur() != NULL) ){
                                // cette personne est disponible pour etre embauchée
                                //if ()
                                embauche(ptrHumain, typeRecrutement);
                                if (nbEmployes > nbCadres * 20) {
                                    // trop de salaries, il faut recruter un cadre
                                    gereRecrutement(CADRE);
                                } 
                            }
                        }
                    }
                    printf("  .... A verifier .... \n");
                }
            }
        }
    }
}

//-------------------------------------------
//
//          Entreprise::isInCatalogue
//
//-------------------------------------------
bool Entreprise::isInCatalogue(char *produit){
    //printf("Entreprise::isInCatalogue => debut tests si %s au catalogue\n", produit);
    structProduit ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = listeProduits[i];
        if (strcmp(ptrProduit.nom, produit) == 0){
            return true;
        }
    }
    return false;
}
//-------------------------------------------
//
//          Entreprise::isInCatalogue
//
//-------------------------------------------
bool Entreprise::isInCatalogue(Produit *produit){
    printf("Entreprise::isInCatalogue => debut tests si %s au catalogue\n", produit->getNom());
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = listeProduit[i];
        if (ptrProduit == produit){
            return true;
        }
    }
    return false;
}

//-------------------------------------------
//
//          Entreprise::sauve
//
//-------------------------------------------
void Entreprise::sauve(FILE *fic){
    printf("Entreprise::sauve => Sauvegarde de l'entreprise %s\n", this->nom);
    char ligne[500];
    char tmp[500];
    int id_patron = this->patron->getId();
    strcpy(ligne, "");
    sprintf(tmp, "entreprise %d %s %d %d %d", this->id, this->nom, id_patron, 
            this->typeProduction, this->effectifMax);
    strcat(ligne, tmp);
    strcat(ligne, "\n");
    fputs(ligne, fic);
    printf("Entreprise::sauve => Ligne a sauvegarder : %s\n", ligne);
    fflush(fic);

    // boucle sur les produits
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        structProduit *item = &this->listeProduits[i];
        if (strcmp(item->nom,"") != 0){
            // produit idEntreprise nomProduit prix stock stockMini coutFabrication
            printf("Entreprise::sauve => Sauvegarde du produit %s\n", item->nom);
            sprintf(ligne, "produit %d %s %d %d %d %d", this->id, item->nom, 
                item->prix, item->stock, item->stockMini, item->coutFabrication);
            strcat(ligne, "\n");
            fputs(ligne, fic);
            printf("Entreprise::sauve => Ligne a sauvegarder : %s\n", ligne);
        }
    }
    fflush(fic);

    // boucle sur les salaries
    for (int i = 0 ; i < nbSalaries ; i++){
        structSalarie *item = &this->listeSalarie[i];
        if (item->salarie != NULL){
            // salarie idEntreprise idSalarie idCptBanque status salaire derniereAugmentation productivite
            printf("Entreprise::sauve => Sauvegarde du salarie %s\n", item->salarie->getNomComplet());
            sprintf(ligne, "salarie %d %d %d %d %d %d ", this->id, item->salarie->getId(), 
                    item->status, item->remuneration, item->derniereAugmentation, item->productivite);
            strcat(ligne, "\n");
            fputs(ligne, fic);
            printf("Entreprise::sauve => Ligne a sauvegarder : %s\n", ligne);
        }
    }
    fflush(fic);
}

//-------------------------------------------
//
//          Entreprise::getEffectifMax
//
//-------------------------------------------
int Entreprise::getEffectifMax(void){
    return this->effectifMax;
}


//-------------------------------------------
//
//          Entreprise::getId
//
//-------------------------------------------
int Entreprise::getId(void){
    return this->id;
}

//-------------------------------------------
//
//          Entreprise::boucleTraitement
//
//-------------------------------------------
void Entreprise::boucleTraitement(void){
    printf("Entreprise::boucleTraitement => debut\n");
    printf("Entreprise::boucleTraitement => fin\n");
}
