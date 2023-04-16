#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "jatek.h"
#include "grafika.h"
#include "menu.h"
#include "debugmalloc.h"

void fomenu_kirajzol(SDL_Renderer *renderer)
{
     boxRGBA(renderer, 330, 90, 170, 210, 255, 0, 0, 255);
     boxRGBA(renderer, 320, 100, 180, 200, 255, 255, 255, 255);
     boxRGBA(renderer, 330, 240, 170, 360, 0, 0, 255, 255);
     boxRGBA(renderer, 320, 250, 180, 350, 255, 255, 255, 255);
     szoveg(renderer, "New game", 30, 185, 130);
     szoveg(renderer, "Continue", 30, 195, 280);
}

void uj_jatek_menu_kirajzol(SDL_Renderer *renderer)
{
     boxRGBA(renderer, 240, 100, 90, 200, 0, 0, 255, 255);
     boxRGBA(renderer, 230, 110, 100, 190, 255, 255, 255, 255);
     szoveg(renderer, "Single Player", 22, 105, 140);

     boxRGBA(renderer, 410, 100, 260, 200, 255, 0, 0, 255);
     boxRGBA(renderer, 400, 110, 270, 190, 255, 255, 255, 255);
     szoveg(renderer, "Multiplayer", 22, 285, 140);

     boxRGBA(renderer, 330, 250, 180, 350, 255, 0, 0, 255);
     boxRGBA(renderer, 320, 260, 190, 340, 255, 255, 255, 255);
     szoveg(renderer, "5x5", 30, 230, 285);

     boxRGBA(renderer, 400, 280, 350, 320, 255, 255, 255, 255);
     szoveg(renderer, "+", 40, 365, 280);

     boxRGBA(renderer, 160, 280, 110, 320, 255, 255, 255, 255);
     szoveg(renderer, "-", 40, 130, 275);

     boxRGBA(renderer, 330, 380, 180, 480, 0, 0, 255, 255);
     boxRGBA(renderer, 320, 390, 190, 470, 255, 255, 255, 255);
     szoveg(renderer, "START", 30, 210, 415);

}


