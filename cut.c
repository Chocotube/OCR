#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"

void cut(SDL_Surface *surf)
{
    int horLen = surf->w;               //Initialize variables
    int hor[horLen];
    binHorArray(surf, hor);
    int horfirst = 0, horlast = horLen;
    int i = 0;
    int space;


    while (i < horLen && hor[i] == 0)      //Go to first black pixel
    {
        i++;
    }
    horfirst = i;


    int spacings[2] = {0,0};                //Define spacing
    int test = 0;
    int j = i;
    while (test < 2 || (spacings[0] >= spacings[1] && j < horLen))
    {
        if (spacings[0]*2 >= spacings[1])
        {
            test = 1;
            spacings[1] = 0;
        }
        while (j < horLen && hor[j] != 0)
        {
            j++;
        }
        while (j < horLen && hor[j] == 0)
        {
            j++;
            spacings[test]++;
        }
        test++;
    }
    int spacing = (spacings[0] + spacings[1]);


    while (i < horLen)                      //Find bloc
    {
        space = 0;                                  //Find horizontal bounds
        while (i < horLen && hor[i] != 0)
        {
            i++;
            horlast = i;
        }
        while (space < spacing && i < horLen && hor[i] == 0)
        {
            space++;
            i++;
        }
        if (space >= spacing || i >= horLen)        //Find vertical bounds
        {
            int verLen = surf->h;
            int ver[verLen];
            binVerArray(surf, ver);
            int verfirst = 0, verlast = horLen;
            int i = 0;
            while (i < verLen && ver[i] == 0)
            {
                i++;
            }
            verfirst = i;
            while (i < verLen)
            {
                if (ver[i] != 0)
                    verlast = i;
                i++;
            }
            cutLines(cropSurf(surf, makeRectangle(horfirst, verfirst, horlast-horfirst, verlast-verfirst)));
        }
    }
}

int cutLines(SDL_Surface *surf)
{
    int verLen = surf->h;
    int ver[verLen];
    binVerArray(surf, ver);
    int last = verLen;
    int i = 0;
    int n = 0;
    while (i < verLen)
    {
        while (i < verLen && ver[i] == 0)
        {
            i++;
        }
        int first = i;
        while (i < verLen && ver[i] != 0)
        {
            last = i;
            i++;
        }
        n = cutWords(cropSurf(surf, makeRectangle(0, first, surf->w, last-first)));
        saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 30, 30, 32, 256, 0, 0, 0), n);
    }
    return n;
}

int cutWords(SDL_Surface *surf)
{
    int horLen = surf->w;
    int hor[horLen];
    binHorArray(surf, hor);
    int first = 0;
    int last = horLen;
    int i = 0;
    int n = 0;


    int spacings[2] = {0,0};                //Define spacing
    int test = 0;
    int j = 0;
    while (test < 2 || (spacings[0] >= spacings[1] && j < horLen))
    {
        if (spacings[0]*2 >= spacings[1])
        {
            test = 1;
            spacings[1] = 0;
        }
        while (j < horLen && hor[j] != 0)
        {
            j++;
        }
        while (j < horLen && hor[j] == 0)
        {
            j++;
            spacings[test]++;
        }
        test++;
    }
    int spacing = (spacings[0] + spacings[1])/2;

    int space = 0;
    while (i < horLen)
    {
        while (i < horLen && hor[i] != 0)
        {
            last = i;
            i++;
        }
        while (space < spacing && i < horLen && hor[i] == 0)
        {
            space++;
            i++;
        }
        if (space >= spacing || i >= horLen)        //Find vertical bounds
        {
            n = cutLetters(cropSurf(surf, makeRectangle(first, 0, last-first, surf->h)), n);
            saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 30, 30, 32, 0, 0, 0, 0), n);
        }
    }
    return n;
}

int cutLetters(SDL_Surface *surf, int n)
{
    int verLen = surf->h;
    int ver[verLen];
    binVerArray(surf, ver);
    int last = verLen;
    int i = 0;
    while (i < verLen)
    {
        while (i < verLen && ver[i] == 0)
        {
            i++;
        }
        int first = i;
        while (i < verLen && ver[i] != 0)
        {
            last = i;
            i++;
        }
        saveSurfaceAsBMP(cropSurf(surf, makeRectangle(0, first, surf->w, last-first)), i);
    }
    return n+i;
}
