#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "Cutimage.h"
#include "CutLetter.h"


//We check if the column is blank or not
int IsBlankColonne(SDL_Surface *image,int colonne)
{
	int index = 0;
	int height = image -> h;
	while(index <= height && getpixel(image,colonne,index) > 0)
	{

		index++;

	}
	if(index == height + 1)
	{
		return 1;
	}
	return 0;
}


//We find the lowest pixel in the letter
int FindClosest2(SDL_Surface *image, int colonne)
{
	int index = 0;
	while(getpixel(image,colonne,index) > 0)
	{
		index++;
	}
	return index - 1;
}


//We find the highest pixel in the letter
int FindFurthest2(SDL_Surface *image, int colonne)
{
	int height = image -> h;
	int index = height;
	while(getpixel(image,colonne,index) >  0)
	{
		index--;
	}
	return index + 1;
}


//Function that will save the letter simular proces as in Cutimage
void SaveLetter(SDL_Surface * image, int startx, int starty,
int width, int height,int letterId, int LineNumber)
{
	SDL_Surface *Result;
	char buf[200];

	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	sprintf(buf, "line_%d_%d.bmp", letterId, LineNumber);

	SDL_SaveBMP(Result,buf);
}


//Function that will Find the letter and sends it for chopping
void FindLetter(SDL_Surface *image , int line)
{
//letterID is the letter number colonne is the column
	int colonne = 0;

//maxcolonne is the width of the line
	int maxcolonne = image -> w;
	int letterId = 0;
	while(colonne < maxcolonne)
	{
		while(IsBlankColonne(image,colonne) == 1 && colonne < maxcolonne)
		{
			colonne++;
//Basicly this while the collumn is all white we iterate
		}
		if(colonne != maxcolonne)
		{
//aslong as we are not at the end of the line we HAVE FOUND A LETTER !
			int start = colonne;
//We rememeber where we started
			while(IsBlankColonne(image,colonne) == 0 && colonne < maxcolonne)
			{
//We iterate the columns that have black
				colonne++;
			}
			int yndex = start;
//Simular to find line we are going to find the furthest and the closest
//black pixel so we have them as reference for the cutting
			int closestbot = image -> h;
			int closesttop = 0;
			while(yndex != colonne)
			{

				int closesttop1 = FindFurthest2(image,yndex);
				int closestbot1 = FindClosest2(image,yndex);
				if(closesttop < closesttop1)
				{
					closesttop = closesttop1;
				}
				if(closestbot > closestbot1)
				{
					closestbot = closestbot1;
				}
				yndex++;

			}
			int width = colonne - start;
			int height = closesttop - closestbot;
//We have the letter and iterate the letterID
			SaveLetter(image,start,closestbot,width,height,line,letterId);
			letterId++;
		}



















}









}

