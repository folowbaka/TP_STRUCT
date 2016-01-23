#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#define Value(g) (g.type==ULONG ? (g.data.u) : (Value2(g)) )
#define Value2(g) (g.type==DOUBLE ? (g.data.d) : (g.data.i) )

#define TAILLE_CHAINE 30

typedef enum{DOUBLE, LONG, ULONG} TypeGenerique;

typedef struct generique
{
    TypeGenerique type;
    union
    {
        double d;
        uint64_t u;
        int64_t i;
    }data;
}generique;
typedef struct
{
    generique **data;
    uint64_t hauteur;
    uint64_t largeur;
} matriceg;
generique creerGenerique(char* chaine)
{
    generique g;
    uint32_t cpt_points, cpt_neg, cpt_nondigit;
    uint32_t i;
    char *pc;
    cpt_points=0;
    cpt_neg=0;
    cpt_nondigit=0;
    //On va compter le nombre de points decimaux et de symboles "-" dans le chaine... On va aussi vérifier que la chaine est correcte. Si ce n'est pas le cas, on quitte !
    for(i=0; chaine[i]!='\0'; i+=1)
    {
        if (chaine[i]=='.') //Le caractère est-il un point ?
            cpt_points+=1;
        else if (chaine[i]=='-') //Le caractère est-il un symbole négatif ?
            cpt_neg+=1;
        else if ((chaine[i]<'0' || chaine[i]>'9') && chaine[i]!='\n')
            cpt_nondigit+=1;

    }

    if (cpt_points > 1 || cpt_neg > 1 || (cpt_neg==1 && chaine[0]!='-') || cpt_nondigit > 0)
    {
        fprintf(stderr, "Erreur, la chaine entrée n'a pas le bon format\n");
        assert(0); //Il faudrait éviter ca... Mais que retourner avec cette fonction ?
    } //Arrive a ce point, on a le bon format ! On peut faire de la conversion
    else if(cpt_points == 1)
    {
        //L'utilisateur a entré un double, on le convertit
        g.data.d=strtod(chaine, &pc);
        g.type=DOUBLE;
    }
    else if(cpt_neg == 0)
    {
        //L'utilisateur a entre un entier non signé
        g.data.u= strtoul(chaine, &pc, 10);
        g.type=ULONG;
    }
    else
    {
        //L'utilisateur a entre un entier signé
        g.data.i = strtol(chaine, &pc, 10);
        g.type=LONG;
    }
    return g;


}
generique demanderValeur()
{
    char chaine[TAILLE_CHAINE];
    char c;

    //On recupere la chaine entree par l'utilisateur
    fgets(chaine, sizeof(chaine), stdin);

    //On doit faire un petit nettoyage après au cas où l'utilisateur ait entré plus de caractères que nécessaire (plus de TAILLE_CHAINE)...
    if(strchr(chaine, '\n') == NULL) //Ah, pas de retour a la ligne dans chaine : l'utilisateur a tapé trop de caractères
    {
        c = fgetc(stdin);
        while (c!='\n' && c!=EOF)
            c = fgetc(stdin);
    }
    //Ok, on a correctement vidé l'entrée standard
    return creerGenerique(chaine);

}

