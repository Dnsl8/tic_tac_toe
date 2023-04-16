#include <stdio.h>
#include <stdbool.h>
#include "jatek.h"
#include "mentes.h"
#include "debugmalloc.h"

bool mentes(jatek *j, char const *fajlnev, int meret, int jatekmod)
{
    FILE *fp;
    fp = fopen(fajlnev, "wt");

    if (fp == NULL)
        return false;

    fprintf(fp, "%d\n", meret);
    fprintf(fp, "%d\n", jatekmod);

    for (int y = 0; y < meret; ++y)
    {
        for (int x = 0; x < meret; ++x)
        {
            fprintf(fp, "%d ", (int) j->palya[y][x]);
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "%d\n", (int) j->jatekos);
    fprintf(fp, "%d\n", (int) j->allapot);
    fclose(fp);
    return true;
}


bool betolt(jatek *j, char const *fajlnev, int meret, int jatekmod)
{
    FILE *fp;
    fp = fopen(fajlnev, "rt");

    if (fp == NULL)
        return false;

    int b, c, d, e;
    fscanf(fp, " %d", &d);
    meret = d;
    fscanf(fp, " %d", &e);
    jatekmod = e;

    for (int y = 0; y < meret; ++y)
    {
        for (int x = 0; x < meret; ++x)
        {
            int a;
            fscanf(fp, "%d", &a);
            j->palya[y][x] = (cella) a;
        }
    }

    fscanf(fp, " %d", &b );
    j->jatekos = (cella) b;
    fscanf(fp, " %d", &c);
    j->allapot = (jatekallas) c;
    fclose(fp);
    return true;
}

