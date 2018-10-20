#include <stdio.h>
#include <stdlib.h>
#include "savetab.h"
 
   int main()
   {
    Un_tab2d *tab;
    int nb_ligne=5;
    int nb_colonne=4;
    char *fic;
    fic="fichier.txt";
 
    tab=creer_tab2d(nb_ligne,nb_colonne);    
    ecrire_tab2d(tab,fic);
 
 
 
    return 0;
}