void afficheGenerique(generique g)
{
    switch (g.type)
    {
        case DOUBLE:
        printf("%lf (double)\n",g.data.d);
        break;
        case LONG:
        printf("%lld (Long)\n",g.data.i);
        break;
        case ULONG:
        printf("%llu (Ulong)\n",g.data.u);
    }
}
generique add(generique g1, generique g2)
{
    generique r;

    if(g1.type == DOUBLE || g2.type == DOUBLE)
    {
        r.type = DOUBLE;

        if(g1.type == DOUBLE) r.data.d=g1.data.d; else if(g1.type == ULONG) r.data.d=g1.data.u; else r.data.d=g1.data.i;
        if(g2.type == DOUBLE) r.data.d+=g2.data.d; else if(g2.type == ULONG) r.data.d+=g2.data.u; else r.data.d+=g2.data.i;

    }

    else if(g1.type == LONG || g2.type == LONG)
    {
        r.type = LONG;

        if(g1.type == ULONG) r.data.i=g1.data.u; else r.data.i=g1.data.i;
        if(g2.type == ULONG) r.data.i+=g2.data.u; else r.data.i+=g2.data.i;
    }

    else
    {
        r.type = ULONG;
        r.data.u = g1.data.u + g2.data.u;
    }

    return r;
}
generique multGenerique(generique g1, generique g2)
{
    generique r;

    if(g1.type == DOUBLE || g2.type == DOUBLE)
    {
        r.type = DOUBLE;
        r.data.d =  Value(g2);
        r.data.d *= Value(g1);
    }

    else if(g1.type == LONG || g2.type == LONG)
    {
        r.type = LONG;
        r.data.i = Value(g2);
        r.data.i *= Value(g1);
    }

    else
    {
        r.type = ULONG;
        r.data.u = g1.data.u * g2.data.u;
    }

    return r;
}
generique soustraire(generique g1, generique g2)
{
    generique r =add(g1,multGenerique(creerGenerique("-1"),g2));


    return r;
}
generique diviser(generique g1,generique g2)
{
    generique r;
    r.type=DOUBLE;
    r.data.d=g1.data.d/g2.data.d;

    return r;
}
void allocationGenerique2d(int largeur,int hauteur,generique ***r)
{
        *r=malloc(largeur*sizeof(generique*));
        int i=0;

            for(i=0;i<largeur;i++)
            {
                (*r)[i]=malloc(hauteur*sizeof(generique));
            }
}
matriceg creerMatriceGenerique( uint64_t largeur,uint64_t hauteur)
{
    matriceg m;
    m.hauteur=hauteur;
    m.largeur=largeur;
    allocationGenerique2d(largeur,hauteur,m.data);

    return m;

}

void remplirMatriceGenerique(matriceg r,...)
{
    uint64_t i,j;
    va_list ap;
    va_start(ap,(r.largeur*r.hauteur));
    for(i=0;i<r.hauteur;i++)
    {
        for(j=0;j<r.largeur;j++)
        {
            r.data[i][j]=creerGenerique(va_arg(ap,char*));
        }
    }

}
void afficheMatriceGenerique(matriceg r)
{
    uint64_t i,j;
    printf("hauteur : %d\nlargeur : %d",r.hauteur,r.largeur);
    for(i=0;i<r.largeur;i++)
    {
        for(j=0;j<r.hauteur;i++)
        {
            afficheGenerique(r.data[i][j]);
        }
    }
}

void* mymalloc(uint64_t taille)
{
    void *p=malloc(taille+8);
    printf("%p\n", p);
    p=p+8;
    uint64_t *ptaille=p-8;
    *ptaille=taille;
    return p;
}
uint64_t mymesize(void* pointeurMalloc)
{
    uint64_t* ptaille=pointeurMalloc-8;
    uint64_t taille=*ptaille;
    return taille;

}
uint64_t mytabsize(void* pointeurMalloc,uint64_t nbOctetType)
{
    uint64_t taille=mymesize(pointeurMalloc);
    uint64_t nbcase=taille/nbOctetType;

    return nbcase;

}
void myfree(void* pointeur)
{

    free(pointeur-8);
}
void affichetableau(uint32_t* tableau)
{
    uint32_t i;
    uint64_t tailletab=mytabsize(tableau,sizeof(uint32_t));
    for(i=0;i<tailletab;i++)
    {
        printf("case %d valeur %d\n",i+1,tableau[i]);
    }


}
int main(int argc, const char * argv[])
{
    uint32_t* tab=(uint32_t*)mymalloc(10*sizeof(uint32_t));
    uint32_t i=0;
    uint32_t tailletab=mytabsize(tab,sizeof(uint32_t));
    printf("taille tableau : %d\n",tailletab);
    for(i=0;i<tailletab;i++)
    {
        tab[i]=2*i;
    }
    affichetableau(tab);
    myfree(tab);


    return 0;
}
