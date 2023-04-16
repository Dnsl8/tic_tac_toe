#include <stdlib.h>
#include <stdio.h>
#include "memoria.h"
#include "debugmalloc.h"

cella** palya_lefoglal(int x)
{
    cella **palya=(cella**)malloc(x*sizeof(cella*));
    for(int i=0;i<x;i++)
    {
        palya[i]=(cella*)malloc(x*sizeof(cella));
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            palya[i][j]= ures;
        }
    }
    return palya;
}

void palya_felszabadit(cella **palya, int x)
{
    for(int i=0; i<x; i++)
    {
        free(palya[i]);
    }
    free(palya);
}


