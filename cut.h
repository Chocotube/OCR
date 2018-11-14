#ifndef CUT_H
#define CUT_H

void cut(SDL_Surface *surf);
int cutLines(SDL_Surface *surf);
int cutWords(SDL_Surface *surf);
int cutLetters(SDL_Surface *surf, int n);

#endif