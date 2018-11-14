#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"

void Loadimage(imageData *img)                                                //Opens an image and gives an sdl surface in the image data struct
{

    //SDL_Init(SDL_INIT_VIDEO);
    printf("%s","Bonjour mettez le nom du fichier que vous voulez ouvrir : ");      //Ask the path to the user
    scanf("%s",img -> path);

    //img -> window = SDL_CreateWindow(img -> path, SDL_WINDOWPOS_UNDEFINED,
    //SDL_WINDOWPOS_UNDEFINED,640,480,0);//Creates the window
    //img -> renderer = SDL_CreateRenderer(img -> window, -1, 0); //Creates
    //the renderer for the image

    img -> image = SDL_LoadBMP(img -> path);                                        //Loads the image
    /*img -> texture = SDL_CreateTextureFromSurface(img -> renderer, 
     * img -> image);//Puts the texture in the window
    if(img -> image = NULL) //If we can't find the image sdl will give an Error
    {
        printf("%s\n","Error :");
        SDL_GetError();
    }*/
}
/*
void Delimage(imageData *img) 
//This is the idle function and waits for the user to shut the image
{
    int end = 0;
    SDL_Event event;

    while (end == 0) //Waiting for user to do something
    {
        SDL_WaitEvent(&event);

        if(event.type == SDL_QUIT) //If the user wa
        nts to quit we destroy everything
        {
            end = 1;
        }
        SDL_RenderCopy(img -> renderer,img -> texture, NULL, NULL);
        SDL_RenderPresent(img -> renderer);
    }
    SDL_DestroyTexture(img -> texture);
    SDL_FreeSurface(img -> image);
    SDL_DestroyRenderer(img -> renderer);
    SDL_DestroyWindow(img -> window);

    SDL_Quit;
}*/

int getPixelRed(SDL_Surface *surf, x, y)                            //Returns the value of the red color of the pixel in position x y of the surf
{
    Uint32 pixel = surface->pixels[y * loadingSurface->w + x]
    Uint8 *colors = pixel;
    return colors[0];
}

void binVerArray(SDL_Surface *surf, int[] array)                   //Put the addition of red values of each line in array
{
    for (int i = 0; i < surf->h; i++)
    {
        for (int j = 0; j < surf->w; j++)
        {
            array[i] += getPixelRed(surf, i, j);
        }
    }
}

void binHorArray(SDL_Surface *surf, int[] array)                   //Put the addition of red values of each colone in array
{
    for (int i = 0; i < surf->w; i++)
    {
        for (int j = 0; j < surf->h; j++)
        {
            array[i] += getPixelRed(surf, i, j);
        }
    }
}

SDL_Rect makeRectangle(int x ,int y, int w, int h)                  //Returns an SDL_Rect with the given parametres
{
    SDL_Rect res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}

SDL_Surface* cropSurf(SDL_Surface surf, SDL_Rect crop)              //Return the surface cropped with the given rectangle
{
    SDL_Surface *res = SDL_CreateRGBSurface( 0, crop.w, crop.h, 32, 0, 0, 0, 0);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    SDL_BlitSurface(surf, &crop, res, &rect);
    return res;
}

void saveSurfaceAsBMP(SDL_Surface *surf, int name)                  //Saves the surface as a BMP named name.bmp
{
    char[sizeof(int) + 4 * sizeof(char)] strName;
    sprintf(strName, "%d.bmp", name);
    SDL_SaveBMP(surf, strName);
}