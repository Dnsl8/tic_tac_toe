#include "jatek.h"
#include "debugmalloc.h"
#include <stdbool.h>

void jatekos_csere(jatek *j)
{
    if (j->jatekos == jatekos_x)
    {
        j->jatekos = jatekos_o;
    }
    else if (j->jatekos == jatekos_o)
    {
        j->jatekos = jatekos_x;
    }
}

bool n_egy_iranyban(jatek *pj,int jatekos,int meret,int kezdet_x,int kezdet_y,int irany_x,int irany_y, int n, int ures_vegek)
{
    for (int x = 0; x<n; ++x)
    {
        int sor = kezdet_y + x * irany_y;
        int oszlop = kezdet_x + x * irany_x;
        if(sor < 0 || oszlop < 0 ||sor>=meret || oszlop>=meret || pj->palya[sor][oszlop] != jatekos)
        {
            return false;
        }
    }

    int ures_kezdet = 1;
    int sor = kezdet_y - irany_y;
    int oszlop = kezdet_x - irany_x;

    if(sor < 0 || oszlop < 0 ||sor>=meret || oszlop>=meret || pj->palya[sor][oszlop] != ures)
    {
        ures_kezdet = 0;
    }

    int ures_veg = 1;
    sor = kezdet_y + n * irany_y;
    oszlop = kezdet_x + n * irany_x;

    if(sor < 0 || oszlop < 0 ||sor>=meret || oszlop>=meret || pj->palya[sor][oszlop] != ures)
    {
        ures_veg = 0;
    }

    return (ures_kezdet + ures_veg) >= ures_vegek;
}

bool n_sor(jatek *pj, int jatekos, int meret, int n, int ures_vegek)
{
    for (int y = 0; y < meret; ++y)
    {
        for (int x = 0; x < meret; ++x)
        {
            if (n_egy_iranyban(pj, jatekos, meret, x, y, 1, 0,n,ures_vegek))
                return true;
            if (n_egy_iranyban(pj, jatekos, meret, x, y, 1, 1,n,ures_vegek))
                return true;
            if (n_egy_iranyban(pj, jatekos, meret, x, y, 0, 1,n,ures_vegek))
                return true;
            if (n_egy_iranyban(pj, jatekos, meret, x, y, -1, 1,n,ures_vegek))
                return true;
        }
    }
    return false;
}

int cella_szamlal( cella **palya, cella keresett, int meret)
{
    int db = 0;

    for (int i = 0; i < meret; ++i)
    {
        for(int j=0;j<meret;j++)
        {
            if (palya[i][j] == keresett)
            {
                db++;
            }
        }
    }

    return db;
}

void jatek_vege(jatek *j, int meret)
{
    if (n_sor(j, jatekos_x, meret,5,0))
    {
        j->allapot = x_nyert;
    }
    else if (n_sor(j, jatekos_o, meret,5,0))
    {
        j->allapot = o_nyert;
    }
    else if (cella_szamlal(j->palya, ures, meret) == 0)
    {
        j->allapot = egyenlo;
    }
}

void lepes(jatek *j, int sor, int oszlop, int meret)
{
    if (j->palya[sor][oszlop] == ures && j->allapot == folyamatban)
    {
        j->palya[sor][oszlop] = j->jatekos;
        jatekos_csere(j);
        jatek_vege(j, meret);
    }
}



