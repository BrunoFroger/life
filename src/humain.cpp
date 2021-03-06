//-----------------------------------
//
//      humain.cpp
//
//-----------------------------------

#include <string>
#include <iostream>

#include "../inc/humain.hpp"

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
Humain::Humain(Humain *pere, int genre, char *nom, char *prenom, int nbJours){
    this->id=nbHumains;
    this->genre = genre;
    setGenreTexte();
    this->nbJours = nbJours;
    this->nbEnfants=0;
    strcpy(this->nom, nom);
    strcpy(this->prenom, prenom);
    this->status=CELIBATAIRE;
    this->pere=pere;
    if (pere != NULL){
        this->mere = pere->conjoint;
        pere->addEnfant(this);
        if (this->mere != NULL){
            mere->addEnfant(this);
        }
    } else {
        this->mere=NULL;
    }
    this->conjoint=NULL;
    for (int i = 0 ; i < MAX_ENFANTS ; i++){
        this->enfants[i]=NULL;
    }
    listeHumains[nbHumains] = this;
    nbHumains++;
    listeHumains[nbHumains] = NULL;
    //displayInfos();
    //if (debugHumain) printf("fin creation humain %s\n", nom);
    this->employeur=NULL;
    this->compteBancaire = new CompteBancaire(this->getNomComplet());
    this->compteBancaire->credite(100);
    this->commandeEnCours=false;
    this->pointsDeVie = POINTS_DE_VIE_INITIAL;
    for (int i = 0 ; i < MAX_ACHAT_CLIENT ; i++){
        mesProduits[i] = NULL;
    }
    if (debugHumain) printf("Humain::Humain => humain cree : %s en position %d\n", this->getNomComplet(), nbHumains);
}

