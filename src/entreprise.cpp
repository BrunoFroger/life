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
    printf("Entreprise::Entreprise => entreprise %s cree ligne datas (id=%d)\n", this->nom, this->id);
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
    int dataStatus, dataRemuneration, dataDernAugment, dataProductivite;
    int i = 0;
    sscanf(datas,"%s ", typeLigne);
    if (strcmp(typeLigne, "entreprise") == 0){
        printf("Entreprise::restore => restaure une entreprise : %s", datas);
        sscanf(datas,"%s %d %s %d %d %d", typeLigne, &dataIdEnt, dataNom, &dataIdHumain, &dataTypeProd, &dataEffectifMax);
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
    //printf("Entreprise::Entreprise => tentative creation entreprise <%s>\n", nom);
    strcpy(this->nom,nom);
    this->typeProduction = typeProd;
    this->patron = patron;
    this->id = nbEntreprises;
    this->nbEmployes = 0;
    this->nbSalaries = 0;
    this->nbCadres = 0;
    //printf("Entreprise::Entreprise => init du patron\n");
    if (patron != NULL){
        embauche(patron, PATRON);
    }
    this->compteBancaire = new CompteBancaire(this->nom);
    this->compteBancaire->credite(10000);
    listeEntreprises[nbEntreprises] = this;
    this->effectifMax = effectifMax;
    nbEntreprises++;
    printf("Entreprise::Entreprise => entreprise %s cree (id=%d)\n", this->nom, this->id);
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
//          Entreprise::catalogue
//
//-------------------------------------------
void Entreprise::catalogue(void){
    printf("+-------------------------------------------------+\n");
    printf("|  catalogue de l'entreprise %20s |\n", this->nom);
    printf("+---------------------------+-----------+---------+\n");
    printf("|            Nom du produit |     prix  |   stock |\n");
    printf("+---------------------------+-----------+---------+\n");
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = listeProduit[i];
        if (ptrProduit != NULL){
            printf("|     %20s  |   %6d  |   %4d  |\n", ptrProduit->getNom(), ptrProduit->getPrix(), ptrProduit->getStock());
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
    printf("Entreprise::embauche => recrutement de %s en tant que %s\n", personne->getNomComplet(), getStatusString(status));
    if (personne != NULL){
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
                        this->patron=personne;
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
                personne->setEmployeur(this);
                //listeSalaries();
                return;
            }
        }
    }
}

//-------------------------------------------
//
//          Entreprise::supprimeSalarie
//
//-------------------------------------------
void Entreprise::supprimeSalarie(Humain *personne){
    printf("Entreprise::supprimeSalarie => supprime salarie %s\n", personne->getNomComplet());
    printf("nbSAlarie = %d\n", nbSalaries);
    this->listeSalaries();
    for (int i = 0 ; i < MAX_SALARIE ; i++){
        printf("Entreprise::supprimeSalarie => test salarie %d\n", i);
        structSalarie *ptrSalarie = &listeSalarie[i];
        if (ptrSalarie->salarie != NULL){
            printf(" le salarie n'est pas null\n");
            if (ptrSalarie->salarie == personne){
                printf("c'est le bon salarie\n");
                ptrSalarie->status = 0;
                ptrSalarie->salarie->setEmployeur(NULL);
                printf("Entreprise::supprimeSalarie => suppression d'un salarie \"%s\" de l'entreprise \"%s\" \n", 
                    ptrSalarie->salarie->getNomComplet(), this->nom);
                nbSalaries--;
                ptrSalarie->salarie = NULL;
                //listeSalaries();
                return;
            }
        }
    }
    printf("Entreprise::supprimeSalarie => le salarie(%s) ne travaille pas dans l'entreprise %s\n", personne->getNomComplet(), this->nom);
}

//-------------------------------------------
//
//          Entreprise::addProduit
//
//-------------------------------------------
void Entreprise::addProduit(Produit *newProduit){
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        if (listeProduit[i] == NULL){
            listeProduit[i] = newProduit;
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
        if (listeProduit[i] != NULL){
            if (strcmp(produit, listeProduits[i]->getNom()) == 0){
                return listeProduit[i]->getPrix();
            }
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
        if (listeProduit[i] != NULL){
            if (strcmp(produit, listeProduits[i]->getNom()) == 0){
                return listeProduit[i]->getStock();
            }
        }
    }
    return 0;
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
    printf("Entreprise::production => Boucle de production de l'entreprise %s (%d salarie)\n", this->nom, nbSalaries);
    listeSalaries();
    // calcul capacité  a produire
    int productionPossible = getProductionPossible();
    printf("Entreprise::production => la quantite de production possible est de %d\n", productionPossible);
    // determination de ce qu'il faut produire
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = this->listeProduit[i];
        if (ptrProduit != NULL){
            if (ptrProduit->getStock() < ptrProduit->getStockMini()){
                // il faut fabriquer ce produit
                productionPossible -= ptrProduit->getCoutProduction();
                ptrProduit->miseAJourStock(1);
            }
        }
    }
}

