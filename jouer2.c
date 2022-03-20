#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "jouer.h"
#include "jouer2.h"
#include <time.h>


void jouer2(SDL_Surface *ecran)
{
    int con=1,carte[12][12]={0},direction=BAS,tempsactuel=0,tempsprecedent=0,i,j;
    SDL_Surface *mvt[4]={NULL},*mure=NULL,*mvtactuel=NULL,*fin=NULL,*bravo=NULL;
    SDL_Event event;
    SDL_Rect position,posimario,posmur,posfin,posibravo;

    mvt[HAUT]=IMG_Load("mario_haut.gif");
    mvt[BAS]=IMG_Load("mario_bas.gif");
    mvt[GAUCHE]=IMG_Load("mario_gauche.gif");
    mvt[DROITE]=IMG_Load("mario_droite.gif");
    mure=IMG_Load("mur.jpg");
    fin=IMG_Load("fin.png");
    bravo=IMG_Load("bravo.png");

    remplir(&carte);

    mvtactuel=mvt[BAS];


    do{
        srand(time(NULL));
        posimario.x=(rand() % (11)) + 0;
        posimario.y=(rand() % (11)) + 0;

    }while(carte[posimario.x][posimario.y]==MUR);



    position.x=(posimario.x)*taille_box;
    position.y=(posimario.y)*taille_box;

    posibravo.x=0;
    posibravo.y=0;

    while(con)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                con=0;
                break;
        }
        tempsactuel=SDL_GetTicks();
        if (tempsactuel-tempsprecedent>500)
        {
            RMD(carte,&posimario,&direction);
            mvtactuel=mvt[direction];
            tempsprecedent=tempsactuel;
        }
        else
        {
            SDL_Delay(500-(tempsactuel-tempsprecedent));
        }
        position.x=posimario.x * taille_box;
        position.y=posimario.y * taille_box;
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
        for (i=0;i<lar_box;i++)
        {
            for (j=0;j<haut_box;j++)
            {
                if (carte[i][j]==MUR)
                {

                    posmur.x=i*taille_box;
                    posmur.y=j*taille_box;
                    SDL_BlitSurface(mure,NULL,ecran,&posmur);
                }
                if (carte[i][j]==FIN)
                {
                    posfin.x=i*taille_box;
                    posfin.y=j*taille_box;
                    SDL_BlitSurface(fin,NULL,ecran,&posfin);
                }

            }
        }
        if (carte[posimario.x][posimario.y]==FIN)
        {
            SDL_BlitSurface(bravo,NULL,ecran,&posibravo);
            SDL_Flip(ecran);
            SDL_Delay(1000);
            break;
        }
        else
        {
            SDL_BlitSurface(mvtactuel,NULL,ecran,&position);
            SDL_Flip(ecran);
        }
    }
    SDL_FreeSurface(mure);
    SDL_FreeSurface(fin);
    SDL_FreeSurface(mvtactuel);
    SDL_FreeSurface(bravo);
    for (i=0;i<4;i++)
    {
        SDL_FreeSurface(mvt[i]);
    }
}


void RMD(int carte[][haut_box],SDL_Rect *pos,int *dir)
{
    if (carte[pos->x+1][pos->y]==VIDE || carte[pos->x+1][pos->y]==FIN)
    {
        pos->x=pos->x+1;
        *dir=DROITE;

    }
    else
    {
        if(carte[pos->x][pos->y-1]==VIDE || carte[pos->x][pos->y-1]==FIN)
        {
            pos->y=pos->y-1;
            *dir=HAUT;

        }
        else
        {
            if(carte[pos->x][pos->y+1]==VIDE || carte[pos->x][pos->y+1]==FIN)
            pos->y=pos->y+1;
            *dir=BAS;
        }
    }


}




