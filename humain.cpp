//-----------------------------------
//
//      humain.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "humain.hpp"
#include "variables.hpp"
#include "statistiques.hpp"
#include "tools.hpp"
#include "compteBancaire.hpp"

//-------------------------------------------
//
//          Humain::setGenreTexte
//
//-------------------------------------------
void Humain::setGenreTexte(){
    switch(this->genre){
        case HOMME: 
            strcpy(this->genreTexte, "Homme");
            break;;
        case FEMME:
            strcpy(this->genreTexte, "Femme");
            break;;
        default:
            strcpy(this->genreTexte, "Inconnu");
            break;;
    }
}

//-------------------------------------------
//
//          Humain::Humain
//
//-------------------------------------------
Humain::Humain(int genre, char *nom, char *prenom, int age){
    //printf("debut creation humain %s %s en position %d\n", prenom, nom, indexHumain);
    this->id=indexHumain;
    this->genre = genre;
    setGenreTexte();
    this->age = age;
    this->nbEnfants=0;
    strcpy(this->nom, nom);
    strcpy(this->prenom, prenom);
    this->status=CELIBATAIRE;
    this->mere=NULL;
    this->pere=NULL;
    this->conjoint=NULL;
    for (int i = 0 ; i < MAX_ENFANTS ; i++){
        this->enfants[i]=NULL;
    }
    listeHumains[indexHumain++] = this;
    listeHumains[indexHumain] = NULL;
    //displayInfos();
    //printf("fin creation humain %s\n", nom);
    this->employeur=NULL;
    this->compteBancaire = new CompteBancaire(this->getNomComplet());
    this->compteBancaire->credite(100);
    this->commandeEnCours=false;
}

//-------------------------------------------
//
//          Humain::Humain
//
//-------------------------------------------
Humain::Humain(char *datas){
    //printf("Humain::Humain => initialisation partielle d'un humain a partir d'une ligne <%s>\n", datas);
    int index = 0;
    int cpt = 0;
    char tmp[50];
    Humain *ptr;
    int id, genre, age, status;
    char prenom[50], nom [50], reste[100];
    tmp[0] = '\0';
    sscanf(datas, "humain %d %s %s %d %d", &id, prenom, nom, &genre, &age);
    //printf("Humain::Humain => données récupereees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d\n", id, prenom, nom, genre, age);
    if (this->id != id){
        printf("Humain::Humain => ERREUR : l'id de la ligne <%s> ne correspond pas a celui de cet humain (%d)\n", datas, this->id);
    }
    strcpy(this->prenom, prenom);
    strcpy(this->nom, nom);
    this->genre = genre;
    this->age = age;
    return;
}

//-------------------------------------------
//
//          Humain::restore
//
//-------------------------------------------
void Humain::restore(char *datas){
    //printf("Humain::restore => restauration des donnees d'un humain a partir d'une ligne <%s>\n", datas);
    int index = 0;
    int cpt = 0;
    char tmp[50];
    Humain *ptr;
    tmp[0] = '\0';
    char datas_prenom[50], datas_nom[50];
    int datas_id, datas_genre, datas_age, datas_status, datas_idPere, datas_idMere, datas_idConjoint, datas_nbEnfants;

    sscanf(datas, "humain %d %s %s %d %d %d %d %d %d %d", 
            &datas_id, datas_prenom, datas_nom, &datas_genre, &datas_age, &datas_nbEnfants, 
            &datas_status, &datas_idConjoint, &datas_idPere, &datas_idMere);
    //printf("Humain::restore => données récupereees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d, status=%d, idConjoint=%d, idPere=%d, idMere=%d, nbEnfants=%d\n", 
    //        datas_id, datas_prenom, datas_nom, datas_genre, datas_age, datas_status, datas_idConjoint, datas_idPere, datas_idMere, datas_nbEnfants);
    this->nbEnfants = datas_nbEnfants;
    this->status = datas_status;
    this->id = datas_id;
    //printf("Humain::restore => données enregistrees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d, status=%d, nbEnfants=%d\n", 
    //        this->id, this->prenom, this->nom, this->genre, this->age, this->status, this->nbEnfants);
    for (int i = 0 ; i < indexHumain ; i++){
        ptr = listeHumains[i];
        if (ptr->id == datas_idConjoint) {
            ptr->conjoint = this;
            this->conjoint = ptr;
        }
        if (ptr->id == datas_idMere) {
            this->mere = ptr;
            for (int j = 0 ; j < MAX_ENFANTS ; j++){
                if (ptr->enfants[j] == NULL){
                    ptr->enfants[j] = this;
                    break;
                }
            }
        }
        if (ptr->id == datas_idPere) {
            this->pere = ptr;
            for (int j = 0 ; j < MAX_ENFANTS ; j++){
                if (ptr->enfants[j] == NULL){
                    ptr->enfants[j] = this;
                    break;
                }
            }
        }
    }
    //printf("Humain::restore =>  fin\n");

}

