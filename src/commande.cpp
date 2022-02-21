//-----------------------------------
//
//      commande.cpp
//
//-----------------------------------

#include <stdio.h>
#include <string>
#include <iostream>

#include "../inc/commande.hpp"

//-------------------------------------------
//
//          Commande::~Commande
//
//-------------------------------------------
Commande::~Commande(void){
    nbCommandes--;
}

//-------------------------------------------
//
//          Commande::Commande
//
//-------------------------------------------
Commande::Commande(Produit *produit, int qte, Humain *client){
    //debugCommande=true;
    if (debugCommande) printf("Commande::Commande => creation de la commande %d mode standard (%s commande %d %s) : ", nbCommandes, client->getNomComplet(), qte, produit->getNom());
    this->produit = produit;
    this->client = client;
    this->quantite = qte;
    this->numero = nbCommandes;
    this->fabricant=NULL;
    this->status=COMMANDE_IMPOSSIBLE;
    Entreprise *ptrEntreprise;
    for (int i = 0; i < MAX_ENTREPRISES ; i++){
        ptrEntreprise = listeEntreprises[i];
        if (ptrEntreprise != NULL){
            if (ptrEntreprise->isInCatalogue(produit)){
                this->numero = nbCommandes;
                this->fabricant = ptrEntreprise;
                this->status = COMMANDE_INITIALISEE;
                if (debugCommande) printf("commande OK\n");
                for (int j = 0 ; j < MAX_COMMANDES ; j++){
                    if (listeCommandes[j] == NULL){
                        listeCommandes[j] = this;
                        break;
                    }
                }
                nbCommandes++;
                return;
            }
        } 
    }
    // on a pas trouvé d'entreprise qui a ce produit en stock
    // il faut creer une entreprise qui fabrique ce produit
    if (debugCommande) printf("commande KO\n");
    if (debugCommande) printf("Commande::Commande => ERREUR : aucune entreprise ne fabrique ce produit %s\n", produit->getNom());
    debugCommande=false;
}

//-------------------------------------------
//
//          Commande::Commande
//
//-------------------------------------------
Commande::Commande(char *datas){
    if (debugCommande) printf("Commande::Commande => creation d'une commande avec ligne datas (%s)\n", datas);
    int ligne_numero, ligne_status, ligne_quantite, ligne_clientId, ligne_entrepriseId, ligne_produitId;
    sscanf(datas, "commande %d %d %d %d %d %d", &ligne_numero, &ligne_status, &ligne_quantite, &ligne_clientId, &ligne_entrepriseId, &ligne_produitId);
    this->numero = ligne_numero;
    this->status = ligne_status;
    this->quantite = ligne_quantite;
    this->client = getHumainById(ligne_clientId);
    this->fabricant = getEntrepriseById(ligne_entrepriseId);
    this->produit = getProduitById(ligne_produitId);
    nbCommandes++;
    //displayCommande();
    // on a pas trouvé d'entreprise qui a ce produit en stock
    // il faut creer une entreprise qui fabrique ce produit
    if (debugCommande) printf("Commande::Commande => ERREUR : aucune entreprise ne fabrique ce produit %s\n", produit->getNom());
}

//-------------------------------------------
//
//          Commande::displayCommande
//
//-------------------------------------------
void Commande::displayCommande(void){
    debugCommande = true;
    if (debugCommande) printf("+-----------------------------------+\n");
    if (debugCommande) printf("|     commande n°  %5d            |\n", this->numero);
    if (debugCommande) printf("+----------+------------------------+\n");
    if (debugCommande) printf("| Status   |  %20s  |\n", this->getStatusString());
    if (debugCommande) printf("| quantite |  %20d  |\n", this->quantite);
    if (debugCommande) printf("| clientId |  %20s  |\n", this->client->getNomComplet());
    if (debugCommande) printf("| entrepId |  %20s  |\n", this->fabricant->getNom());
    if (debugCommande) printf("| produit  |  %20s  |\n", this->produit->getNom());
    if (debugCommande) printf("+----------+------------------------+\n");
    
}

//-------------------------------------------
//
//          Commande::getStatus
//
//-------------------------------------------
int Commande::getStatus(void){
    return status;
}

