#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include "jatek.h"
#include "grafika.h"
#include "debugmalloc.h"

SDL_Surface *felirat;
SDL_Texture *felirat_t;
SDL_Rect hova = { 0, 0, 0, 0 };

const SDL_Color fekete = { .r = 0, .g = 0, .b = 0 };
const SDL_Color feher = { .r = 255, .g = 255, .b = 255 };
const SDL_Color piros = { .r = 255, .g = 0, .b = 0 };
const SDL_Color kek = { .r = 0, .g = 0, .b = 255 };
const SDL_Color szurke = { .r = 100, .g = 100, .b = 100 };

double cella_szelesseg(int meret)
{
    return palya_szelesseg/meret;
}

double cella_magassag(int meret)
{
    return palya_szelesseg/meret;
}

void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Amoba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    *pwindow = window;
    *prenderer = renderer;
}

void szoveg(SDL_Renderer *r, char *c, int betumeret, int x, int y)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", betumeret);
    if (!font)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    felirat = TTF_RenderUTF8_Solid(font, c, fekete);
    felirat_t = SDL_CreateTextureFromSurface(r, felirat);
    hova.x = x;
    hova.y = y;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(r, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    TTF_CloseFont(font);
}

void halo_kirajzol(SDL_Renderer *renderer, const SDL_Color *color, int meret)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 0; i <=meret; ++i)
    {
        SDL_RenderDrawLine(renderer,
                           i * cella_szelesseg(meret), 0,
                           i * cella_szelesseg(meret), palya_magassag);
        SDL_RenderDrawLine(renderer,
                           0, i * cella_magassag(meret),
                           palya_szelesseg, i * cella_magassag(meret));
    }
}

void x_kirajzol(SDL_Renderer *renderer, int sor, int oszlop, const SDL_Color *color, int meret)
{
    const float keret = fmin(cella_szelesseg(meret), cella_magassag(meret)) * 0.25;
    const float center_x = cella_szelesseg(meret) * 0.5 + oszlop * cella_szelesseg(meret);
    const float center_y = cella_magassag(meret) * 0.5 + sor * cella_magassag(meret);

    thickLineRGBA(renderer,
                  center_x - keret,
                  center_y - keret,
                  center_x + keret,
                  center_y + keret,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);
    thickLineRGBA(renderer,
                  center_x + keret,
                  center_y - keret,
                  center_x - keret,
                  center_y + keret,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);
}

void o_kirajzol(SDL_Renderer *renderer, int sor, int oszlop, const SDL_Color *color, int meret)
{
    const float keret = fmin(cella_szelesseg(meret),cella_magassag(meret)) * 0.25;
    const float center_x = cella_szelesseg(meret) * 0.5 + oszlop * cella_szelesseg(meret);
    const float center_y = cella_magassag(meret) * 0.5 + sor * cella_magassag(meret);

    filledCircleRGBA(renderer,
                     center_x, center_y, keret + 5,
                     color->r, color->g, color->b, 255);
    filledCircleRGBA(renderer,
                     center_x, center_y, keret - 5,
                     0, 0, 0, 255);
}

void palya_kirajzol(SDL_Renderer *renderer, cella **palya, const SDL_Color *x_szin, const SDL_Color *o_szin, int meret)
{
    for (int i = 0; i < meret; ++i)
    {
        for (int j = 0; j < meret; ++j)
        {
            switch (palya[i][j])
            {
                case jatekos_x:
                    x_kirajzol(renderer, i, j, x_szin, meret);
                    break;

                case jatekos_o:
                    o_kirajzol(renderer, i, j, o_szin, meret);
                    break;

                default: {}
            }
        }
    }
}

void kozben_kirajzol(SDL_Renderer *renderer, jatek *j, int meret)
{
    halo_kirajzol(renderer, &feher, meret);
    palya_kirajzol(renderer, j->palya, &piros, &kek, meret);
    boxRGBA(renderer, 490, 530, 370, 570, 255, 255, 255, 255);
    szoveg(renderer, "Quit", 40, 395, 525);
    boxRGBA(renderer, 130, 530, 10, 570, 255, 255, 255, 255);
    szoveg(renderer, "Save", 40, 30, 525);
}

void vegen_kirajzol(SDL_Renderer *renderer, jatek *j, const SDL_Color *color, int meret)
{
    halo_kirajzol(renderer, color, meret);
    palya_kirajzol(renderer, j->palya, color, color, meret);
    boxRGBA(renderer, palya_szelesseg/meret, 150, palya_szelesseg-(palya_szelesseg/meret), 350, color->r, color->g, color->b, 255);
    szoveg(renderer, "GAME OVER", 50, 100, 220);
    boxRGBA(renderer, 490, 530, 370, 570, 255, 255, 255, 255);
    szoveg(renderer, "Quit", 40, 395, 525);
}

void jatek_kirajzol(SDL_Renderer *renderer, jatek *j, int meret)
{
    switch (j->allapot)
    {
        case folyamatban:
            kozben_kirajzol(renderer, j, meret);
            break;

        case x_nyert:
            vegen_kirajzol(renderer, j, &piros, meret);
            break;

        case o_nyert:
            vegen_kirajzol(renderer, j, &kek, meret);
            break;

        case egyenlo:
            vegen_kirajzol(renderer, j, &szurke, meret);
            break;

        default: {}
    }
}


