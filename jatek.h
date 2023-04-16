#ifndef JATEK_H
#define JATEK_H

#define ablak_szelesseg 500.0
#define ablak_magassag 600.0
#define palya_szelesseg 500.0
#define palya_magassag 500.0

#include <stdbool.h>

typedef enum cella{
    ures,
    jatekos_x ,
    jatekos_o
} cella;

typedef enum jatekallas{
folyamatban,
x_nyert,
o_nyert,
egyenlo,
kilepes
}jatekallas;


typedef struct jatek{
    cella **palya;
    cella jatekos;
    jatekallas allapot;
} jatek;

void lepes(jatek *j, int sor, int oszlop, const int meret);
bool n_sor(jatek *pj, int jatekos, int meret, int n, int ures_vegek);
int cella_szamlal( cella **palya, cella keresett, int meret);

#endif


