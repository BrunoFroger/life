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
    printf("evolution ==> boucle sur les commandes \n");
    printf("evolution ----------------------------------\n");
    for (i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i] != NULL){
            listeCommandes[i]->boucleTraitement();
        }
    }

    printf("evolution ----------------------------------\n");
    printf("evolution ==> boucle sur les produits \n");
    printf("evolution ----------------------------------\n");
    for (i = 0 ; i < MAX_PRODUITS ; i++){
        if (listeProduits[i] != NULL){
            listeProduits[i]->boucleTraitement();
        }
    }


    printf("evolution ===================\n");
    printf("evolution ==> fin \n");
    printf("evolution ===================\n");
    printf("\n\n");
}