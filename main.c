#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "jouer.h"
#include "jouer2.h"
#include <time.h>



int main(int argc , char **argv)
{
    SDL_Surface *ecran=NULL , *menu=NULL;
    SDL_Rect posi;
    int con=1;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("caisse.jpg"),NULL);

    ecran=SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("le labyrinthe",NULL);

    menu=IMG_Load("menu.png");

    posi.x=0;
    posi.y=0;

    while(con)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                con=0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                     case SDLK_3:
                         con=0;
                         break;
                     case SDLK_1:
                         jouer(ecran);
                         break;
                     case SDLK_2:
                         jouer2(ecran);
                         break;
                }
                break;

        }
        SDL_BlitSurface(menu,NULL,ecran,&posi);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