//-------------------------------------------
//
//          Humain::~Humain
//
//-------------------------------------------
Humain::~Humain(){
    // rien a faire pour le moment
}

//-------------------------------------------
//
//          Humain::estSalarie
//
//-------------------------------------------
bool Humain::estSalarie(void){
    if (this->employeur != NULL)
        return true;
    return false;
}

//-------------------------------------------
//
//          Humain::displayInfos
//
//-------------------------------------------
void Humain::displayInfos(void){
    printf("\n-------------------------\n");
    printf(" infos Humain\n");
    printf(" genre   = %s\n", this->genreTexte);
    printf(" nom     = %s\n", this->nom);
    printf(" prenom  = %s\n", this->prenom);
    printf(" age     = %d\n", this->age);
    printf(" status  = %d\n", this->status);
    printf(" enfants = %d\n", this->nbEnfants);
    if (this->status == MARIE){
        printf(" conjoint = %s\n", this->conjoint->nom);
    }
    if (this->pere != NULL){
        printf(" pere = %s\n", this->pere->nom);
    }
    if (this->mere != NULL){
        printf(" mere = %s\n", this->mere->nom);
    }
    if (this->nbEnfants != 0){
        printf(" enfants \n");
        for (int i = 0 ; i < this->nbEnfants ; i++){
            if (this->enfants[i] != NULL){
                printf("     %d : %s\n", i, this->enfants[i]->nom);
            }
        }
    }
    printf("-------------------------\n\n");
}

//-------------------------------------------
//
//          Humain::mariage
//
//-------------------------------------------
void Humain::mariage(Humain *conjoint){
    this->conjoint = conjoint;
    this->status=MARIE;
    this->conjoint->conjoint=this;
    this->conjoint->status=MARIE;
    printf("declaration mariage de %s avec %s\n", this->getNomComplet(), conjoint->getNomComplet());
}

//-------------------------------------------
//
//          Humain::descendance
//
//-------------------------------------------
void Humain::descendance(){
    descendance(0);
}

//-------------------------------------------
//
//          Humain::descendance
//
//-------------------------------------------
void Humain::descendance(int level){
    if (level == 0){
        printf("-----------------------------\n");
        printf(" debut descendance de %s %s", this->nom, this->prenom);    
        if (this->conjoint != NULL){
        printf(" avec %s\n", this->conjoint->nom);
        } else {
            printf("\n");
        }
    }
    //printf("descendance de %s (level = %d)", this->nom, level);
    //displayInfos();
    char tabs[100];
    //tabs[0]='*';
    tabs[0]='\0';
    for (int i = 0 ; i < level * 4 ; i++){
        tabs[i]=' ';
        tabs[i+1]='\0';
    }
    if (this->nbEnfants != 0){
        for (int i = 0 ; i < nbEnfants ; i++){
            if (this->enfants[i] != NULL){
                printf("%s %s %s(%c)", tabs, this->enfants[i]->nom, this->enfants[i]->prenom, this->enfants[i]->getGenreTexte()[0]);
                if (this->enfants[i]->conjoint != NULL){
                    printf(" en couple avec %s(%c)", this->enfants[i]->conjoint->nom, this->enfants[i]->conjoint->getGenreTexte()[0]);
                }
                printf("\n");
                this->enfants[i]->descendance(level + 1);            }
        }
    }
    if (level == 0){
        printf(" fin descendance de %s\n", this->nom);
        printf("-----------------------------\n");
    }
}

