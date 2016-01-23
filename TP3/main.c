#include <stdio.h>
#include <stdlib.h>
#include "myliste.h"
typedef struct myarraylist
{
    uint64_t capacite;
    maillon *tab_maillon;
    liste *utilises;
    liste *libres;
}myarraylist;
void arraylist_new(uint64_t taille)
{
    assert(taille>0);
    myarraylist* ma=(myarraylist*)malloc(sizeof(myarraylist));
    ma->capacite=taille;
    ma->tab_maillon=malloc(ma->capacite*sizeof(maillon));
    ma->utilises=liste_new();
    ma->libres=liste_new();
    uint64_t i=0;
    for(i=0;i<ma->capacite;i++)
    {
        liste_pushMTete(ma->libres,&ma->tab_maillon[i]);
    }
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
