#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "jatek.h"
#include "grafika.h"
#include "menu.h"
#include "memoria.h"
#include "mentes.h"
#include "bot.h"
#include "debugmalloc.h"

int palya_meret = 5;
int melyseg = 2;
int jatekmod =1;

char c5[4] = "5x5";
char c6[4] = "6x6";
char c7[4] = "7x7";
char c8[4] = "8x8";
char c9[4] = "9x9";
char c10[6] = "10x10";

int main(int argc, char *argv[])
{
    srand(time(0));

    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(ablak_szelesseg, ablak_magassag, &window, &renderer);

    jatek j =
    {
        .palya = NULL,
        .jatekos = jatekos_x,
        .allapot = folyamatban,
    };

    j.palya = palya_lefoglal(palya_meret);

    fomenu_kirajzol(renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    bool uj_jatek = false;
    bool folytatas = false;
    int x = 0;
    int y = 0;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
           case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                if(x>=180 && x<=320 && y>=100 && y<=200)
                {
                    uj_jatek = true;
                }
                if(x>=180 && x<=320 && y>=251 && y<=350)
                {
                    folytatas = true;
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
        if(folytatas)
        {
            palya_felszabadit(j.palya, palya_meret);

            FILE *fp;
            fp = fopen("mentes.txt", "rt");
            if (fp == NULL)
                return false;
            fscanf(fp, " %d", &palya_meret);
            fscanf(fp, " %d", &jatekmod);

            j.palya = palya_lefoglal(palya_meret);
            betolt(&j, "mentes.txt", palya_meret,jatekmod);

            if(jatekmod ==1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                jatek_kirajzol(renderer, &j, palya_meret);
                SDL_RenderPresent(renderer);

                SDL_Event event;
                        while (!quit)
                        {
                            while (SDL_PollEvent(&event))
                            {
                                int lepes_sor;
                                int lepes_oszlop ;
                                switch (event.type)
                                {
                                    case SDL_QUIT:
                                        quit = true;
                                        break;

                                    case SDL_MOUSEBUTTONDOWN:
                                        x = event.button.x;
                                        y = event.button.y;
                                        if(y<=500)
                                        {
                                            lepes_sor = y / cella_magassag(palya_meret);
                                            if (lepes_sor >= palya_meret)
                                            {
                                                lepes_sor = palya_meret - 1;
                                            }
                                            lepes_oszlop = x / cella_szelesseg(palya_meret);
                                            if (lepes_oszlop >= palya_meret)
                                            {
                                                lepes_oszlop = palya_meret - 1;
                                            }
                                            lepes(&j, lepes_sor, lepes_oszlop, palya_meret);
                                        }
                                        else if(x>=10 && x<=130 && y>=530 && y<=570)
                                        {
                                            mentes(&j, "mentes.txt", palya_meret, 1);
                                            break;
                                        }
                                        else if(x>=370 && x<=490 && y>=530 && y<=570)
                                        {
                                            quit = true;
                                            break;
                                        }

                                    default: {}
                                }
                            }

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            jatek_kirajzol(renderer, &j, palya_meret);
                            SDL_RenderPresent(renderer);

                            SDL_Delay(300);

                            if(j.jatekos==jatekos_o)
                            {
                                Lepes gep_lep = optimalis(&j,melyseg,palya_meret,jatekos_o, O_NYERT+1, true);
                                lepes(&j,gep_lep.x,gep_lep.y,palya_meret);
                            }

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            jatek_kirajzol(renderer, &j, palya_meret);
                            SDL_RenderPresent(renderer);
                        }
            }

            if(jatekmod ==0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                jatek_kirajzol(renderer, &j, palya_meret);
                SDL_RenderPresent(renderer);

                SDL_Event event;
                        while (!quit)
                        {
                            while (SDL_PollEvent(&event))
                            {
                                int lepes_sor;
                                int lepes_oszlop ;
                                switch (event.type)
                                {
                                    case SDL_QUIT:
                                        quit = true;
                                        break;

                                    case SDL_MOUSEBUTTONDOWN:
                                        x = event.button.x;
                                        y = event.button.y;
                                        if(y<=500)
                                        {
                                            lepes_sor = y / cella_magassag(palya_meret);
                                            if (lepes_sor >= palya_meret)
                                            {
                                                lepes_sor = palya_meret - 1;
                                            }
                                            lepes_oszlop = x / cella_szelesseg(palya_meret);
                                            if (lepes_oszlop >= palya_meret)
                                            {
                                                lepes_oszlop = palya_meret - 1;
                                            }
                                            lepes(&j, lepes_sor, lepes_oszlop, palya_meret);
                                        }
                                        else if(x>=10 && x<=130 && y>=530 && y<=570)
                                        {
                                            mentes(&j, "mentes.txt", palya_meret, 0);
                                            break;
                                        }
                                        else if(x>=370 && x<=490 && y>=530 && y<=570)
                                        {
                                            quit = true;
                                            break;
                                        }

                                    default: {}
                                }
                            }

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            jatek_kirajzol(renderer, &j, palya_meret);
                            SDL_RenderPresent(renderer);
                        }
                    }
            }

        if (uj_jatek)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            uj_jatek_menu_kirajzol(renderer);
            SDL_RenderPresent(renderer);

            bool start = false;
            bool egyjatekos = false;
            bool tobbjatekos = false;
            x = 0;
            y = 0;
            while (!quit) {
                SDL_Event event;
                SDL_WaitEvent(&event);
                switch (event.type) {
                   case SDL_MOUSEBUTTONDOWN:
                        x = event.button.x;
                        y = event.button.y;
                        if(x>=350 && x<=400 && y>=280 && y<=320 && palya_meret<10 && palya_meret>4)
                        {
                            palya_felszabadit(j.palya,palya_meret);
                            palya_meret++;
                            j.palya = palya_lefoglal(palya_meret);
                            boxRGBA(renderer, 330, 250, 180, 350, 255, 0, 0, 255);
                            boxRGBA(renderer, 320, 260, 190, 340, 255, 255, 255, 255);
                            if(palya_meret == 5)
                            {
                                    szoveg(renderer, c5, 30, 230, 285);
                            }
                            if(palya_meret == 6)
                            {
                                    szoveg(renderer, c6, 30, 230, 285);
                            }
                            if(palya_meret == 7)
                            {
                                    szoveg(renderer, c7, 30, 230, 285);
                            }
                            if(palya_meret == 8)
                            {
                                    szoveg(renderer, c8, 30, 230, 285);
                            }
                            if(palya_meret == 9)
                            {
                                    szoveg(renderer, c9, 30, 230, 285);
                            }
                            if(palya_meret == 10)
                            {
                                    szoveg(renderer, c10, 30, 230, 285);
                            }

                            SDL_RenderPresent(renderer);
                        }
                        else if(x>=110 && x<=160 && y>=280 && y<=320 && palya_meret>5 && palya_meret<11)
                        {
                            palya_felszabadit(j.palya,palya_meret);
                            palya_meret--;
                            j.palya = palya_lefoglal(palya_meret);
                            boxRGBA(renderer, 330, 250, 180, 350, 255, 0, 0, 255);
                            boxRGBA(renderer, 320, 260, 190, 340, 255, 255, 255, 255);
                            if(palya_meret == 5)
                            {
                                    szoveg(renderer, c5, 30, 230, 285);
                            }
                            if(palya_meret == 6)
                            {
                                    szoveg(renderer, c6, 30, 230, 285);
                            }
                            if(palya_meret == 7)
                            {
                                    szoveg(renderer, c7, 30, 230, 285);
                            }
                            if(palya_meret == 8)
                            {
                                    szoveg(renderer, c8, 30, 230, 285);
                            }
                            if(palya_meret == 9)
                            {
                                    szoveg(renderer, c9, 30, 230, 285);
                            }
                            if(palya_meret == 10)
                            {
                                    szoveg(renderer, c10, 30, 230, 285);
                            }

                            SDL_RenderPresent(renderer);
                        }
                        else if(x>=100 && x<=230 && y>=110 && y<=190)
                        {
                            egyjatekos = true;
                            tobbjatekos = false;
                        }
                        else if(x>=270 && x<=400 && y>=110 && y<=190)
                        {
                            tobbjatekos = true;
                            egyjatekos = false;
                        }

                        else if(x>=190 && x<=320 && y>=390 && y<=470)
                        {
                            start = true;
                        }
                        break;
                    case SDL_QUIT:
                        quit = true;
                        break;
                }

                if (start && egyjatekos)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    jatek_kirajzol(renderer, &j, palya_meret);
                    SDL_RenderPresent(renderer);

                    SDL_Event event;
                    while (!quit)
                    {
                        while (SDL_PollEvent(&event))
                        {
                            int lepes_sor;
                            int lepes_oszlop ;
                            switch (event.type)
                            {
                                case SDL_QUIT:
                                    quit = true;
                                    break;

                                case SDL_MOUSEBUTTONDOWN:
                                    x = event.button.x;
                                    y = event.button.y;
                                    if(y<=500)
                                    {
                                        lepes_sor = y / cella_magassag(palya_meret);
                                        if (lepes_sor >= palya_meret)
                                        {
                                            lepes_sor = palya_meret - 1;
                                        }
                                        lepes_oszlop = x / cella_szelesseg(palya_meret);
                                        if (lepes_oszlop >= palya_meret)
                                        {
                                            lepes_oszlop = palya_meret - 1;
                                        }
                                        lepes(&j, lepes_sor, lepes_oszlop, palya_meret);
                                    }
                                    else if(x>=10 && x<=130 && y>=530 && y<=570)
                                    {
                                        mentes(&j, "mentes.txt", palya_meret, 1);
                                        break;
                                    }
                                    else if(x>=370 && x<=490 && y>=530 && y<=570)
                                    {
                                        quit = true;
                                        break;
                                    }

                                default: {}
                            }
                        }

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        jatek_kirajzol(renderer, &j, palya_meret);
                        SDL_RenderPresent(renderer);

                        SDL_Delay(300);

                        if(j.jatekos==jatekos_o)
                        {
                            Lepes gep_lep = optimalis(&j,melyseg,palya_meret,jatekos_o, O_NYERT+1, true);
                            lepes(&j,gep_lep.x,gep_lep.y,palya_meret);
                        }

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        jatek_kirajzol(renderer, &j, palya_meret);
                        SDL_RenderPresent(renderer);
                    }
                }

                else if (start && tobbjatekos)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    jatek_kirajzol(renderer, &j, palya_meret);
                    SDL_RenderPresent(renderer);

                    SDL_Event event;
                    while (!quit)
                    {
                        while (SDL_PollEvent(&event))
                        {
                            int lepes_sor;
                            int lepes_oszlop ;
                            switch (event.type)
                            {
                                case SDL_QUIT:
                                    quit = true;
                                    break;

                                case SDL_MOUSEBUTTONDOWN:
                                    x = event.button.x;
                                    y = event.button.y;
                                    if(y<=500)
                                    {
                                        lepes_sor = y / cella_magassag(palya_meret);
                                        if (lepes_sor >= palya_meret)
                                        {
                                            lepes_sor = palya_meret - 1;
                                        }
                                        lepes_oszlop = x / cella_szelesseg(palya_meret);
                                        if (lepes_oszlop >= palya_meret)
                                        {
                                            lepes_oszlop = palya_meret - 1;
                                        }
                                        lepes(&j, lepes_sor, lepes_oszlop, palya_meret);
                                    }
                                    else if(x>=10 && x<=130 && y>=530 && y<=570)
                                    {
                                        mentes(&j, "mentes.txt", palya_meret, 0);
                                        break;
                                    }
                                    else if(x>=370 && x<=490 && y>=530 && y<=570)
                                    {
                                        quit = true;
                                        break;
                                    }

                                default: {}
                            }
                        }

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        jatek_kirajzol(renderer, &j, palya_meret);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    palya_felszabadit(j.palya,palya_meret);
    return 0;
}
