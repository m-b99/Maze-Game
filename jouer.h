#ifndef JOUER_H_INCLUDED
#define JOUER_H_INCLUDED

void jouer(SDL_Surface *ecran);
void deplacement(int carte[][haut_box],SDL_Rect *pos,int direction);
void remplir(int *carte[][haut_box]);


#endif // JOUER_H_INCLUDED