//-------------------------------------------
//
//          Humain::getId
//
//-------------------------------------------
int Humain::getId(void){
    return this->id;
}

//-------------------------------------------
//
//          Humain::getNbEnfants
//
//-------------------------------------------
int Humain::getNbEnfants(void){
    return this->nbEnfants;
}

//-------------------------------------------
//
//          Humain::getAge
//
//-------------------------------------------
int Humain::getAge(void){
    return this->age;
}

//-------------------------------------------
//
//          Humain::getEmployeur
//
//-------------------------------------------
char *Humain::getEmployeur(void){
    if (this->employeur != NULL){
        return this->employeur->getNom();
    }
    return "";
}

//-------------------------------------------
//
//          Humain::getNom
//
//-------------------------------------------
char *Humain::getNom(void){
    return this->nom;
}

//-------------------------------------------
//
//          Humain::getNomComplet
//
//-------------------------------------------
char result[50];
char *Humain::getNomComplet(void){
    if (strcmp(this->prenom, "") == 0){
        return this->nom;
    }
    if (strcmp(this->nom, "") == 0){
        return this->prenom;
    }
    sprintf(result,"%s %s", this->prenom, this->nom);
    return result;
}

//-------------------------------------------
//
//          Humain::getSoldeBancaire
//
//-------------------------------------------
int Humain::getSoldeBancaire(void){
    return this->compteBancaire->getSolde();;
}

//-------------------------------------------
//
//          Humain::getPrenom
//
//-------------------------------------------
char *Humain::getPrenom(void){
    return this->prenom;
}

//-------------------------------------------
//
//          Humain::getConjoint
//
//-------------------------------------------
Humain *Humain::getConjoint(void){
    return this->conjoint;
}

//-------------------------------------------
//
//          Humain::getPere
//
//-------------------------------------------
Humain *Humain::getPere(void){
    return this->pere;
}

//-------------------------------------------
//
//          Humain::getMere
//
//-------------------------------------------
Humain *Humain::getMere(void){
    return this->mere;
}

//-------------------------------------------
//
//          Humain::getEnfant
//
//-------------------------------------------
Humain *Humain::getEnfant(int index){
    return enfants[index];
}

//-------------------------------------------
//
//          Humain::getGenreTexte
//
//-------------------------------------------
char *Humain::getGenreTexte(void){
    return genreTexte;
}

//-------------------------------------------
//
//          Humain::getStatus
//
//-------------------------------------------
char Humain::getStatus(void){
    switch (this->status){
        case CELIBATAIRE:
            return 'C';
        case MARIE:
            return 'M';
        case DIVORCE:
            return 'D';
        case VEUF:
            return 'V';
        case MORT:
            return 'X';
        default:
            return '?';
    }
}

//-------------------------------------------
//
//          Humain::addEnfant
//
//-------------------------------------------
bool Humain::addEnfant(Humain *enfant){
    if (this->nbEnfants < MAX_ENFANTS){
        //printf("on ajoute l'enfant %s a %s\n", enfant->nom, this-> nom);
        this->enfants[this->nbEnfants]=enfant;
        this->nbEnfants++;
        //printf("%s a maintenant %d enfants\n", this->nom, this->nbEnfants);
        return true;
    }
    return false;
}

//-------------------------------------------
//
//          Humain::naissance
//
//-------------------------------------------
Humain *Humain::naissance(int genre, char *nom, char *prenom){
    //printf(" %s %s donne naissance à %s\n", this->prenom, this->prenom, nom);
    if (this->nbEnfants >= MAX_ENFANTS){
        printf("ERREUR : nb enfants > %d\n", MAX_ENFANTS);
    } else {
        //printf(" max enfants pas atteint, on continue\n");
        //printf("on initialise l'enfant %d\n", nbEnfants);
        try{
            Humain *ptr;
            ptr = ::new Humain(genre, nom, prenom, 0);
            //if (strcmp(this->nom,"dieu") !=0){
                this->addEnfant(ptr);
            //}
            if (this->conjoint != NULL){
                this->conjoint->addEnfant(ptr);
            }
            //printf("initialisation des parents\n");
            if (this->genre == HOMME){
                //printf("le pere declare\n");
                ptr->pere=this;
                ptr->mere=this->conjoint;
            } else {
                //printf("la mere declare (%s)\n", this->nom);
                ptr->pere=this->conjoint;
                ptr->mere=this;
            }
            if (ptr->pere != NULL){
                //printf("pere : %s\n", ptr->pere->nom);
            }
            if (ptr->mere != NULL){
                //printf("mere : %s\n", ptr->mere->nom);
            }
            //ptr->displayInfos();
            //printf(" declaration de naissance de %s => OK\n", nom);
            return ptr;
        } catch(...){
            printf("ERREUR => impossible de creer un enfant\n");
        }
    }
    printf(" fin naissance de %s %s => KO\n", this->nom, this->prenom);
    return NULL;
}

