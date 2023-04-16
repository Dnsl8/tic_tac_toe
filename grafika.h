#ifndef GRAFIKA_H
#define GRAFIKA_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "jatek.h"

void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
void jatek_kirajzol(SDL_Renderer *renderer, jatek *j, int meret);
double cella_szelesseg(int meret);
double cella_magassag(int meret);
void szoveg(SDL_Renderer *r, char *c, int betumeret, int x, int y);

#endif