//-------------------------------------------
//
//          Commande::traitement
//
//-------------------------------------------
void Commande::boucleTraitement(void){
    if (debugCommande) printf("Commande::boucleTraitement => boucleTraitement : debut\n");
    switch(this->status){
        case COMMANDE_INITIALISEE:
            //if (debugCommande) printf("Commande::boucleTraitement => boucleTraitement : commande de %s initialisee\n", this->produit->getNom());
            // recherche d'une entreprise capable de founir ce produit
            // boucle sur les entreprises
            if (this->getProduit()->getStock() > this->quantite){
                this->status = COMMANDE_EN_COURS;
            } else {
                this->status = COMMANDE_EN_ATTENTE;
            }
            break;
        default:
            //if (debugCommande) printf("Commande::boucleTraitement => ERREUR : status incorrect %d\n", this->status);
            break;
    }
}

//-------------------------------------------
//
//          Commande::getStatusString
//
//-------------------------------------------
char *Commande::getStatusString(void){
    switch(status){
        case COMMANDE_IMPOSSIBLE:
            strcpy(tmpString, "IMPOSSIBLE");
            break;
        case COMMANDE_INITIALISEE:
            strcpy(tmpString, "INIT");
            break;
        case COMMANDE_EN_COURS:
            strcpy(tmpString, "EN COURS");
            break;
        case COMMANDE_EN_ATTENTE:
            strcpy(tmpString, "EN ATTENTE");
            break;
        case COMMANDE_DISPONIBLE:
            strcpy(tmpString, "DISPONIBLE");
            break;
        case COMMANDE_LIVREE:
            strcpy(tmpString, "LIVREE");
            break;
        case COMMANDE_SOLDEE:
            strcpy(tmpString, "SOLDEE");
            break;
        default:
            strcpy(tmpString, "INCONNU");
            break;
    }
    return tmpString;
}

//-------------------------------------------
//
//          Commande::getClient
//
//-------------------------------------------
Humain *Commande::getClient(void){
    return this->client;
}

//-------------------------------------------
//
//          Commande::getFabricant
//
//-------------------------------------------
Entreprise *Commande::getFabricant(void){
    return this->fabricant;
}

//-------------------------------------------
//
//          Commande::getClient
//
//-------------------------------------------
Produit *Commande::getProduit(void){
    return this->produit;
}

//-------------------------------------------
//
//          Commande::getQuantite
//
//-------------------------------------------
int Commande::getQuantite(void){
    return this->quantite;
}

//-------------------------------------------
//
//          Commande::getNumero
//
//-------------------------------------------
int Commande::getNumero(void){
    return this->numero;
}

//-------------------------------------------
//
//          Commande::sauve
//
//-------------------------------------------
void Commande::sauve(FILE *fichier){
    if (debugCommande) printf("Commande::sauve => debut\n");
    int id_client, id_fabricant, id_produit;
    id_client = this->client->getId();
    id_fabricant = this->fabricant->getId();
    id_produit = this->produit->getId();
    sprintf(tmpString,"commande %d %d %d %d %d %d", this->numero, this->status, this->quantite, id_client, id_fabricant, id_produit);
    if (debugCommande) printf("Commande::sauve => ligne sauvegardee : %s\n", tmpString);
    fprintf(fichier, "%s\n", tmpString);
    fflush(fichier);
    if (debugCommande) printf("Commande::sauve => fin\n");
}

//-------------------------------------------
//
//          Commande::sauveJson
//
//-------------------------------------------
void Commande::sauveJson(FILE *fic){
    if (debugCommande) printf("Commande::sauveJson => Sauvegarde de la commande %d\n", this->numero);
    int id_client, id_fabricant, id_produit;
    id_client = this->client->getId();
    id_fabricant = this->fabricant->getId();
    id_produit = this->produit->getId();
    fprintf(fic, "      { \"id\": %d, ", this->numero);
    fprintf(fic, "\"status\": \"%d\" ,", this->status);
    fprintf(fic, "\"quantite\": \"%d\" ,", this->quantite);
    fprintf(fic, "\"id_client\": %d ,", id_client);
    fprintf(fic, "\"id_fabricant\": %d ,", id_fabricant);
    fprintf(fic, "\"id_produit\": %d ,", id_produit);
    fprintf(fic, " },");
    fprintf(fic, "\n");
    fflush(fic);
}

//-------------------------------------------
//
//          Commande::changeStatus
//
//-------------------------------------------
void Commande::changeStatus(int nouveauStatus){
    if (debugCommande) printf("Commande::changeStatus => nouveau status = %s\n", getStatusString());
    this->status = nouveauStatus;
}
