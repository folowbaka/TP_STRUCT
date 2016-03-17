#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include<stdbool.h>
typedef struct
{
    uint64_t m;
    uint64_t* sol;
}minimale;
void solutionToStringDynamique(uint64_t* tabSolution,uint64_t tailleSolution)
{
    uint64_t i=0;
    printf("Solution={");
    while(i<tailleSolution)
    {
        if(i+1==tailleSolution)
        {
            printf("%d}\n",tabSolution[i]);
        }
        else
        {
            printf("%d,",tabSolution[i]);
        }
        i++;
    }
}
void solutionToStringGlouton(uint64_t* tabSolution,uint64_t tailleSolution)
{
    uint64_t i=0;
    printf("Solution={");
    while(tabSolution[i]!=0 && i<tailleSolution)
    {
        if(tabSolution[i+1]==0 || i==tailleSolution)
        {
            printf("%d}\n",tabSolution[i]);
        }
        else
        {
            printf("%d,",tabSolution[i]);
        }
        i++;
    }
}
uint64_t* glouton(uint64_t S,uint64_t* L,uint64_t taille_L)
{
    uint64_t i=0,j=0,tailleSolution=0;
    if(S%L[taille_L-1]==0)
        tailleSolution=S/L[taille_L-1];
    else
        tailleSolution=(S/L[taille_L-1])+1;
    uint64_t* tabSolution=(uint64_t*)calloc(tailleSolution,sizeof(uint64_t));

    printf("Valeur de la taille de la solution au pire cas : %d\n",tailleSolution);
    while(S!=0 && i<taille_L && j<tailleSolution)
    {
        int p=S-L[i];
        printf("Valeur de S : %d, ",S);
         printf("valeur de l[i] : %d\n",L[i]);
        if(p>=0)
        {
            S=S-L[i];
            tabSolution[j]=L[i];
            j++;
        }
        else
            i++;

        printf("Valeur de suivante de S : %d\n",S);

    }
    if(S!=0)
    {
        fprintf(stderr,"Erreur : Aucune solution n'a ete trouvee");
        return NULL;
    }
    else
    {
        solutionToStringGlouton(tabSolution,tailleSolution);
        return tabSolution;
    }

}

uint64_t* dynamique(uint64_t S,uint64_t* L,uint64_t taille_L)
{

    uint64_t i=0,j=0,k=0,m=0,n=0;
    uint64_t* L_Croissant=(uint64_t*)malloc(taille_L*sizeof(uint64_t));
    for(i=0;i<taille_L;i++)
    {
        L_Croissant[i]=L[taille_L-1-i];
    }
    minimale*** matrice=(minimale ***)malloc(taille_L*sizeof(minimale**));
    for(i=0;i<taille_L;i++)
    {
        matrice[i]=(minimale**)malloc(((S+1))*sizeof(minimale*));
    }
    for(i=0;i<taille_L;i++)
    {
        for(j=0;j<=S;j++)
        {
            matrice[i][j]=(minimale*)malloc(sizeof(minimale));
            matrice[i][j]->sol=(uint64_t*)calloc(taille_L,sizeof(uint64_t));
        }
    }
    for(i=0;i<taille_L;i++)
    {
        for(j=0;j<=S;j++)
        {
             printf("i : %d    ",i);
             printf("j : %d\n",j);
            if(j==0)
            {
                matrice[i][j]->m=0;
               for(n=0;n<i;n++)
                {
                    matrice[i][j]->sol[n]=0;
                }
            }
            else if(j%L_Croissant[i]==0)
            {
                 m=j/L_Croissant[i];
                 matrice[i][j]->m=m;
                 for(n=0;n<i;n++)
                {
                    matrice[i][j]->sol[n]=0;
                }
                 matrice[i][j]->sol[i]=m;
            }
             else if(L_Croissant[i]>j && i==0)
            {
                matrice[i][j]->m=0;
            }
            else if(L_Croissant[i]>j)
            {
                matrice[i][j]->m=matrice[i-1][j]->m;
                for(n=0;n<i;n++)
                {
                    matrice[i][j]->sol[n]=matrice[i-1][j]->sol[n];
                }
            }
            else
            {
                k=j%L_Croissant[i];
                m=j/L_Croissant[i];
                printf("k :   %d\n",k);
                printf("m : %d\n",m);
                if(m+matrice[i][k]->m<matrice[i-1][j]->m)
                {
                    matrice[i][j]->m=m+matrice[i][k]->m;
                    for(n=0;n<i;n++)
                    {
                        matrice[i][j]->sol[n]=matrice[i][k]->sol[n];
                    }
                    matrice[i][j]->sol[i]=m;
                }
                else
                {
                    matrice[i][j]->m=matrice[i-1][j]->m;
                    for(n=0;n<i;n++)
                    {
                        matrice[i][j]->sol[n]=matrice[i-1][j]->sol[n];
                    }
                }
            }
            printf("mbla:    %d\n",matrice[i][j]->m);
            solutionToStringDynamique(matrice[i][j]->sol,taille_L);
        }
    }
    uint64_t *tabSolution=(uint64_t *)malloc(matrice[taille_L-1][S]->m*sizeof(uint64_t));
    n=0;
    for(i=0;i<matrice[taille_L-1][S]->m;i++)
    {
        while(matrice[taille_L-1][S]->sol[n]==0)
                    n++;
        tabSolution[i]=L_Croissant[n];
        matrice[taille_L-1][S]->sol[n]--;
    }
    solutionToStringDynamique(tabSolution,matrice[taille_L-1][S]->m);
     for(i=0;i<taille_L;i++)
    {
        for(j=0;j<=S;j++)
        {
            free(matrice[i][j]->sol);
            free(matrice[i][j]);
        }
    }
    for(i=0;i<taille_L;i++)
    {
        free(matrice[i]);
    }
    free(matrice);
    return tabSolution;
}
uint64_t comptePiece(uint64_t* solution)
{
    uint64_t i=0;
    while(solution[i]!=NULL && solution[i]!=0)
    {
        i++;
    }

    return i;
}
bool canonique(uint64_t* L,uint64_t taille_L)
{
    uint64_t v=L[0]+2;
    uint64_t* solutionGv=glouton(v,L,taille_L);
    uint64_t* solutionGvc=NULL;
    uint64_t i=0,Gvc=0;
    uint64_t Gv=comptePiece(solutionGv);
    bool canonique=true;
    while(canonique && i<taille_L)
    {
        solutionGvc=glouton(v-L[i],L,taille_L);
        Gvc=comptePiece(solutionGvc);
        if(Gv>Gvc+1)
                canonique=false;

        i++;
        printf("Gv : %d  ",Gv);
        printf("Gvc +1 :  %d \n",(Gvc));
    }
    free(solutionGv);
    free(solutionGvc);
    if(canonique)
       printf("Ce systeme de pieces est canonique l'algorithme glouton sera donc optimal\n");
    else
        printf("Ce systeme de pieces n'est pas canonique l'algorithme glouton ne sera donc pas optimal\n");
    return canonique;
}
int main()
{
    uint64_t L[4]={6,5,4,1};
    //glouton(15,L,4);
    //free(dynamique(15,L,4));
    canonique(L,4);
    return 0;
}
