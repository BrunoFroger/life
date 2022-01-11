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

Humain::Humain(int genre, char *nom, char *prenom, int age){
    //printf("debut creation humain %s\n", nom);
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
    listeHumains[indexHumain++]=this;
    //displayInfos();
    //printf("fin creation humain %s\n", nom);
}

Humain::Humain(char *datas){
    printf("creation d'un humain a partir d'une ligne <%s>\n", datas);
    int index = 0;
    int cpt = 0;
    char tmp[50];
    Humain *ptr;
    tmp[0] = '\0';
    for (int i = 0 ; i < strlen(datas) ; i++){
        if (datas[i] != ';'){
            tmp[index++] = datas[i];
            tmp[index] = '\0';
        } else {
            printf("<%s>",tmp);
            switch(cpt++){
                case 0: // id
                    this->id=atoi(tmp);
                    printf("id = %d\n", this->id);
                    break;
                case 1: // nom
                    strcpy(this->nom,tmp);
                    printf("nom = %s\n", this->nom);
                    break;
                case 2: // prenom
                    strcpy(this->prenom,tmp);
                    printf("prenom = %s\n", this->prenom);
                    break;
                case 3: // genre
                    this->genre=atoi(tmp);
                    setGenreTexte();
                    printf("genre = %s\n", this->genreTexte);
                    break;
                case 4: // age
                    this->age=atoi(tmp);
                    printf("age = %d\n", this->age);
                    break;
                case 5: // nbEnfants
                    this->nbEnfants=0;
                    printf("nbEnfants = %d\n", this->nbEnfants);
                    break;
                case 6: // status
                    this->status=atoi(tmp);
                    printf("status = %d\n", this->status);
                    break;
                case 7: // conjoint
                    printf("conjoint = %s\n", tmp);
                    if (strcmp(tmp,"") != 0){
                        //printf("initialisation du conjoint\n");
                        for (int i = 0 ; i < indexHumain ; i++){
                            ptr = listeHumains[i];
                            if (strcmp(ptr->nom, tmp) == 0){
                                this->conjoint = ptr;
                                this->conjoint->conjoint = this;
                            }
                        }
                    }
                    break;
                case 8: // pere
                    printf("pere = %s\n", tmp);
                    if (strcmp(tmp,"") != 0){
                        //printf("initialisation du pere\n");
                        for (int i = 0 ; i < indexHumain ; i++){
                            ptr = listeHumains[i];
                            if (strcmp(ptr->nom, tmp) == 0){
                                this->pere = ptr;
                                ptr->addEnfant(this);
                            }
                        }
                    }
                    break;
                case 9: // mere
                    printf("mere = %s\n", tmp);
                    if (strcmp(tmp,"") != 0){
                        //printf("initialisation de la mere\n");
                        for (int i = 0 ; i < indexHumain ; i++){
                            ptr = listeHumains[i];
                            if (strcmp(ptr->nom, tmp) == 0){
                                this->mere = ptr;
                                ptr->addEnfant(this);
                            }
                        }
                    }
                    break;
                default: // enfants
                    printf("enfant = %s\n", tmp);
                    if (strcmp(tmp,"") != 0){
                        //printf("initialisation d'un enfant\n");
                    }
                    break;
            }
            index = 0;
            tmp[index] = '\0';
        }
    }
    printf("\n");
    listeHumains[indexHumain++]=this;
}

Humain::~Humain(){
    // rien a faire pour le moment
}

void Humain::displayInfos(void){
    printf("\n-------------------------\n");
    printf(" infos Humain\n");
    printf(" genre   = %s\n", this->genreTexte);
    printf(" nom     = %s\n", this->nom);
    printf(" prenom  = %s\n", this->nom);
    printf(" age     = %d\n", this->age);
    printf(" status  = %d\n", this->status);
    printf(" enfants = %d\n", nbEnfants);
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
        for (int i = 0 ; i < nbEnfants ; i++){
            if (this->enfants != nullptr){
                printf("     %d : %s\n", i, this->enfants[i]->nom);
            }
        }
    }
    printf("-------------------------\n\n");
}

