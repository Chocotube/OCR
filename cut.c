#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"
#include "resize.h"

int cut(SDL_Surface *surf)
{
    int verLen = surf->h;
    int *ver = malloc(sizeof(int) * verLen);
    binVerArray(surf, ver);
    int verfirst = 0;
    int verlast = 0;
    int i = 0;
    while (i < verLen && ver[i] == 0)
    {
        i++;
    }
    verfirst = i;
    while (i < verLen && ver[i] != 0)
    {
        i++;
    }
    verlast = i;
    SDL_Surface *line = cropSurf(surf, makeRectangle(0, verfirst, surf->w, verlast-verfirst));



    int horLen = line->w;               //Initialize variables
    int *hor = malloc(sizeof(int) * horLen);
    binHorArray(line, hor);
    int horfirst = 0, horlast = 0;
    i = 0;
    int space;


    while (i < horLen && hor[i] == 0)      //Go to first black pixel
    {
        i++;
    }
    horfirst = i;

    int spacings1 = 0, spacings2 = 0;                //Define spacing
    int j = i;
    while (j < horLen && hor[j] != 0)
    {
        j++;
    }
    while (j < horLen && hor[j] == 0)
    {
        j++;
        spacings1++;
    }
    while (spacings1 * 2 >= spacings2 && j < horLen)
    {
        spacings2 = 0;
        while (j < horLen && hor[j] != 0)
        {
            j++;
        }
        while (j < horLen && hor[j] == 0)
        {
            j++;
            spacings2++;
        }
    }
    int spacing;
    spacing = (spacings1 + spacings2);


    binHorArray(surf, hor);
    horfirst = 0, horlast = 0;
    i = 0;

    while (i < horLen && hor[i] == 0)      //Go to first black pixel
    {
        i++;
    }
    horfirst = i;

    int n = 0;
    int hasText = 1;
    while (i < horLen && hasText)                      //Find bloc
    {
        space = 0;                                  //Find horizontal bounds
        hasText = 0;
        while (i < horLen && hor[i] != 0)
        {
            i++;
            horlast = i;
            hasText = 1;
        }
        while (space < spacing && i < horLen && hor[i] == 0)
        {
            space++;
            i++;
        }
        if ((space >= spacing || i >= horLen) && hasText)        //Find vertical bounds
        {
            binVerArray(surf, ver);
            verfirst = 0, verlast = 0;
            int j = 0;
            while (j < verLen && ver[j] == 0)
            {
                j++;
            }
            verfirst = j;
            while (j < verLen)
            {
                if (ver[j] != 0)
                    verlast = j;
                j++;
            }
            n = cutLines(cropSurf(surf, makeRectangle(horfirst, verfirst, horlast-horfirst, verlast-verfirst)), n);
            n++;
            saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 30, 30, 32, 0, 0, 0, 0), n, 3);
            horfirst = i;
            while (i < horLen && hor[i] == 0)
            {
                i++;
                horfirst++;
            }
        }
    }
    free(hor);
    free(ver);
    return n;
}

int cutLines(SDL_Surface *surf, int n)
{
    int verLen = surf->h;
    int *ver = malloc(sizeof(int) * verLen);
    binVerArray(surf, ver);
    int last = 0;
    int i = 0;
    while (i < verLen)
    {
        int hasText = 0;
        while (i < verLen && ver[i] == 0)
        {
            i++;
        }
        int first = i;
        while (i < verLen && ver[i] != 0)
        {
            i++;
            last = i;
            hasText = 1;
        }
        if (hasText)
        {
            n = cutWords(cropSurf(surf, makeRectangle(0, first, surf->w, last-first)), n);
            n++;
            saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 30, 30, 32, 0, 0, 0, 0), n, 2);
        }
    }
    free(ver);
    return n;
}

int cutWords(SDL_Surface *surf, int n)
{
    int horLen = surf->w;
    int *hor = malloc(sizeof(int) * horLen);
    binHorArray(surf, hor);
    int first = 0;
    int last = 0;
    int i = 0;


    int spacings[2] = {0,0};                //Define spacing
    int j = 0;
    while (j < horLen && hor[j] == 0)      //Go to first black pixel
    {
        j++;
    }
    first = j;
    while (j < horLen && hor[j] != 0)
    {
        j++;
    }
    while (j < horLen && hor[j] == 0)
    {
        j++;
        spacings[0]++;
    }
    while (spacings[0] * 3 >= spacings[1] && j < horLen)
    {
        spacings[1] = 0;
        while (j < horLen && hor[j] != 0)
        {
            j++;
        }
        while (j < horLen && hor[j] == 0)
        {
            j++;
            spacings[1]++;
        }
    }
    int spacing;
    if (j == horLen)
        spacing = spacings[0]*2;
    else
        spacing = (spacings[0] + spacings[1])/2;

    while (i < horLen)
    {
        int space = 0;
        while (i < horLen && hor[i] != 0)
        {
            i++;
            last = i;
        }
        while (space < spacing && i < horLen && hor[i] == 0)
        {
            space++;
            i++;
        }
        if (space >= spacing || i >= horLen)        //Find vertical bounds
        {
            n = cutLetters(cropSurf(surf, makeRectangle(first, 0, last-first, surf->h)), n);
            n++;
            saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 100, 100, 32, 0, 0, 0, 0), n, 1);
            first = i;
            while (i < horLen && hor[i] == 0)
            {
                i++;
                first++;
            }
        }
    }
    free(hor);
    return n;
}

int cutLetters(SDL_Surface *surf, int n)
{
    int horLen = surf->w;
    int *hor = malloc(sizeof(int) * horLen);
    binHorArray(surf, hor);
    int last = horLen;
    int i = 0;
    while (i < horLen)
    {
        while (i < horLen && hor[i] == 0)
        {
            i++;
        }
        int first = i;
        while (i < horLen && hor[i] != 0)
        {
            i++;
            last = i;
        }
        n++;
        saveSurfaceAsBMP(resize(eatBlank(cropSurf(surf, makeRectangle(first, 0, last-first, surf->h))), 30, 30), n, 0);
    }
    free(hor);
    return n;
}

SDL_Surface *eatBlank(SDL_Surface *surf)
{
    int horLen = surf->w;
    int *hor = malloc(sizeof(int) * horLen);
    binHorArray(surf, hor);
    int verLen = surf->h;
    int *ver = malloc(sizeof(int) * verLen);
    binVerArray(surf, ver);
    int horfirst = 0, horlast = 0, verfirst = 0, verlast = 0;
    int i = 0;
    while (i < horLen && hor[i] == 0)
    {
        i++;
    }
    horfirst = i;
    while (i < horLen)
    {
        i++;
        if (hor[i] != 0)
            horlast = i;
    }
    i = 0;
    while (i < verLen && ver[i] == 0)
    {
        i++;
    }
    verfirst = i;
    while (i < verLen)
    {
        i++;
        if (ver[i] != 0)
            verlast = i;
    }
    return cropSurf(surf, makeRectangle(horfirst, verfirst, horlast-horfirst, verlast-verfirst));
}