//-------------------------------------------
//
//          Humain::deces
//
//-------------------------------------------
void Humain::deces(void){
    //printf("mort de %s\n", this->nom);
    this->status=MORT;
    if (this->conjoint != nullptr){
        //printf("le conjoint %s devient veuf\n", this->conjoint->nom);
        if (this->conjoint->status != MORT){
            this->conjoint->status = VEUF;
        }
    }
}

//-------------------------------------------
//
//          Humain::sauve
//
//-------------------------------------------
void Humain::sauve(FILE *fic){
    printf("Humain::sauve => Sauvegarde de %s\n", this->getNomComplet());
    char ligne[500];
    char tmp[500];
    int thisPere, thisMere, thisConjoint;
    for (int i = 0 ; i < indexHumain ; i++){
        // nom; genre; age ; nbEnfants; status, conjoint(nom), pere(nom), mere(nom), liste enfants(nom), ...
        sprintf(tmp, "humain %d %s %s %d %d %d %d", this->id, this->prenom, this->nom, this->genre, this->age, this->nbEnfants, this->status);
        //printf("tmp = %s\n", tmp);
        if (this->pere == NULL) thisPere = -1;
        else thisPere = this->pere->getId();
        if (this->mere == NULL) thisMere = -1;
        else thisMere = this->mere->getId();
        if (this->conjoint == NULL) thisConjoint = -1;
        else thisConjoint = this->conjoint->getId();
        sprintf(ligne, "%s %d %d %d ", tmp, thisConjoint, thisPere, thisMere);
        //printf("ligne = %s\n", ligne);
        //printf("sauvegarde de %d enfants\n", nbEnfants);
        for (int j = 0 ; j < nbEnfants ; j++){
            //printf("sauvegarde de l'enfant %d\n", j);
            sprintf(tmp,"%d ", this->enfants[j]->getId());
            strcat(ligne, tmp);
        }
        strcat(ligne, "\n");
    }
    printf("Humain::sauve => Ligne a sauvegarder : %s\n", ligne);
    fputs(ligne, fic);
    fflush(fic);
}

