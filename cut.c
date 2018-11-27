#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"

void cut(SDL_Surface *surf)
{
    int horLen = surf->w;               //Initialize variables
    int *hor = malloc(sizeof(int) * horLen);
    for (int i = 0; i < horLen; i++)
    {
        hor[i] = 0;
    }
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
        if (test == 2 && spacings[0]*2 >= spacings[1])
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
    printf("\n[%d, %d] = %d\n", spacings[0], spacings[1], spacing);

    int n = 0;
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
            int *ver = malloc(sizeof(int) * verLen);
            for (int j = 0; j < verLen; j++)
            {
                ver[j] = 0;
            }
            printf("len = %d\n", verLen);
            binVerArray(surf, ver);
            int verfirst = 0, verlast = verLen;
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
            printf("\nDone bloc : i = %d\n", i);
            n = cutLines(cropSurf(surf, makeRectangle(horfirst, verfirst, horlast-horfirst, verlast-verfirst)), n);
            n++;
        }
    }
    printf("\nDone bloc FINAL\n");
}

int cutLines(SDL_Surface *surf, int n)
{
    int verLen = surf->h;
    int *ver = malloc(sizeof(int) * verLen);
    for (int j = 0; j < verLen; j++)
    {
        ver[j] = 0;
    }
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
            i++;
            last = i;
        }
        printf("\nDone line : n = %d\n", n);
        n = cutWords(cropSurf(surf, makeRectangle(0, first, surf->w, last-first)));
        n++;
        saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 100, 100, 32, 255, 255, 255, 0), n);
    }
    printf("\nDone line FINAL\n");
    return n;
}

int cutWords(SDL_Surface *surf, int n)
{
    int horLen = surf->w;
    printf("len = %d\n", horLen);
    int *hor = malloc(sizeof(int) * horLen);
    for (int i = 0; i < horLen; i++)
    {
        hor[i] = 0;
    }
    binHorArray(surf, hor);
    int first = 0;
    int last = horLen;
    int i = 0;
    int n = 0;


    int spacings[2] = {0,0};                //Define spacing
    int j = 0;
    while (j < horLen && hor[j] != 0)
    {
        j++;
    }
    while (j < horLen && hor[j] == 0)
    {
        j++;
        spacings[0]++;
    }
    while (spacings[0] * 2 >= spacings[1] && j < horLen)
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
    printf("\n[%d, %d] = %d\n", spacings[0], spacings[1], spacing);


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
            printf("\nDone word : n = %d\nBounds = (%d, %d)\n", n, first, last);
            n = cutLetters(cropSurf(surf, makeRectangle(first, 0, last-first, surf->h)), n);
            n++;
            saveSurfaceAsBMP(SDL_CreateRGBSurface( 0, 100, 100, 32, 0, 0, 0, 0), n);
        }
    }
    printf("\nDone word FINAL\n");
    return n;
}

int cutLetters(SDL_Surface *surf, int n)
{
    int horLen = surf->w;
    int *hor = malloc(sizeof(int) * horLen);
    for (int j = 0; j < horLen; j++)
    {
        hor[j] = 0;
    }
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
        printf("\nDone letter : n = %d\nBounds = (%d, %d)\n", n, first, last);
        saveSurfaceAsBMP(cropSurf(surf, makeRectangle(first, 0, last-first, surf->h)), i);
    }
    printf("\nDone letter FINAL\n");
    return n;
}
