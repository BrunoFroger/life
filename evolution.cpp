//-----------------------------------
//
//      evolution.cpp
//
//-----------------------------------

#include "humain.hpp"
#include "entreprise.hpp"
#include "variables.hpp"
#include "statistiques.hpp"
#include "tools.hpp"


//-------------------------------------------
//
//          evolution
//
//-------------------------------------------
void evolution(void){

    printf("evolution ==> debut \n");
    Humain *ptrIndividu;
    Entreprise *ptrEnt;

    // vieillissemnt de la population
    for (int i = 0 ; i < indexHumain ; i++){
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

    if (listeAuto) afficheListeHumains();
    if (statAuto) statistiques();
}