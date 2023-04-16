#include <stdio.h>
#include <stdlib.h>
#include "jatek.h"
#include "bot.h"
#include "debugmalloc.h"

/*
A gep lepeseit iranyito fuggvenyek megirasahoz az alabbi forrasokat hasznaltam fel:
https://en.wikipedia.org/wiki/Minimax
https://blog.theofekfoundation.org/artificial-intelligence/2015/12/11/minimax-for-gomoku-connect-five/
*/

int kiertekel(jatek *j,int meret)
{
    int ertek = 0;
    if(n_sor(j, jatekos_x,meret,4,2))
    {
        ertek -= 6;
    }
    else if(n_sor(j, jatekos_x,meret,4,1))
    {
        ertek -= 5;
    }
    else if(n_sor(j, jatekos_x,meret,3,2))
    {
        ertek -= 4;
    }
    else if(n_sor(j, jatekos_x,meret,3,1))
    {
        ertek -= 3;
    }
    else if(n_sor(j, jatekos_x,meret,2,2))
    {
        ertek -= 2;
    }
    else if(n_sor(j, jatekos_x,meret,2,1))
    {
        ertek -= 1;
    }
    else if(n_sor(j, jatekos_o,meret,4,2))
    {
        ertek += 6;
    }
    else if(n_sor(j, jatekos_o,meret,4,1))
    {
        ertek += 5;
    }
    else if(n_sor(j, jatekos_o,meret,3,2))
    {
        ertek += 4;
    }
    else if(n_sor(j, jatekos_o,meret,3,1))
    {
        ertek += 3;
    }
    else if(n_sor(j, jatekos_o,meret,2,2))
    {
        ertek += 2;
    }
    else if(n_sor(j, jatekos_o,meret,2,1))
    {
        ertek += 1;
    }

    return ertek;
}

Lepes legjobb_lepes_kiertekelve(jatek *j, int meret)
{
    Lepes proba =
    {
        .x = 0,
        .y = 0,
        .ertek = 0,
    };

    Lepes legjobb =
    {
        .x = 0,
        .y = 0,
        .ertek = 0,
    };

    for(int x=0;x<meret;x++)
    {
        for(int y=0;y<meret;y++)
        {
            if(j->palya[x][y]==ures)
            {
                proba.x=x;
                proba.y=y;
                proba.ertek=kiertekel(j,meret);

                if(proba.ertek>legjobb.ertek)
                {
                    legjobb.ertek = proba.ertek;
                    legjobb.x = proba.x;
                    legjobb.y = proba.y;
                }
            }
        }
    }
    return legjobb;
}

Lepes optimalis(jatek *j, int melyseg, int meret, cella jatekos, int vagas, bool legkulso)
{
    if (cella_szamlal(j->palya, ures, meret) == 0)
    {
        Lepes l =
        {
            .x = 0,
            .y = 0,
            .ertek = kiertekel(j,meret),
        };
        return l;
    }
    if(cella_szamlal(j->palya, jatekos_x, meret) == 1)
    {
       Lepes l =
        {
            .x = 0,
            .y = 0,
            .ertek = kiertekel(j,meret),
        };
        for(int x=0;x<meret;x++)
        {
            for(int y=0;y<meret;y++)
            {
                if(j->palya[x][y]==jatekos_x)
                {
                    while(true)
                    {
                     int rand_x = rand()%3;
                     int rand_y = rand()%3;

                     l.x=x-1+rand_x;
                     l.y=y-1+rand_y;

                     if(l.x>=0 && l.y>=0 && l.x<meret && l.y <meret && j->palya[l.x][l.y]==ures)
                     {
                        break;
                     }
                    }
                }
            }
        }
        return l;
    }
    if(legkulso==true)
    {
        if (n_sor(j, jatekos_o, meret,5,0))
        {
            Lepes proba = legjobb_lepes_kiertekelve(j,meret);
            Lepes l =
            {
                .x = proba.x,
                .y = proba.y,
                .ertek = O_NYERT,
            };
            return l;
        }
        else if (n_sor(j, jatekos_x, meret,5,0))
        {
            Lepes proba = legjobb_lepes_kiertekelve(j,meret);
            Lepes l =
            {
                .x = proba.x,
                .y = proba.y,
                .ertek = X_NYERT,
            };
            return l;
        }
        if (melyseg == 0)
        {
            Lepes l = legjobb_lepes_kiertekelve(j,meret);
            return l;
        }
    }
    else
    {
        if (n_sor(j, jatekos_o, meret,5,0))
        {
            Lepes l =
            {
                .x = 0,
                .y = 0,
                .ertek = O_NYERT,
            };
            return l;
        }
        else if (n_sor(j, jatekos_x, meret,5,0))
        {
            Lepes l =
            {
                .x = 0,
                .y = 0,
                .ertek = X_NYERT,
            };
            return l;
        }
        if (melyseg == 0)
        {
            Lepes l =
            {
                .x = 0,
                .y = 0,
                .ertek = kiertekel(j,meret),
            };
            for(int x=0;x<meret;x++)
            {
                for(int y=0;y<meret;y++)
                {
                    if(j->palya[x][y]==ures)
                    {
                        l.x=x;
                        l.y=y;
                        return l;
                    }
                }
            }
            return l;
        }
    }
    if (jatekos == jatekos_o)
    {
        Lepes legjobb =
            {
                .x = 0,
                .y = 0,
                .ertek = X_NYERT - 1,
            };
        for (int x=0;x<meret;x++)
        {
            for (int y=0;y<meret;y++)
            {
                if (j->palya[x][y]==ures)
                {
                    j->palya[x][y]=jatekos_o;
                    Lepes proba = optimalis(j,melyseg-1,meret,jatekos_x, legjobb.ertek, false);
                    j->palya[x][y]=ures;
                    if (proba.ertek > legjobb.ertek)
                    {
                        legjobb.x=x;
                        legjobb.y=y;
                        legjobb.ertek=proba.ertek;
                    }
                    if(legjobb.ertek>vagas)
                    {
                        return legjobb;
                    }
                }
            }
        }
        return legjobb;
    }
    else
    {
        Lepes legjobb =
            {
                .x = 0,
                .y = 0,
                .ertek = O_NYERT + 1,
            };
        for (int x=0;x<meret;x++)
        {
            for (int y=0;y<meret;y++)
            {
                if (j->palya[x][y]==ures)
                {
                    j->palya[x][y]=jatekos_x;
                    Lepes proba = optimalis(j,melyseg-1,meret, jatekos_o,legjobb.ertek, false);
                    j->palya[x][y]=ures;
                    if (proba.ertek < legjobb.ertek)
                    {
                        legjobb.x=x;
                        legjobb.y=y;
                        legjobb.ertek=proba.ertek;
                    }
                    if(legjobb.ertek<vagas )
                    {
                        return legjobb;
                    }
                }
            }
        }
        return legjobb;
    }
}