//-------------------------------------------
//
//          Entreprise::traiteSalaires
//
//-------------------------------------------
void Entreprise::traiteSalaires(void){
    //------
    // salaires
    //------
    if ((nbJours % 30) == 0){
        // on verse la paye tous les 30 jours
        printf("Entreprise::traiteSalaires => traitement des salaires des %d salaries\n", nbSalaries);
        for (int i = 0 ; i < nbSalaries ; i++){
            structSalarie *ptrSalarie = &listeSalarie[i];
            if (ptrSalarie->salarie != NULL){
                printf("Entreprise::traiteSalaires => traitement du salaire de %s\n",ptrSalarie->salarie->getNomComplet());
                if (strcmp(ptrSalarie->salarie->getNomComplet(), "dieu") != 0 ) {
                    int salaire = ptrSalarie->remuneration;
                    if (this->debite(salaire)) {
                        // l'entreprise peut paye le salaire
                        ptrSalarie->salarie->credite(salaire);
                    } else {
                        printf("Entreprise::traiteSalaires => l'entreprise ne peut pas payer ce salaire !\n");
                    }
                } else {
                    printf("Entreprise::traiteSalaires => Dieu ne recois pas de salaire !\n");
                }
            } else {
                printf("Entreprise::traiteSalaires => ERREUR : structure salarie invalide\n");
            }
        }
        printf("Entreprise::traiteSalaires => ..... A verifier .....\n");
    }
}

//-------------------------------------------
//
//          Entreprise::listeSalaries
//
//-------------------------------------------
void Entreprise::listeSalaries(void){
    //printf("nombre de salarie = %d\n", nbSalaries);
    printf("+--------------------------------------------------+\n");
    printf("| salaries de %-25s            |\n", this->nom);
    printf("+-------------------------+--------------+---------+\n");
    printf("|                   nom   |     fonction | salaire |\n");
    printf("+-------------------------+--------------+---------+\n");
    for (int i = 0 ; i < nbSalaries ; i++){
        structSalarie ptrSalarie = listeSalarie[i];
        printf("|    %20s |   %10s |   %5d |\n", ptrSalarie.salarie->getNomComplet(), 
            getStatusString(ptrSalarie.status), ptrSalarie.remuneration);
    }
    printf("+-------------------------+--------------+---------+\n");
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
    printf("Entreprise::gereCommandes => %s\n", this->nom);
    Commande *ptrCde;
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        ptrCde = listeCommandes[i];
        if (ptrCde != NULL){
            ptrProduit = ptrCde->getProduit();
            if (ptrCde->getFabricant() == this){
                switch(ptrCde->getStatus()){
                    case COMMANDE_EN_COURS:
                        printf("Entreprise::gereCommandes => commande %d en cours\n", ptrCde->getNumero());
                        // la commande n'est pas encore traitee on test si on peut la traiter
                        // on verifie si on a du stock
                        if (ptrProduit->getStock() >= ptrCde->getQuantite()){
                            // le stock est suffisant, on accepte la commande
                            ptrProduit->miseAJourStock(-ptrCde->getQuantite());
                            ptrCde->changeStatus(COMMANDE_LIVREE);
                        } else {
                            ptrCde->changeStatus(COMMANDE_EN_ATTENTE);
                        }
                        break;
                    case COMMANDE_EN_ATTENTE:
                        printf("Entreprise::gereCommandes => commande %d en attente\n", ptrCde->getNumero());
                        // on verifie si on a du stock
                        if (ptrProduit->getStock() >= ptrCde->getQuantite()){
                            // le stock est suffisant, on accepte la commande
                            ptrProduit->miseAJourStock(-ptrCde->getQuantite());
                            ptrCde->changeStatus(COMMANDE_LIVREE);
                        } else {
                            ptrCde->changeStatus(COMMANDE_EN_ATTENTE);
                        }
                        break;
                    case COMMANDE_SOLDEE:
                        // fin de traitement de cette commande c'est au client de la supprimer
                        printf("Entreprise::gereCommandes => commande %d soldee\n", ptrCde->getNumero());
                        this->credite(ptrProduit->getPrix());
                        listeCommandes[i] = NULL;
                        delete ptrCde;
                        break;
                    default:
                        //printf("Entreprise::gereCommandes => status de commande %d inconnu (%d)\n", ptrCde->getNumero(), ptrCde->getStatus());
                        break;
                }
            }
        }
    }
    printf("Entreprise::gereCommandes => fin \n");
}

