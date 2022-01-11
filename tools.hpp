//-----------------------------------
//
//      tools.hpp
//
//-----------------------------------

#ifndef __TOOLS__
#define __TOOLS__

    typedef struct{
        char nom[20];
        char prenom[20];
        int genre;
    }enfantDieu;

    extern int getRandom(int range);
    extern enfantDieu getRandomEnfant(void);
    extern void afficheListeHumains(void);
    extern char *getPrenomMasculin(void);
    extern char *getPrenomFeminin(void);
    extern int getRandomGenre();

#endif