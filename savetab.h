#ifndef SAVETAB_H
#define SAVETAB_H


typedef struct 
    {
    unsigned int nb_colonnes;
    unsigned int nb_lignes;
    int *plan;    //pointeur sur le tableau de nb_lignes * nb_colonnes            
    } Un_tab2d;


Un_tab2d * creer_tab2d(unsigned int nb_lignes, unsigned int nb_colonnes)
{

        Un_tab2d *tab=malloc(sizeof(Un_tab2d));

        tab->plan=malloc(nb_colonnes*nb_lignes*(sizeof(int)));
        tab->nb_colonnes=nb_colonnes;
        tab->nb_lignes=nb_lignes;

        return tab;
}


void ecrire_tab2d(Un_tab2d *tab, char *nom_fichier)
{

        FILE *fic;
        int nb_li,nb_co;
        int *t = tab -> plan;
        int i,j;

        fic=fopen(nom_fichier,"w");
        if (fic==NULL)
	{
           fprintf(stderr,"Impossible d'ouvrir le fichier");
           exit (1);
        }
        nb_li=tab->nb_lignes;
        nb_co=tab->nb_colonnes;

        fprintf(fic,"%d\n",nb_li);
        fprintf(fic,"%d\n",nb_co);

        for(i=0;i<nb_li;i++)
	{
           for(j=0;i<nb_co;j++) {
                   fprintf(fic,"%d",t[i*nb_co+j]);
          }
        fprintf(fic,"\n");
        }
        fclose(fic);
}


#endif
