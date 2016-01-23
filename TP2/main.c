#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct maillon
{
    uint32_t value;
    struct maillon *next;
} maillon;
typedef struct liste
{
    uint32_t taille;
    maillon *tete;
    maillon *queue;
} liste;

liste* liste_new()
{
    liste* l=(liste*)calloc(1,sizeof(liste));

    return l;
}
maillon* Maillon_new(uint32_t v)
{
    maillon* m=(maillon*)malloc(sizeof(maillon));
    m->value=v;
    m->next=NULL;
}
void maillon_free(maillon * m)
{
    if(m!=NULL)
        free(m);
}
void Liste_free(liste *l)
{
    if(l!=NULL)
    {
        while(l->tete!=NULL)
        {
            maillon* mSuivant=l->tete->next;
            free(l->tete);
            l->tete=mSuivant;
        }

    }
}
void Liste_pushTete(liste *l, uint32_t v)
{
    maillon* m=Maillon_new(v);
    m->next=l->tete;
    l->tete=m;
    if(l->queue==NULL)
        l->queue=l->tete;

    l->taille++;
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
