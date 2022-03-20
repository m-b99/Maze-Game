#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "jouer.h"
#include <time.h>



void jouer(SDL_Surface *ecran)
{
    int con=1,i=0,j=0,carte[12][12]={0};
    SDL_Surface *mvt[4]={NULL},*mure=NULL,*mvtactuel=NULL,*fin=NULL,*bravo;
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

    SDL_EnableKeyRepeat(100,100);

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
                    case SDLK_ESCAPE:
                        con=0;
                        break;
                    case SDLK_UP:
                        mvtactuel=mvt[HAUT];
                        deplacement(carte,&posimario,HAUT);
                        break;
                    case SDLK_DOWN:
                        mvtactuel=mvt[BAS];
                        deplacement(carte,&posimario,BAS);
                        break;
                    case SDLK_LEFT:
                        mvtactuel=mvt[GAUCHE];
                        deplacement(carte,&posimario,GAUCHE);
                        break;
                    case SDLK_RIGHT:
                        mvtactuel=mvt[DROITE];
                        deplacement(carte,&posimario,DROITE);
                        break;

                }
                break;

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

    SDL_EnableKeyRepeat(0,0);

    SDL_FreeSurface(mure);
    SDL_FreeSurface(fin);
    SDL_FreeSurface(mvtactuel);
    SDL_FreeSurface(bravo);
    for (i=0;i<4;i++)
    {
        SDL_FreeSurface(mvt[i]);
    }





}
void deplacement(int carte[][haut_box],SDL_Rect *pos,int direction)
{
    switch(direction)
    {
        case HAUT:
            if(pos->y -1 < 0)
                break;
            if(carte[pos->x][pos->y -1]==MUR)
                break;
            if(carte[pos->x][pos->y -1]==VIDE || carte[pos->x][pos->y -1]==FIN)
                pos->y=pos->y - 1 ;
                break;

        case BAS:
            if(pos->y +1 > 11)
                break;
            if(carte[pos->x][pos->y +1]==MUR)
                break;
            if(carte[pos->x][pos->y +1]==VIDE || carte[pos->x][pos->y +1]==FIN)
                pos->y=pos->y + 1 ;
                break;
        case GAUCHE:
            if(pos->x -1 < 0)
                break;
            if(carte[pos->x - 1][pos->y]==MUR)
                break;
            if(carte[pos->x -1 ][pos->y ]==VIDE || carte[pos->x -1 ][pos->y ]==FIN )
                pos->x=pos->x - 1 ;
                break;
        case DROITE:
            if(pos->x +1 > 11)
                break;
            if(carte[pos->x + 1][pos->y]==MUR)
                break;
            if(carte[pos->x + 1][pos->y]==VIDE || carte[pos->x + 1][pos->y]==FIN )
                pos->x=pos->x + 1 ;
                break;

    }

}

void remplir(int *carte[][haut_box])
{
    int i=0,j=0;
    for(i=0;i<lar_box;i++)
        carte[i][0]=1;
    carte[1][0]=0;

    for(j=0;j<haut_box;j++)
        carte[0][j]=1;
    carte[0][5]=0;

    for(i=0;i<lar_box;i++)
        carte[i][11]=1;
    carte[9][11]=0;

    for(j=0;j<haut_box;j++)
        carte[11][j]=1;
    carte[11][2]=0;

    carte[5][1]=1;
    carte[7][1]=1;
    carte[9][1]=1;
    carte[10][1]=1;
    carte[11][1]=1;
    carte[2][2]=1;
    carte[3][2]=1;
    carte[7][2]=1;
    carte[3][3]=1;
    carte[5][3]=1;
    carte[9][3]=1;
    carte[10][3]=1;
    carte[1][4]=1;
    carte[4][4]=1;
    carte[5][4]=1;
    carte[6][4]=1;
    carte[8][4]=1;
    carte[9][4]=1;
    carte[2][5]=1;
    carte[5][5]=1;
    carte[9][5]=1;
    carte[3][6]=1;
    carte[2][6]=1;
    carte[6][6]=1;
    carte[9][6]=1;
    carte[4][7]=1;
    carte[7][7]=1;
    carte[1][8]=1;
    carte[2][8]=1;
    carte[5][8]=1;
    carte[7][8]=1;
    carte[8][8]=1;
    carte[9][8]=1;
    carte[5][9]=1;
    carte[1][0]=1;
    carte[0][5]=1;
    carte[11][1]=FIN;
    carte[10][11]=1;
    carte[9][11]=1;
    carte[10][3]=0;
    carte[5][1]=0;
    carte[7][1]=0;
    carte[9][1]=0;
    carte[10][1]=0;
    carte[11][2]=1;
    carte[6][9]=0;
    carte[7][8]=0;
    carte[8][9]=0;
    carte[5][9]=0;
    carte[2][6]=0;
    carte[2][10]=1;
    carte[4][10]=1;
    carte[6][10]=1;
    carte[9][2]=1;
    carte[4][9]=0;
    carte[7][2]=1;
    carte[5][2]=1;
    carte[9][4]=0;
    carte[8][4]=0;
    carte[9][9]=1;
    carte[7][4]=1;





}
