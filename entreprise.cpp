//-----------------------------------
//
//      entreprise.cpp
//
//-----------------------------------

#include <string.h>
#include "variables.hpp"
#include "entreprise.hpp"
#include "compteBancaire.hpp"

//-------------------------------------------
//
//          Entreprise::Entreprise
//
//-------------------------------------------
Entreprise::Entreprise(char *nom, int typeProd, Humain *patron){
    strcpy(this->nom,nom);
    this->typeProduction = typeProd;
    this->patron = patron;
    this->nbEmployes = 0;
    this->nbSalaries = 0;
    this->nbCadres = 0;
    // initialise liste des salaries
    for (int i = 0 ; i < MAX_SALARIE ; i++){
        listeSalarie[i].salarie = NULL;
        listeSalarie[i].compteBancaire = NULL;
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
    // initialise liste des commandes
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        listeCommandes[i].client = NULL;
        strcpy(listeCommandes[i].nomProduit,"");
        listeCommandes[i].quantite=-1;
    }
    embauche(patron, PATRON);
    this->compteBancaire = new CompteBancaire(this->nom);
    this->compteBancaire->credite(10000);
    listeEntreprises[nbEntreprises] = this;
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
            return "Nouriture";
        case PROD_MAISON:
            return "Maison";
        case PROD_VOITURE:
            return "Voiture";
        default:
            return "";
    }
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
            return "Employe";
        case CADRE:
            return "Cadre";
        case PATRON:
            return "Patron";
    }
    return"Inconnu";
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
                    ptrSalarie->productivite = 10;
                    break;
                case CADRE:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_CADRE;
                    ptrSalarie->productivite = 3;
                    break;
                case PATRON:
                    ptrSalarie->remuneration = SALAIRE_DEBUT_PATRON;
                    ptrSalarie->productivite = 1;
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
            listeSalaries();
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
        if (strcmp(this->listeProduits[i].nom,"") == 0){
            structProduit *item = &this->listeProduits[i];
            strcpy(item->nom, nom);
            item->prix = prix;
            item->stock = stock;
            item->stockMini = stockMini;
            item->coutFabrication = coutProd;
            printf("Entreprise::addProduit => ajout du produit %s au prix de %d, avec un stock de %d\n", item->nom, item->prix, item->stock);
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
//          Entreprise::commande
//
//-------------------------------------------
bool Entreprise::commande(Humain *client, char *produit, int qte){
    if (strcmp(client->getNom(),"dieu") != 0){
        printf("Entreprise::commande => tentative de commmande de %s dans entreprise %s par %s\n",
            produit, this->nom, client->getNomComplet());
        for (int i = 0 ; i < MAX_COMMANDES ; i++){
            structCommande *commande=&listeCommandes[i];
            if (commande->client == NULL){
                printf("Entreprise::commande => traitement de la commande %s pour %s\n", produit, client->getNomComplet());
                commande->client = client;
                strcpy(commande->nomProduit, produit);
                commande->quantite = qte;
                printf("Entreprise::commande => ..... a verifier .....\n");
                return true;
            }
        }
        printf("Entreprise::commande => ERREUR : commande de %s impossible pour %s\n", produit, client->getNomComplet());
        return false;
    } else {
        printf("Dieu ne fait pas de commande\n");
        return false;
    }
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
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        structProduit produit = listeProduits[i];
        if (strlen(produit.nom) != 0){
            if (produit.stock <= produit.stockMini){
                printf("Entreprise::production => Il faut fabriquer du produit %s\n", produit.nom);
                printf("Entreprise::production => ..... TODO .....\n");
            }
        }
    }

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
                ptrSalarie->compteBancaire->credite(ptrSalarie->remuneration);
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
//          Entreprise::getCommande
//
//-------------------------------------------
structCommande *Entreprise::getCommande(int index){
    if (listeCommandes[index].client != NULL){
        return &listeCommandes[index];
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
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        structCommande *ptrCommande = &listeCommandes[i];
        for (int i = 0 ; i < MAX_COMMANDES ; i++){
            if (ptrCommande->client != NULL){
                printf("Entreprise::gereCommandes => Traitement de la commande de %d %s par %s\n",
                    ptrCommande->quantite, ptrCommande->nomProduit, ptrCommande->client->getNomComplet());
                // recherche disponibilite du produit
                for (int ii = 0 ; ii < MAX_PRODUITS ; ii++){
                    if (strcmp(ptrCommande->nomProduit, listeProduits[ii].nom) == 0){
                        // on a trouve le produit
                        structProduit *ptrProduit = &listeProduits[ii];
                        if (ptrProduit->stock > ptrCommande->quantite){
                            printf("Entreprise::gereCommandes => Livraison possible diu produit\n");
                            ptrCommande->client->debite(ptrProduit->prix);
                            this->credite(ptrProduit->prix);
                            ptrProduit->stock -= ptrCommande->quantite;
                            ptrCommande->client=NULL;
                            ptrCommande->quantite=0;
                            strcpy(ptrCommande->nomProduit, "");
                            printf("Entreprise::gereCommandes =>  .... Done .....\n");
                        } else {
                            printf("Entreprise::gereCommandes => pas assez de stock pour cette commande on lance la production de ce produit\n");
                            printf("Entreprise::gereCommandes =>  .... TODO .....\n");
                        }
                    }
                }
            }
        }
    }
}

//-------------------------------------------
//
//          Entreprise::recrutement
//
//-------------------------------------------
void Entreprise::recrutement(int typeRecrutement){
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
                                (ptrHumain->getAge() > 20) &&
                                (ptrHumain->getAge() < 65 ) &&
                                (ptrHumain->getEmployeur() != NULL) ){
                                // cette personne est disponible pour etre embauchée
                                embauche(ptrHumain, typeRecrutement);
                                if (nbEmployes > nbCadres * 20) {
                                    // trop de salaries, il faut recruter un cadre
                                    recrutement(CADRE);
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