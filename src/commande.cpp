//-----------------------------------
//
//      commande.cpp
//
//-----------------------------------

#include <stdio.h>
#include <string>
#include <iostream>

#include "../inc/variables.hpp"
#include "../inc/tools.hpp"

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
    printf("Commande::Commande => creation d'une commande mode standard \n");
    this->produit = produit;
    this->client = client;
    this->quantite = qte;
    Entreprise *ptrEntreprise;
    for (int i = 0; i < MAX_ENTREPRISES ; i++){
        ptrEntreprise = listeEntreprises[i];
        if (ptrEntreprise->isInCatalogue(produit)){
            this->fabricant = ptrEntreprise;
            this->status = COMMANDE_EN_COURS;
            nbCommandes++;
            return;
        }
    }
    // on a pas trouvé d'entreprise qui a ce produit en stock
    // il faut creer une entreprise qui fabrique ce produit
    printf("Commande::Commande => ERREUR : aucune entreprise ne fabrique ce produit %s\n", produit->getNom());
}

//-------------------------------------------
//
//          Commande::Commande
//
//-------------------------------------------
Commande::Commande(char *datas){
    printf("Commande::Commande => creation d'une commande avec ligne datas (%s)\n", datas);
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
    printf("Commande::Commande => ERREUR : aucune entreprise ne fabrique ce produit %s\n", produit->getNom());
}

//-------------------------------------------
//
//          Commande::displayCommande
//
//-------------------------------------------
void Commande::displayCommande(void){
    printf("+-----------------------------------+\n");
    printf("|     commande n°  %5d            |\n", this->numero);
    printf("+----------+------------------------+\n");
    printf("| Status   |  %20s  |\n", this->getStatusString());
    printf("| quantite |  %20d  |\n", this->quantite);
    printf("| clientId |  %20s  |\n", this->client->getNomComplet());
    printf("| entrepId |  %20s  |\n", this->fabricant->getNom());
    printf("| produit  |  %20s  |\n", this->produit->getNom());
    printf("+----------+------------------------+\n");
    
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
    printf("Commande::boucleTraitement => boucleTraitement : debut\n");
    switch(this->status){
        case COMMANDE_INITIALISEE:
            printf("Commande::boucleTraitement => boucleTraitement : commande de %s initialisee\n", this->produit->getNom());
            // recherche d'une entreprise capable de founir ce produit
            // boucle sur les entreprises
            Entreprise *ptrEntreprise;
            int i;
            for (i = 0 ; i < MAX_ENTREPRISES ; i++){
                ptrEntreprise = listeEntreprises[i];
                // boucle sur les produits de cette entreprise
                if (ptrEntreprise->produitEnStock(this->produit)){
                    // le produit est en stock, on accepte la commande
                    this->status = COMMANDE_EN_COURS;
                    break;
                }
            }
            if (i == MAX_ENTREPRISES){
                printf("Commande::boucleTraitement => aucune entreprise trouvée pour ce produit\n");
                printf("... TODO .... creer une entreprise\n");
            }
            break;
        case COMMANDE_EN_COURS:
            printf("Commande::boucleTraitement => boucleTraitement : commande en cours\n");
            printf(" ..... TODO .....\n");
            break;
        case COMMANDE_DISPONIBLE:
            printf("Commande::boucleTraitement => boucleTraitement : commande disponible\n");
            printf(" ..... TODO .....\n");
            break;
        case COMMANDE_LIVREE:
            printf("Commande::boucleTraitement => boucleTraitement : commande livree\n");
            printf(" ..... TODO .....\n");
            break;
        default:
            printf("Commande::boucleTraitement => ERREUR : status incorrect %d\n", this->status);
    }
}

//-------------------------------------------
//
//          Commande::getStatusString
//
//-------------------------------------------
char *Commande::getStatusString(void){
    switch(status){
        case COMMANDE_INITIALISEE:
            strcpy(tmpString, "INIT");
            break;
        case COMMANDE_EN_COURS:
            strcpy(tmpString, "EN COURS");
            break;
        case COMMANDE_DISPONIBLE:
            strcpy(tmpString, "DISPO");
            break;
        case COMMANDE_LIVREE:
            strcpy(tmpString, "LIVREE");
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
    printf("Commande::sauve => debut\n");
    int id_client, id_fabricant, id_produit;
    id_client = this->client->getId();
    id_fabricant = this->fabricant->getId();
    id_produit = this->produit->getId();
    sprintf(tmpString,"commande %d %d %d %d %d %d", this->numero, this->status, this->quantite, id_client, id_fabricant, id_produit);
    printf("Commande::sauve => ligne sauvegardee : %s\n", tmpString);
    fprintf(fichier, "%s\n", tmpString);
    fflush(fichier);
    printf("Commande::sauve => fin\n");
}

//-------------------------------------------
//
//          Commande::sauveJson
//
//-------------------------------------------
void Commande::sauveJson(FILE *fic){
    //printf("Humain::sauveJson => Sauvegarde de %s\n", this->getNomComplet());
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