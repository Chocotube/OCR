#ifndef GREY_H
#define GREY_H

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putPixel(SDL_Surface *surface,int x, int y, Uint32 pixel);
SDL_Surface* greyScale(SDL_Surface *surf);
SDL_Surface* blackAndWhite(SDL_Surface *surf,float ratio);

#endif
