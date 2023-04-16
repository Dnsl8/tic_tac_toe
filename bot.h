#ifndef BOT_H
#define BOT_H

#define O_NYERT 99999
#define X_NYERT (-O_NYERT)

typedef struct Lepes{
    int x;
    int y;
    int ertek;
} Lepes;

Lepes optimalis(jatek *j, int melyseg, int meret, cella jatekos, int vagas, bool legkulso);
int kiertekel(jatek *j,int meret);

#endif