//-------------------------------------------
//
//          Humain::Humain
//
//-------------------------------------------
Humain::Humain(char *datas){
    //if (debugHumain) printf("Humain::Humain => initialisation partielle d'un humain a partir d'une ligne <%s>\n", datas);
    char tmp[50];
    int id, genre, age;
    char prenom[50], nom [50];
    tmp[0] = '\0';
    sscanf(datas, "humain %d %s %s %d %d", &id, prenom, nom, &genre, &age);
    //if (debugHumain) printf("Humain::Humain => donn??es r??cupereees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d\n", id, prenom, nom, genre, age);
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
    //if (debugHumain) printf("Humain::restore => restauration des donnees d'un humain a partir d'une ligne <%s>", datas);
    char tmp[50];
    Humain *ptr;
    tmp[0] = '\0';
    char datas_prenom[50], datas_nom[50];
    int datas_id, datas_genre, datas_age, datas_status, datas_pointsdevie, datas_idPere, datas_idMere, datas_idConjoint, datas_nbEnfants;

    sscanf(datas, "humain %d %s %s %d %d %d %d %d %d %d %d", 
            &datas_id, datas_prenom, datas_nom, &datas_genre, &datas_age, &datas_nbEnfants, 
            &datas_status, &datas_pointsdevie, &datas_idConjoint, &datas_idPere, &datas_idMere);
    //if (debugHumain) printf("Humain::restore => donn??es r??cupereees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d, status=%d, idConjoint=%d, idPere=%d, idMere=%d, nbEnfants=%d\n", 
    //        datas_id, datas_prenom, datas_nom, datas_genre, datas_age, datas_status, datas_idConjoint, datas_idPere, datas_idMere, datas_nbEnfants);
    this->nbEnfants = datas_nbEnfants;
    this->status = datas_status;
    this->id = datas_id;
    //if (debugHumain) printf("Humain::restore => donn??es enregistrees : id=%d, prenom=%s, nom=%s, genre=%d, age=%d, status=%d, nbEnfants=%d\n", 
    //        this->id, this->prenom, this->nom, this->genre, this->age, this->status, this->nbEnfants);
    for (int i = 0 ; i < nbHumains ; i++){
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
    //if (debugHumain) printf("Humain::restore =>  fin\n");

}

//-------------------------------------------
//
//          Humain::~Humain
//
//-------------------------------------------
Humain::~Humain(){
    // rien a faire pour le moment
    nbHumains--;
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
//          Humain::setEmployeur
//
//-------------------------------------------
void Humain::setEmployeur(Entreprise *ptrEntreprise){
    this->employeur = ptrEntreprise;
    if (ptrEntreprise == NULL){
        if (debugHumain) printf("Humain::setEmployeur => %s a ??t?? supprime de son entreprise\n", this->getNomComplet());
    } else {
        if (debugHumain) printf("Humain::setEmployeur => %s a ??t?? embauch?? par %s\n", this->getNomComplet(), ptrEntreprise->getNom());
    }
}

//-------------------------------------------
//
//          Humain::displayInfos
//
//-------------------------------------------
void Humain::displayInfos(void){
    debugHumain = true;
    if (debugHumain) printf("\n-------------------------\n");
    if (debugHumain) printf(" infos Humain\n");
    if (debugHumain) printf(" genre   = %s\n", this->genreTexte);
    if (debugHumain) printf(" nom     = %s\n", this->nom);
    if (debugHumain) printf(" prenom  = %s\n", this->prenom);
    if (debugHumain) printf(" age     = %d\n", this->age);
    if (debugHumain) printf(" status  = %d\n", this->status);
    if (debugHumain) printf(" enfants = %d\n", this->nbEnfants);
    if (this->status == MARIE){
       if (debugHumain) printf(" conjoint = %s\n", this->conjoint->nom);
    }
    if (this->pere != NULL){
        if (debugHumain) printf(" pere = %s\n", this->pere->nom);
    }
    if (this->mere != NULL){
        if (debugHumain) printf(" mere = %s\n", this->mere->nom);
    }
    if (this->nbEnfants != 0){
        if (debugHumain) printf(" enfants \n");
        for (int i = 0 ; i < this->nbEnfants ; i++){
            if (this->enfants[i] != NULL){
                if (debugHumain) printf("     %d : %s\n", i, this->enfants[i]->nom);
            }
        }
    }
    if (debugHumain) printf("-------------------------\n\n");
}

//-------------------------------------------
//
//          Humain::mariage
//
//-------------------------------------------
void Humain::mariage(Humain *conjoint){
    char homme[50];
    strcpy(homme,this->getNomComplet());
    char femme[50];
    strcpy(femme, conjoint->getNomComplet());
    this->conjoint = conjoint;
    this->status=MARIE;
    this->conjoint->conjoint=this;
    this->conjoint->status=MARIE;
    if (debugHumain) printf("Humain::mariage => declaration mariage de %s avec %s\n", homme, femme);
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
        if (debugHumain) printf("-----------------------------\n");
        if (debugHumain) printf(" debut descendance de %s (%c-%d)", this->getNomComplet(), this->getGenreTexte()[0], this->getAge());    
        if (this->conjoint != NULL){
            if (debugHumain) printf(" avec %s (%c-%d)\n", this->conjoint->getNomComplet(), this->conjoint->getGenreTexte()[0], this->conjoint->getAge());
        } else {
            printf("\n");
        }
    }
    char tabs[100];
    tabs[0]='\0';
    for (int i = 0 ; i < level * 4 ; i++){
        tabs[i]=' ';
        tabs[i+1]='\0';
    }
    if (this->nbEnfants != 0){
        for (int i = 0 ; i < nbEnfants ; i++){
            if (this->enfants[i] != NULL){
                if (debugHumain) printf("%s %s(%c-%d)", tabs, this->enfants[i]->getNomComplet(), this->enfants[i]->getGenreTexte()[0], this->enfants[i]->getAge());
                if (this->enfants[i]->conjoint != NULL){
                    if (debugHumain) printf(" en couple avec %s(%c-%d)", this->enfants[i]->conjoint->getNomComplet(), this->enfants[i]->conjoint->getGenreTexte()[0], this->enfants[i]->getAge());
                }
                if (debugHumain) printf("\n");
                this->enfants[i]->descendance(level + 1);            }
        }
    } else {
        if (debugHumain) printf("%s pas d'enfants\n", tabs);
    }
    if (level == 0){
        if (debugHumain) printf(" fin descendance de %s\n", this->getNomComplet());
        if (debugHumain) printf("-----------------------------\n");
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
//          Humain::getNbJours
//
//-------------------------------------------
int Humain::getNbJours(void){
    return this->nbJours;
}


//-------------------------------------------
//
//          Humain::getAge
//
//-------------------------------------------
int Humain::getAge(void){
    return this->nbJours / 365;
}

//-------------------------------------------
//
//          Humain::getEmployeur
//
//-------------------------------------------
Entreprise *Humain::getEmployeur(void){
    if (this->employeur != NULL){
        return this->employeur;
    }
    return NULL;
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
        //if (debugHumain) printf("on ajoute l'enfant %s a %s\n", enfant->nom, this-> nom);
        this->enfants[this->nbEnfants]=enfant;
        this->nbEnfants++;
        //if (debugHumain) printf("%s a maintenant %d enfants\n", this->nom, this->nbEnfants);
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
    if (debugHumain) printf("Humain::naissance => %s donne naissance ?? %s\n", this->getNomComplet(), prenom);
    if (this->nbEnfants >= MAX_ENFANTS){
        if (strcmp(this->getNom(), "dieu") != 0){
            if (debugHumain) printf("ERREUR : %s a atteint le nombre maximal d'enfants (%d)\n", this->getNomComplet(), MAX_ENFANTS);
            return NULL;
        }
    } 
    //if (debugHumain) printf(" max enfants pas atteint, on continue\n");
    //if (debugHumain) printf("on initialise l'enfant %d\n", nbEnfants);
    try{
        Humain *ptr;
        ptr = new Humain(0, genre, nom, prenom, 0);
        this->addEnfant(ptr);

        if (this->conjoint != NULL){
            this->conjoint->addEnfant(ptr);
        }
        //if (debugHumain) printf("initialisation des parents\n");
        if (this->genre == HOMME){
            //printf("le pere declare\n");
            ptr->pere=this;
            ptr->mere=this->conjoint;
        } else {
            //if (debugHumain) printf("la mere declare (%s)\n", this->nom);
            ptr->pere=this->conjoint;
            ptr->mere=this;
        }
        if (ptr->pere != NULL){
            //if (debugHumain) printf("pere : %s\n", ptr->pere->nom);
        }
        if (ptr->mere != NULL){
            //if (debugHumain) printf("mere : %s\n", ptr->mere->nom);
        }
        //ptr->displayInfos();
        //if (debugHumain) printf(" declaration de naissance de %s => OK\n", nom);
        return ptr;
    } catch(...){
        printf("ERREUR => impossible de creer un enfant\n");
    }
    if (debugHumain) printf("Humain::naissance => naissance de %s=> KO\n", this->getNomComplet());
    return NULL;
}

//-------------------------------------------
//
//          Humain::deces
//
//-------------------------------------------
void Humain::deces(void){
    //debugHumain = true;
    if (debugHumain) printf("Humain::deces => mort de %s ?? l'age de %d\n", this->getNomComplet(), this->age);
    if (this->conjoint != NULL){
        //printf("le conjoint %s devient veuf\n", this->conjoint->nom);
        if (this->conjoint->status != MORT){
            this->conjoint->status = VEUF;
        }
    }
    if (debugHumain) printf("Humain::deces => check si salarie\n");
    if (this->estSalarie()){
        this->employeur->supprimeSalarie(this);
        if (debugHumain) printf("Humain::deces => %s supprim?? de son entreprise\n", getNomComplet());
    }
    if (debugHumain) printf("Humain::deces => check si commandes en cours\n");
    Commande *ptrCde;
    // suppression des commandes en cours pour cet humain
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        ptrCde = listeCommandes[i];
        if (ptrCde != NULL){
            if ( ptrCde->getClient() == this){
                if (debugHumain) printf("Humain::deces => commande %d supprim?? \n", ptrCde->getNumero());
                listeCommandes[i] = NULL;
                delete ptrCde;
                nbCommandes--;
                break;
            }
        }
    }
    this->status=MORT;
    if (debugHumain) printf("Humain::deces => fin\n");
    //debugHumain = false;
}

//-------------------------------------------
//
//          Humain::testMariage
//
//-------------------------------------------
void Humain::testMariage(void){
    //if (debugHumain) printf("Humain::testMariage => debut\n");
    // test candidats au mariage
    // recherche d'un homme celibataire ou veuf
    Humain *ptrHumain = NULL;
    if ((this->getGenreTexte()[0] == 'H') && (this->getAge() >= AGE_DEBUT_MARIAGE)){
        if ((this->getStatus() == 'C') || (this->getStatus() == 'V')){
            // candidat potentiel au mariage
            //if (debugHumain) printf("%s est candidat au mariage\n", this->nom);
            // recherche partenaire
            for (int j = 1 ; j < nbHumains ; j++){
                ptrHumain = listeHumains[j];
                if ((ptrHumain->getGenreTexte()[0] == 'F') && (ptrHumain->getAge() >= AGE_DEBUT_MARIAGE)){
                    if ((ptrHumain->getStatus() == 'C') || (ptrHumain->getStatus() == 'V')){
                        // candidate potentielle au mariage
                        //if (debugHumain) printf("%s est candidate au mariage\n", ptr1->nom);
                        int differenceAge = abs(this->getAge() - ptrHumain->getAge());
                        if (differenceAge > DIFF_AGE_MARIAGE){
                            //if (debugHumain) printf("mariage impossible a cause de la difference d'age\n");
                        } else {
                            if ((rand() % PROBA_MARIAGE) == 0){
                                // 1 chance sur n qu'elle accepte
                                ptrHumain->mariage(this);
                                return;
                            }else {
                                //if (debugHumain) printf("mariage refuse\n");
                            }
                        }
                    }
                }
            }
        }
    }
}

//-------------------------------------------
//
//          Humain::testNaissance
//
//-------------------------------------------
void Humain::testNaissance(void){
    //if (debugHumain) printf("Humain::testNaissance => debut\n");
    // test generation d'une naissance
    Humain *ptrHumain = NULL;
    if (this->getGenreTexte()[0] == 'H'){
        if (this->conjoint != NULL){
            ptrHumain = this->conjoint;
            //if (debugHumain) printf("teste compatibilite naissance entre %s et %s\n", this->getNomComplet(), ptr1->getNomComplet());
            if ((this->getAge() > AGE_DEBUT_NAISSANCE) && (ptrHumain->getAge() > AGE_DEBUT_NAISSANCE)){
                //if (debugHumain) printf("Les deux parents ont + 25 ans\n");
                if ((this->getAge() < AGE_FIN_NAISSANCE) && (ptrHumain->getAge() < AGE_FIN_NAISSANCE)){
                    //if (debugHumain) printf("Les deux parents ont - 40 ans\n");
                    //if (debugHumain) printf("%s et %s sont les futurs parents\n", this->getNomComplet(), ptr1->getNomComplet());
                    char newPrenom[25];
                    int genreEnfant = getRandomGenre();
                    switch (genreEnfant){
                        case HOMME:
                            //if (debugHumain) printf("%s et %s ont un fils\n", this->getNomComplet(), ptr1->getNomComplet());
                            strcpy(newPrenom,getPrenomMasculin());
                            break;
                        case FEMME:
                            //if (debugHumain) printf("%s et %s ont une fille\n", this->getNomComplet(), ptr1->getNomComplet());
                            strcpy(newPrenom,getPrenomFeminin());
                            break;
                        default:
                            printf("ERREUR : genre de l'enfant inconuu (%d)\n", genreEnfant);
                            break;
                    }
                    //if (debugHumain) printf("prenom de l'enfant : ");
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

//-------------------------------------------
//
//          Humain::achats
//
//-------------------------------------------
void Humain::achats(void){
    //if (debugHumain) printf("Humain::achats => debut\n");
    // genere des cachats en fonction des ressources et des besoins
    produitClient *ptrProduitClient;

    // on supprime les produits dont la date de validite est d??pass??e
    for (int i = 0 ; i < MAX_ACHAT_CLIENT ; i++){
         ptrProduitClient = this->mesProduits[i];
         if (ptrProduitClient != NULL){
            int ageProduit = age - ptrProduitClient->dateAchat;
            if (ageProduit > ptrProduitClient->duree){
                if (debugHumain) printf("Humain::achats => produit p??rim?? -> on le supprime\n");
                delete ptrProduitClient;
                this->mesProduits[i] = NULL;
            }
         }
    }

    // etablir liste des besoin de cet humain en fonction de ses ressources
    //int budget = getSoldeBancaire();

    // declenchements d'achats de premiere necessite
    setListeProduitEnManque();
}

//-------------------------------------------
//
//          Humain::setListeProduitEnManque
//
//-------------------------------------------
void Humain::setListeProduitEnManque(){
    //if (debugHumain) printf("Humain::setListeProduitEnManque => todo\n");

}

//-------------------------------------------
//
//          Humain::sauve
//
//-------------------------------------------
void Humain::sauve(FILE *fic){
    //if (debugHumain) printf("Humain::sauve => Sauvegarde de %s\n", this->getNomComplet());
    char ligne[500];
    char tmp[500];
    int thisPere, thisMere, thisConjoint;
    if (this->pere == NULL) thisPere = -1;
    else thisPere = this->pere->getId();
    if (this->mere == NULL) thisMere = -1;
    else thisMere = this->mere->getId();
    if (this->conjoint == NULL) thisConjoint = -1;
    else thisConjoint = this->conjoint->getId();
    // nom; genre; age ; nbEnfants; status, conjoint(nom), pere(nom), mere(nom), liste enfants(nom), ...
    sprintf(tmp, "humain %d %s %s %d %d %d %d %d", this->id, this->prenom, this->nom, this->genre, 
            this->age, this->nbEnfants, this->status, this->pointsDeVie);
    //if (debugHumain) printf("tmp = %s\n", tmp);
    sprintf(ligne, "%s %d %d %d ", tmp, thisConjoint, thisPere, thisMere);
    //if (debugHumain) printf("ligne = %s\n", ligne);
    //if (debugHumain) printf("sauvegarde de %d enfants\n", nbEnfants);
    for (int j = 0 ; j < nbEnfants ; j++){
        //printf("sauvegarde de l'enfant %d\n", j);
        sprintf(tmp,"%d ", this->enfants[j]->getId());
        strcat(ligne, tmp);
    }
    strcat(ligne, "\n");
    //if (debugHumain) printf("Humain::sauve => Ligne a sauvegarder : %s\n", ligne);
    fputs(ligne, fic);
    fflush(fic);
}

//-------------------------------------------
//
//          Humain::sauveJson
//
//-------------------------------------------
void Humain::sauveJson(FILE *fic){
    //if (debugHumain) printf("Humain::sauveJson => Sauvegarde de %s\n", this->getNomComplet());
    int thisPere, thisMere, thisConjoint;
    if (this->pere == NULL) thisPere = -1;
    else thisPere = this->pere->getId();
    if (this->mere == NULL) thisMere = -1;
    else thisMere = this->mere->getId();
    if (this->conjoint == NULL) thisConjoint = -1;
    else thisConjoint = this->conjoint->getId();
    fprintf(fic, "      { \"id\": %d, ", this->id);
    fprintf(fic, "\"prenom\": \"%s\" ,", this->prenom);
    fprintf(fic, "\"nom\": \"%s\" ,", this->nom);
    fprintf(fic, "\"genre\": %d ,", this->genre);
    fprintf(fic, "\"age\": %d ,", this->age);
    fprintf(fic, "\"nbEnfants\": %d ,", this->nbEnfants);
    fprintf(fic, "\"status\": %d ,", this->status);
    fprintf(fic, "\"pointsDeVie\": %d ,", this->pointsDeVie);
    fprintf(fic, "\"idConjoint\": %d ,", thisConjoint);
    fprintf(fic, "\"idPere\": %d ,", thisPere);
    fprintf(fic, "\"idMere\": %d ,", thisMere);
    fprintf(fic, "\"enfants\": [ ");
    for (int j = 0 ; j < nbEnfants ; j++){
        //if (debugHumain) printf("sauvegarde de l'enfant %d\n", j);
        fprintf(fic, "      {\"id\": %d},", this->enfants[j]->getId());
    }
    fprintf(fic, " ]");
    fprintf(fic, " },");
    fprintf(fic, "\n");
    fflush(fic);
}

//-------------------------------------------
//
//          Humain::vieillir
//
//-------------------------------------------
void Humain::vieillir(void){
    //if (debugHumain) printf("Humain::vieillir => debut pour\n");
    if (strcmp(this->nom, "dieu") != 0){ // dieu ne vieilli pas => immortel
        if (this->status != MORT){ // on ne fait pas vieillir les morts
            this->age++;
            this->pointsDeVie--;
            //if (debugHumain) printf("Humain::vieillir => age %s = %d\n", this->getNomComplet(), age);
            int ageRandom;
            int probabilite;

            // test mort de vieillesse 60 + random(40)
            ageRandom = 60 + getRandom(40);
            //if (debugHumain) printf("age de deces pour %s : %d\n",this->nom, ageRandom);
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
        }
    } else {
        // dieu genere des naissance s'il n'y pas assez d'humains
        if(getNbVivants() < 15){
            enfantDieu child = getRandomEnfant();
            if (debugHumain) printf("Humain::vieillir => enfant genere automatiquement par dieu (%s %s,%d)\n", child.nom, child.prenom, child.genre);
            this->naissance(child.genre, child.nom, child.prenom);
            //printf("fin enfant genere automatiquement par dieu \n");
        }
    }
    //if (debugHumain) printf("Humain::vieillir => fin\n");
}

//-------------------------------------------
//
//          Humain::credite
//
//-------------------------------------------
bool Humain::credite(int montant){
    if (montant < 0){
        printf("ERREUR : credit de somme negative interdit\n");
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

//-------------------------------------------
//
//          Humain::commande
//
//-------------------------------------------
void Humain::commande(Produit *produit, int quantite){
    debugHumain=true;
    if (debugHumain) printf("Humain::commande(1) => %s commande produit = %s, quantite = %d\n", getNomComplet(), produit->getNom(), quantite);
    Commande *ptrCde;
    if (produit->getPrix() > getSoldeBancaire()){
        if (debugHumain) printf("Humain::commande => ERREUR : commande impossble (budget insuffisant\n");
        return;
    }
    ptrCde = new Commande(produit, quantite, this);
    if (ptrCde->getStatus() == COMMANDE_IMPOSSIBLE){
        delete ptrCde;
    }
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i] == NULL){
            debugHumain=true;
            break;
        }
    }
    debugHumain=false;
}

//-------------------------------------------
//
//          Humain::gereCommandeEnCours
//
//-------------------------------------------
void Humain::gereCommandesEnCours(){
    //if (debugHumain) if (debugHumain) printf("Humain::gereCommandeEnCours => debut \n");
    Commande *ptrCde;
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        ptrCde = listeCommandes[i];
        if (ptrCde != NULL){
            if (ptrCde->getClient() == this){
                switch (ptrCde->getStatus()){
                    case COMMANDE_DISPONIBLE:
                        if (debugHumain) printf("Humain::gereCommandeEnCours => %s, status = COMMANDE DISPONIBLE %d\n", getNomComplet(), ptrCde->getNumero());
                        // recuperation du nombre de points de vie du produit 
                        if (this->getSoldeBancaire() > ptrCde->getProduit()->getPrix()){
                            this->debite(ptrCde->getProduit()->getPrix());
                            ptrCde->changeStatus(COMMANDE_LIVREE);
                            pointsDeVie += ptrCde->getProduit()->getNbPointsDeVie();
                        } else {
                            if (debugHumain) printf("Humain::gereCommandeEnCours => %s, budget insuffisant pour payer la commande %d\n", getNomComplet(), ptrCde->getNumero());
                        }
                        break;
                    case COMMANDE_IMPOSSIBLE:
                        if (debugHumain) printf("Humain::gereCommandeEnCours => %s, status = COMMANDE IMPOSSIBLE \n", getNomComplet());
                        listeCommandes[i] = NULL;
                        delete ptrCde;
                        break;
                    case COMMANDE_SOLDEE:
                        if (debugHumain) printf("Humain::gereCommandeEnCours => %s, status = COMMANDE SOLDEE (%d) \n", getNomComplet(), ptrCde->getNumero());
                        listeCommandes[i] = NULL;
                        delete ptrCde;
                        break;
                    default:
                        // rien a faire
                        break;
                }
            }
        }
    }
}

//-------------------------------------------
//
//          Humain::boucleTraitement
//
//-------------------------------------------
void Humain::boucleTraitement(void){
    debugHumain=true;
    //if (debugHumain) printf("Humain::boucleTraitement => debut pour %s\n", getNomComplet());
    this->vieillir();
    this->testMariage();
    this->testNaissance();
    this->achats();
    this->gereCommandesEnCours();
    //if (debugHumain) printf("Humain::boucleTraitement => fin\n");
}

//-------------------------------------------
//
//          Humain::getNumComp
//
//-------------------------------------------
int Humain::getPointsDeVie(void){
    return this->pointsDeVie;
}
