#ifndef GREY_H
#define GREY_H

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface,int x, int y, Uint32 pixel);
void greyscale(imageData *img);
void BlackOrWhite(imageData *img,float ratio);

#endif
