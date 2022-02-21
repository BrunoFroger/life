//-----------------------------------
//
//      evolution.cpp
//
//-----------------------------------

#include <stdio.h>
#include <string>

#include "../inc/evolution.hpp"


//-------------------------------------------
//
//          evolution
//
//-------------------------------------------
void evolution(void){

    nbJours++;

    printf("evolution ===================\n");
    printf("evolution ==> debut \n");
    printf("evolution ===================\n");
    Humain *ptrIndividu;
    Entreprise *ptrEnt;
    //Commande *ptrCommande;
    int i;

    printf("evolution ----------------------------------\n");
    printf("evolution ==> boucle sur les humains \n");
    printf("evolution ----------------------------------\n");
    for (i = 1 ; i < MAX_HUMAINS ; i++){
        if (listeHumains[i] != NULL){
            listeHumains[i]->boucleTraitement();
        }
    }

    printf("evolution ----------------------------------\n");
    printf("evolution ==> boucle sur les entreprises \n");
    printf("evolution ----------------------------------\n");
    for (i = 0 ; i < MAX_ENTREPRISES ; i++){
        if (listeEntreprises[i] != NULL){
            //printf("evolution => lancement du traitement de %s\n", listeEntreprises[i]->getNom());
            listeEntreprises[i]->boucleTraitement();
        }
    }

    printf("evolution ----------------------------------\n");
    printf("evolution ==> boucle sur les produits \n");
    printf("evolution ----------------------------------\n");
    for (i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i] != NULL){
            listeCommandes[i]->boucleTraitement();
        }
    }

    printf("evolution ----------------------------------\n");
    printf("evolution ==> boucle sur les commandes \n");
    printf("evolution ----------------------------------\n");
    for (i = 0 ; i < MAX_PRODUITS ; i++){
        if (listeProduits[i] != NULL){
            listeProduits[i]->boucleTraitement();
        }
    }

    return;

    // vieillissemnt de la population
    for (int i = 0 ; i < MAX_HUMAINS ; i++){
        ptrIndividu = listeHumains[i];
        if (ptrIndividu != NULL){
            ptrIndividu->vieillir();
            // consommation de nourriture pour vivre
            //printf("evolution ==> commande de nourriture \n");
            if (!ptrIndividu->commandeEnCours){
                char prodNourriture[20] = "nourriture";
                Entreprise *ptrEntreprise = getProducteur(prodNourriture);
                if (ptrEntreprise != NULL){
                    printf("evolution ==> tentative commande de %s par %s\n", ptrIndividu->getNomComplet(), prodNourriture);
                    if (ptrEntreprise->commande(ptrIndividu, prodNourriture, 1)){
                        printf("evolution ==> %s commande le produit %s\n", ptrIndividu->getNomComplet(), prodNourriture);
                    } else {
                        printf("evolution ==> ERREUR : commande de %s impossible pour %s\n", prodNourriture, ptrIndividu->getNomComplet());
                    }
                } else {
                    printf("evolution ==> ERREUR : aucune entreprise ne produit (%s)\n", prodNourriture);
                }
            } else {
                printf("evolution ==>  une commande est deja en cours pour %s\n", ptrIndividu->getNomComplet());
            }
        }
    }

    // gestion des commandes en cours
    for (int i = 0 ; i < nbEntreprises ; i++){
        ptrEnt = listeEntreprises[i];
        ptrEnt->gereCommandes();
    }

    // gestion des besoins de personnel

    // generation de produit par les entreprises
    for (int i = 0 ; i < nbEntreprises ; i++){
        ptrEnt = listeEntreprises[i];
        ptrEnt->production();
    }

}