//-------------------------------------------
//
//          Humain::vieillir
//
//-------------------------------------------
void Humain::vieillir(void){
    Humain *ptr, *ptr1;
    if (strcmp(this->nom, "dieu") != 0){ // dieu ne vieilli pas => immortel
        if (this->status != MORT){ // on ne fait pas vieillir les morts
            this->age++;
            int ageRandom;
            int probabilite;
            char saisie[50];

            // test mort de vieillesse 60 + random(40)
            ageRandom = 60 + getRandom(40);
            //printf("age de deces pour %s : %d\n",this->nom, ageRandom);
            if (this->age >= ageRandom){
                printf("*************************************\n");
                printf("%s mort de vieillesse\n", this->getNomComplet());
                printf("*************************************\n");
                this->deces();
                return;
            } else {
                if (this->age > 100){
                    printf("*********************************************************************\n");
                    printf(" age > 100 : %d (ageRandom = %d)\n", this->age, ageRandom);
                    printf("*********************************************************************\n");
                }
            }

            // test mort par accident 1/100 si age > agerandom
            ageRandom = getRandom(100);
            probabilite = getRandom(PROBA_ACCIDENT * PROBA_ACCIDENT);
            if ((probabilite <= PROBA_ACCIDENT) && (this->age > ageRandom)){
                printf("*************************************\n");
                printf("%s mort par accident\n", this->getNomComplet());
                printf("*************************************\n");
                this-> deces();
                return;
            }

            // test candidats au mariage
            // recherche d'un homme celibataire ou veuf
            if ((this->getGenreTexte()[0] == 'H') && (this->getAge() >= AGE_DEBUT_MARIAGE)){
                if ((this->getStatus() == 'C') || (this->getStatus() == 'V')){
                    // candidat potentiel au mariage
                    //printf("%s est candidat au mariage\n", this->nom);
                    // recherche partenaire
                    for (int j = 0 ; j < indexHumain ; j++){
                        ptr1 = listeHumains[j];
                        if ((ptr1->getGenreTexte()[0] == 'F') && (ptr1->getAge() >= AGE_DEBUT_MARIAGE)){
                            if ((ptr1->getStatus() == 'C') || (ptr1->getStatus() == 'V')){
                                // candidate potentielle au mariage
                                //printf("%s est candidate au mariage\n", ptr1->nom);
                                int differenceAge = abs(this->getAge() - ptr1->getAge());
                                if (abs(this->getAge() - ptr1->getAge()) > DIFF_AGE_MARIAGE){
                                    //printf("mariage impossible a cause de la difference d'age\n");
                                } else {
                                    if ((rand() % PROBA_MARIAGE) == 0){
                                        // 1 chance sur n qu'elle accepte
                                        ptr1->mariage(this);
                                        return;
                                    }else {
                                        //printf("mariage refuse\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // test generation d'une naissance
            ptr1 = NULL;
            if (this->getGenreTexte()[0] == 'H'){
                if (this->conjoint != NULL){
                    ptr1 = this->conjoint;
                    //printf("teste compatibilite naissance entre %s et %s\n", this->getNomComplet(), ptr1->getNomComplet());
                    if ((this->getAge() > AGE_DEBUT_NAISSANCE) && (ptr1->getAge() > AGE_DEBUT_NAISSANCE)){
                        //printf("Les deux parents ont + 25 ans\n");
                        if ((this->getAge() < AGE_FIN_NAISSANCE) && (ptr1->getAge() < AGE_FIN_NAISSANCE)){
                            //printf("Les deux parents ont - 40 ans\n");
                            //printf("%s et %s sont les futurs parents\n", this->getNomComplet(), ptr1->getNomComplet());
                            char newPrenom[25];
                            int genreEnfant = getRandomGenre();
                            switch (genreEnfant){
                                case HOMME:
                                    //printf("%s et %s ont un fils\n", this->getNomComplet(), ptr1->getNomComplet());
                                    strcpy(newPrenom,getPrenomMasculin());
                                    break;
                                case FEMME:
                                    //printf("%s et %s ont une fille\n", this->getNomComplet(), ptr1->getNomComplet());
                                    strcpy(newPrenom,getPrenomFeminin());
                                    break;
                                default:
                                    printf("ERREUR : genre de l'enfant inconuu (%d)\n", genreEnfant);
                                    break;
                            }
                            //printf("prenom de l'enfant : ");
                            //scanf("%s", saisie);
                            if ((rand() % 5) == 0){ // 1 chance sur 5 d'avoir un enfant cette annee
                                this->naissance(genreEnfant, this->nom, newPrenom);
                                return;
                            }
                        }
                    }
                }
            }

            // gestion des achats potentiels
        }
    } else {
        // dieu genere des naissance s'il n'y pas assez d'humains
        if(getNbVivants() < 15){
            enfantDieu child = getRandomEnfant();
            printf("enfant genere automatiquement par dieu (%s %s,%d)\n", child.nom, child.prenom, child.genre);
            this->naissance(child.genre, child.nom, child.prenom);
            //printf("fin enfant genere automatiquement par dieu \n");
        }
    }
}

//-------------------------------------------
//
//          Humain::credite
//
//-------------------------------------------
bool Humain::credite(int montant){
    if (montant < 0){
        printf("ERREUR : debit impossible\n");
        return false;
    }
    this->compteBancaire->credite(montant);
    return true;
}

//-------------------------------------------
//
//          Humain::debite
//
//-------------------------------------------
bool Humain::debite(int montant){
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
//          Humain::getNumCompte
//
//-------------------------------------------
int Humain::getNumCompte(void){
    return this->compteBancaire->getNumCompte();;
}