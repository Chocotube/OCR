#ifndef SURF_H
#define SURF_H

int surfToHorArray(SDL_Surface surf);
int surfToVerArray(SDL_Surface surf);
int arrayBound(int arr);
SDL_Surface surfCropper(SDL_Surface surf, SDL_Rect crop);

#endif