void Humain::mariage(Humain *conjoint){
    this->conjoint = conjoint;
    this->status=MARIE;
    this->conjoint->conjoint=this;
    this->conjoint->status=MARIE;
    printf("declaration mariage de %s avec %s\n", this->getNomComplet(), conjoint->getNomComplet());
}

void Humain::descendance(){
    descendance(0);
}

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

int Humain::getId(void){
    return this->id;
}

int Humain::getNbEnfants(void){
    return this->nbEnfants;
}

int Humain::getAge(void){
    return this->age;
}

char *Humain::getNom(void){
    return this->nom;
}

char result[50];
char *Humain::getNomComplet(void){
    sprintf(result,"%s %s", this->prenom, this->nom);
    return result;
}

char *Humain::getPrenom(void){
    return this->prenom;
}

Humain *Humain::getConjoint(void){
    return this->conjoint;
    /*
    if (this->conjoint != NULL){
        sprintf(result,"%s %s", this->conjoint->prenom, this->conjoint->nom);
        return result;
    }
    return "";
    */
}

Humain *Humain::getPere(void){
    return this->pere;
    /*
    if (this->pere != NULL){
        sprintf(result,"%s %s", this->pere->prenom, this->pere->nom);
        return result;
    }
    return "";
    */
}

Humain *Humain::getMere(void){
    return this->mere;
    /*
    if (this->mere != NULL){
        sprintf(result,"%s %s", this->mere->prenom, this->mere->nom);
        return result;
    }
    return "";
    */
}

Humain *Humain::getEnfant(int index){
    return enfants[index];
    /*
    if (this->enfants[index] != NULL){
        return this->enfants[index]->prenom;
    }
    return "";
    */
}

char *Humain::getGenreTexte(void){
    return genreTexte;
}

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
            if (strcmp(this->nom,"dieu") !=0){
                this->addEnfant(ptr);
            }
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

void Humain::sauve(FILE *fic){
    printf("Sauvegarde de %s\n", this->nom);
    char ligne[500];
    char tmp[500];
    char thisPere[50], thisMere[50], thisConjoint[50];
    for (int i = 0 ; i < indexHumain ; i++){
        // nom; genre; age ; nbEnfants; status, conjoint(nom), pere(nom), mere(nom), liste enfants(nom), ...
        sprintf(tmp, "%d;%s;%d;%d;%d;%d", this->id, this->nom, this->genre, this->age, this->nbEnfants, this->status);
        //printf("tmp = %s\n", tmp);
        if (this->pere == NULL) strcpy(thisPere, "");
        else strcpy(thisPere, this->pere->nom);
        if (this->mere == NULL) strcpy(thisMere, "");
        else strcpy(thisMere, this->mere->nom);
        if (this->conjoint == NULL) strcpy(thisConjoint, "");
        else strcpy(thisConjoint, this->conjoint->nom);
        sprintf(ligne, "%s;%s;%s;%s;", tmp, thisConjoint, thisPere, thisMere);
        //printf("ligne = %s\n", ligne);
        //printf("sauvegarde de %d enfants\n", nbEnfants);
        for (int j = 0 ; j < nbEnfants ; j++){
            //printf("sauvegarde de l'enfant %d\n", j);
            sprintf(tmp,"%s;", this->enfants[j]->nom);
            strcat(ligne, tmp);
        }
        strcat(ligne, "\n");
    }
    printf("Ligne a sauvegarder : %s\n", ligne);
    fputs(ligne, fic);
    fflush(fic);
}

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
        }
    } else {
        // dieu genere des naissance s'il n'y plus assez d'humais
        if(getNbVivants() < 15){
            enfantDieu child = getRandomEnfant();
            printf("enfant genere automatiquement par dieu (%s %s,%d)\n", child.nom, child.prenom, child.genre);
            this->naissance(child.genre, child.nom, child.prenom);
        }
    }
}