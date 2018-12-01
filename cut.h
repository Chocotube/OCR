#ifndef CUT_H
#define CUT_H

void cut(SDL_Surface *surf);
int cutLines(SDL_Surface *surf, int n);
int cutWords(SDL_Surface *surf, int n);
int cutLetters(SDL_Surface *surf, int n);
SDL_Surface *eatBlank(SDL_Surface *surf);

#endif
