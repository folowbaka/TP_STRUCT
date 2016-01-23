//
//  myliste.c
//  INFO1_Struct_TP1
//
//  Created by Chaussard on 04/12/2015.
//  Copyright (c) 2015 Chaussard. All rights reserved.
//

#include "myliste.h"


liste *liste_new()
{
    return calloc(1, sizeof(liste));
}



maillon *maillon_new(uint32_t v)
{
    maillon *r = malloc(sizeof(maillon));
    if (r==NULL) return NULL;
    r->value = v;
    r->next=NULL;
    return r;
}



void maillon_free(maillon *m)
{
    if (m!=NULL) free(m);
}



void liste_free(liste *l)
{
    maillon *m;
    if (l != NULL)
    {
        m=l->tete;
        while(m != NULL)
        {
            l->tete = l->tete->next;
            maillon_free(m);
            m = l->tete;
        }
        free(l);
    }
}


void liste_pushTete(liste *l, uint32_t v)
{
    liste_pushMTete(l, maillon_new(v));
}


void liste_pushMTete(liste *l, maillon *r)
{
    assert(l!=NULL);
    assert(r!=NULL);
    
    r->next = l->tete;
    l->tete = r;
    if(l->queue == NULL)
    {
        l->queue = l->tete;
    }
    l->taille += 1;
}


void liste_pushQueue(liste *l, uint32_t v)
{
    liste_pushMQueue(l, maillon_new(v));
}


void liste_pushMQueue(liste *l, maillon *m)
{
    assert(l != NULL);
    assert(m != NULL);
    
    if (l->queue != NULL)
    {
        l->queue->next = m;
    }
    else
    {
        l->tete = m;
    }
    l->queue = m;
    l->taille += 1;
}


uint32_t liste_popTete(liste *l)
{
    uint32_t i;
    maillon *m = liste_popMTete(l);
    
    assert(l!=NULL && l->taille > 0);
    
    i=m->value;
    maillon_free(m);
    
    return i;
}


maillon* liste_popMTete(liste *l)
{
    maillon *m;
    
    assert(l!=NULL && l->taille > 0);
    
    m=l->tete;
    l->tete = l->tete->next;
    
    if(l->tete == NULL)
        l->queue = NULL;
    
    l->taille -= 1;
    return m;
}


void liste_affiche(liste *l)
{
    assert(l != NULL);
    maillon *t = l->tete;
    while(t != NULL)
    {
        printf("%u ", t->value);
        t = t->next;
    }
    printf("\n");
}


_Bool liste_isEmpty(liste *l)
{
    assert(l!=NULL);
    return (l->taille == 0);
}

