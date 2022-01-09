//-----------------------------------
//
//      humain.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "humain.hpp"
#include "variables.hpp"
#include "tools.hpp"

Humain::Humain(int genre){
    char tmp[20];
    strcpy(tmp,"sans nom");
    Humain(genre, tmp, 0);
}

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

Humain::Humain(int genre, char *nom, int age){
    //printf("debut creation humain %s\n", nom);
    this->id=indexHumain;
    this->genre = genre;
    setGenreTexte();
    this->age = age;
    this->nbEnfants=0;
    strcpy(this->nom, nom);
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
                case 2: // genre
                    this->genre=atoi(tmp);
                    setGenreTexte();
                    printf("genre = %s\n", this->genreTexte);
                    break;
                case 3: // age
                    this->age=atoi(tmp);
                    printf("age = %d\n", this->age);
                    break;
                case 4: // nbEnfants
                    this->nbEnfants=0;
                    printf("nbEnfants = %d\n", this->nbEnfants);
                    break;
                case 5: // status
                    this->status=atoi(tmp);
                    printf("status = %d\n", this->status);
                    break;
                case 6: // conjoint
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
                case 7: // pere
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
                case 8: // mere
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
    printf(" genre = %s\n", this->genreTexte);
    printf(" nom   = %s\n", this->nom);
    printf(" age   = %d\n", this->age);
    printf(" status = %d\n", this->status);
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
    printf("declaration mariage de %s avec %s\n", this->nom, conjoint->nom);
}

void Humain::descendance(){
    descendance(0);
}

void Humain::descendance(int level){
    if (level == 0){
        printf("-----------------------------\n");
        printf(" debut descendance de %s ", this->nom);    
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
                printf("%s %s(%c)", tabs, this->enfants[i]->nom, this->enfants[i]->getGenreTexte()[0]);
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

char *Humain::getConjoint(void){
    if (this->conjoint != NULL){
        return this->conjoint->nom;
    }
    return "";
}

char *Humain::getPere(void){
    if (this->pere != NULL){
        return this->pere->nom;
    }
    return "";
}

char *Humain::getMere(void){
    if (this->mere != NULL){
        return this->mere->nom;
    }
    return "";
}

char *Humain::getEnfant(int index){
    if (this->enfants[index] != NULL){
        return this->enfants[index]->nom;
    }
    return "";
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
    printf("on ajoute l'enfant %s a %s\n", enfant->nom, this-> nom);
    if (this->nbEnfants < MAX_ENFANTS){
        this->enfants[this->nbEnfants]=enfant;
        this->nbEnfants++;
        //printf("%s a maintenant %d enfants\n", this->nom, this->nbEnfants);
        return true;
    }
    return false;
}

Humain *Humain::naissance(int genre, char *nom){
    //printf(" debut naissance de %s\n", nom);
    if (nbEnfants >= MAX_ENFANTS){
        //printf("nb enfants > %d\n", MAX_ENFANTS);
    } else {
        //printf(" max enfants pas atteint, on continue\n");
        //printf("on initialise l'enfant %d\n", nbEnfants);
        try{
            Humain *ptr;
            ptr = ::new Humain(genre, nom, 0);
            this->addEnfant(ptr);
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
            printf("impossible de creer un enfant\n");
        }
    }
    printf(" fin naissance de %s => KO\n", this->nom);
    return NULL;
}

void Humain::deces(void){
    printf("mort de %s\n", this->nom);
    this->status=MORT;
    if (this->conjoint != nullptr){
        printf("le conjoint %s devient veuf\n", this->conjoint->nom);
        this->conjoint->status = VEUF;
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
            if (this-> age >= ageRandom){
                printf("%s mort de vieillesse\n", this->nom);
                this->deces();
            }

            // test mort par accident 1/100 si age > agerandom
            ageRandom = getRandom(100);
            probabilite = getRandom(1000);
            if ((probabilite <= 100) && (this->age > ageRandom)){
                printf("%s mort par accident\n", this->nom);
                this-> deces();
            }

            // test candidats au mariage
            // recherche d'un homme celibataire ou veuf
            for (int i = 1 ; i < indexHumain ; i++){
                ptr = listeHumains[i];
                if ((ptr->getGenreTexte()[0] == 'H') && (ptr->getAge() >= 20)){
                    if ((ptr->getStatus() == 'C') || (ptr->getStatus() == 'V')){
                        // candidat potentiel au mariage
                        printf("%s est candidat au mariage\n", ptr->nom);
                        // recherche partenaire
                        for (int j = 0 ; j < indexHumain ; j++){
                            ptr1 = listeHumains[j];
                            if ((ptr1->getGenreTexte()[0] == 'F') && (ptr1->getAge() >= 20)){
                                if ((ptr1->getStatus() == 'C') || (ptr1->getStatus() == 'V')){
                                    // candidate potentielle au mariage
                                    printf("%s est candidate au mariage\n", ptr1->nom);
                                    int differenceAge = abs(ptr->getAge() - ptr1->getAge());
                                    if (abs(ptr->getAge() - ptr1->getAge()) > 5){
                                        printf("mariage impossible a cause de la difference d'age\n");
                                    } else {
                                        if ((rand() % 3) == 0){
                                            // 1 chance sur 3 qu'elle accepte
                                            ptr1->mariage(ptr);
                                        }else {
                                            printf("mariage refuse\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // test naissance
            for (int i = 0 ; i < indexHumain ; i++){
                ptr = listeHumains[i];
                if (ptr->getGenreTexte()[0] == 'H'){
                    if (ptr->conjoint != NULL){
                        ptr1 = ptr->conjoint;
                        if ((ptr->getAge() > 25) && (ptr1->getAge() > 25)){
                            if ((ptr->getAge() < 40) && (ptr1->getAge() > 40)){
                                int genreEnfant = rand()%1 +1;
                                switch (genreEnfant){
                                    case HOMME:
                                        printf("%s et %s ont un fils\n");
                                        break;
                                    case FEMME:
                                        printf("%s et %s ont une fille\n");
                                        break;
                                    default:
                                        printf("ERREUR : genre de l'enfant inconuu (%d)\n", genreEnfant);
                                        break;
                                }
                                printf("nom de l'enfant : ");
                                scanf("%s", saisie);
                                ptr->naissance(genreEnfant, saisie);
                            }
                        }
                    }
                }
            }
        }
    } else {
        // dieu genere des naissance s'il n'y a moins de 4 Humains
        if(indexHumain < 4){
            enfantDieu child = getRandomEnfant();
            printf("enfant genere automatiquement par dieu (%s,%d)\n", child.nom, child.genre);
            this->naissance(child.genre, child.nom);
        }
    }
}