#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>


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


liste *liste_new();
maillon *maillon_new(uint32_t v);
void maillon_free(maillon *m);
void liste_free(liste *l);
void liste_pushTete(liste *l, uint32_t v);
void liste_pushMTete(liste *l, maillon *r);
void liste_pushQueue(liste *l, uint32_t v);
void liste_pushMQueue(liste *l, maillon *m);
uint32_t liste_popTete(liste *l);
maillon* liste_popMTete(liste *l);
void liste_affiche(liste *l);
_Bool liste_isEmpty(liste *l);


