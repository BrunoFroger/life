//-----------------------------------
//
//      evolution.cpp
//
//-----------------------------------

#include "../inc/humain.hpp"
#include "../inc/entreprise.hpp"
#include "../inc/variables.hpp"
#include "../inc/statistiques.hpp"
#include "../inc/tools.hpp"
#include "../inc/commande.hpp"


//-------------------------------------------
//
//          evolution
//
//-------------------------------------------
void evolution(void){

    printf("evolution ==> debut \n");
    Humain *ptrIndividu;
    Entreprise *ptrEnt;
    //Commande *ptrCommande;
    int i;

    for (i = 0 ; i < MAX_HUMAINS ; i++){
        if (listeHumains[i] != NULL){
            listeHumains[i]->boucleTraitement();
        }
    }

    for (i = 0 ; i < MAX_ENTREPRISES ; i++){
        if (listeEntreprises[i] != NULL){
            listeEntreprises[i]->boucleTraitement();
        }
    }

    for (i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i] != NULL){
            listeEntreprises[i]->boucleTraitement();
        }
    }

    return;

    // vieillissemnt de la population
    for (int i = 0 ; i < nbHumains ; i++){
        ptrIndividu = listeHumains[i];
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