//-------------------------------------------
//
//          Entreprise::recrutement
//
//-------------------------------------------
void Entreprise::gereRecrutement(){
    printf("Entreprise::gereRecrutement => Analyse si besoin de recruter des salariés\n");
    int besoinDeProduction = 0;
    Produit *ptrProduit;
    for (int i = 1 ; i< MAX_PRODUITS ; i++){
        ptrProduit = listeProduit[i];
        if (ptrProduit != NULL){
            besoinDeProduction += ptrProduit->getQuantiteAProduire();
        }
    }
    printf("Entreprise::gereRecrutement => besoin de production = %d\n", besoinDeProduction);
    printf("Entreprise::gereRecrutement => production possible = %d\n", getProductionPossible());
    if (besoinDeProduction > getProductionPossible()){
        // il faut recruter
        printf("Entreprise::gereRecrutement => besoin de recruter : \n");
        Humain *ptrHumain;
        for (int i = 1 ; i < MAX_HUMAINS ; i++){
            ptrHumain = listeHumains[i];
            if (ptrHumain != NULL){
                // on verifie si cette personne est employable
                if ( (ptrHumain->getStatus() != MORT) &&
                    (ptrHumain->getAge() > AGE_DEBUT_ACTIVITE) &&
                    (ptrHumain->getAge() < AGE_RETRAITE ) &&
                    (! ptrHumain->estSalarie()) ){
                    // cette personne est disponible pour etre embauchée
                    //if ()
                    if (nbEmployes > nbEmployeSup * 10) {
                        // trop de salaries, il faut recruter un cadre
                        if (nbEmployeSup > nbCadres * 3){
                            embauche(ptrHumain, CADRE);
                        } else {
                            embauche(ptrHumain, EMPLSUPP);
                        }
                    } else {
                        embauche(ptrHumain, EMPLOYE);
                    }
                    break;
                }
            }
        }
    } else {
        printf("Entreprise::gereRecrutement => pas besoin de recruter\n");
    }
}

//-------------------------------------------
//
//          Entreprise::isInCatalogue
//
//-------------------------------------------
bool Entreprise::isInCatalogue(Produit *produit){
    //printf("Entreprise::isInCatalogue => debut tests si %s au catalogue de %s\n", produit->getNom(), this->nom);
    Produit *ptrProduit;
    for (int i = 0 ; i < MAX_PRODUITS ; i++){
        ptrProduit = listeProduit[i];
        if (ptrProduit != NULL){
            if (strcmp(ptrProduit->getNom(), produit->getNom()) == 0){
                return true;
            }
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
    //printf("Entreprise::sauve => Sauvegarde de l'entreprise %s\n", this->nom);
    char ligne[500];
    char tmp[500];
    int id_patron = this->patron->getId();
    strcpy(ligne, "");
    sprintf(tmp, "entreprise %d %s %d %d %d", this->id, this->nom, id_patron, 
            this->typeProduction, this->effectifMax);
    strcat(ligne, tmp);
    strcat(ligne, "\n");
    fputs(ligne, fic);
    //printf("Entreprise::sauve => Ligne a sauvegarder : %s\n", ligne);
    fflush(fic);

    /*
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
    */
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
//          Entreprise::sauveJson
//
//-------------------------------------------
void Entreprise::sauveJson(FILE *fic){
    //printf("Entreprise::sauveJson => Sauvegarde de %s\n", this->getNomComplet());
    int id_patron;
    id_patron = this->patron->getId();
    fprintf(fic, "      { \"id\": %d, ", this->id);
    fprintf(fic, "\"nom\": \"%s\" ,", this->nom);
    fprintf(fic, "\"id_patron\": \"%d\" ,", id_patron);
    fprintf(fic, "\"typeProduction\": %d ,", this->typeProduction);
    fprintf(fic, "\"effectifMax\": %d ", this->effectifMax);
    fprintf(fic, " },");
    fprintf(fic, "\n");
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
//          Entreprise::getPatron
//
//-------------------------------------------
Humain *Entreprise::getPatron(void){
    return this->patron;
}

//-------------------------------------------
//
//          Entreprise::checkPatron
//
//-------------------------------------------
void Entreprise::checkPatron(void){
    if (this->patron != NULL){
        if (this->patron->getStatus() != MORT){
            //printf("Entreprise::checkPatron => %s a deja un patron\n", this->nom);
            return;
        }
        // le patron est decede, on le supprime 
        this->supprimeSalarie(this->patron);
        this->patron=NULL;
    }
    printf("Entreprise::checkPatron => pas de patron pour %s\n", this->nom);
    Humain *ptrHumain;
    for (int i = 1 ; i < MAX_HUMAINS ; i++){
        ptrHumain = listeHumains[i];
        if (ptrHumain != NULL){
            if (! ptrHumain->estSalarie()){
                //printf("Entreprise::checkPatron => %s ne travaille pas on peut le recruter\n", ptrHumain->getNomComplet());
                // cette personne ne travaille pas, elle peut devenir le patron de cette entreprise
                this->embauche(ptrHumain, PATRON);
                return;
            }
        }
    }  
}

//-------------------------------------------
//
//          Entreprise::boucleTraitement
//
//-------------------------------------------
void Entreprise::boucleTraitement(void){
    printf("Entreprise::boucleTraitement =>-------------------------------------------------\n");
    printf("Entreprise::boucleTraitement => debut %s (%d)\n", this->nom, this->id);
    checkPatron();
    gereCommandes();
    gereRecrutement();
    production();
    printf("Entreprise::boucleTraitement => fin\n");
}
