#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "CutLetter.h"


//This function makes an SDL rect with the coordonates of the top corner and 
//the width and height
SDL_Rect MakeARectangle(int x ,int y, int w, int h)
{
	SDL_Rect res;
	res.x = x;
	res.y = y;
	res.w = w;
	res.h = h;
	return res;
}


//Checks if the line is blanc
int IsBlankLine(SDL_Surface *image,int line)
{
	int index = 0;
	int width = image -> w;

//Aslong as we don't seee a black pixel we continue acccros the line
	while (index <  width && getpixel(image,index,line) != 0)
	{
		index++;
	}
	if(index == width)
	{
		//If we have crossed the line completly return 1 else 0
		return 1;
	}
	return 0;
}


//Function that finds the first black pixel starting from the start of the
//line
int FindClosest(SDL_Surface *image, int line)
{
	int index = 0;
	while(getpixel(image,index,line) != 0)
	{
		index++;
	}
	return index;
}


//Function that finds the furthest black pixel on a line
int FindFurthest(SDL_Surface *image, int line)
{
	int width = image -> w;
	int index = width - 1;
	while(getpixel(image,index,line) != 0)
	{
		index--;
	}
	return index + 1;
}


//Function that copies the line saves it and starts cutting out the letters
void CopyAndSaveText(SDL_Surface * image, int startx,
                     int starty, int width, int height, int LineNumber)
{
	SDL_Surface *Result;
	char buf[200];
	
	//We create the destination surface
	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	//We make our cut out
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	//We make our destination rectangle (same dimension as the cut out)
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	//We copy the rectangle to it's destination
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	//We give the name to the file of the line that we are going to save
	sprintf(buf,"line_%d.bmp",LineNumber);
	//We save the file
	SDL_SaveBMP(Result,buf);
	//We create a pointer pointing to this surface
	SDL_Surface *new = Result;
	//We go and cut out the letters
	FindLetter(new, LineNumber);
}


//Function that finds the lines
void FindText(imageData *img)
{

//we intialis ethe line number and the line iterator and get the images height
	int line = 0;
	int maxline = img -> image -> h;
	int i = 0;
	while(line < maxline) //We start going down the image
	{
		int WefounIt = 0;
//We found it is the variable that says if we have found a line
		int howlong = 0;
//Howlong will iterate the lenght of the line when we find one
		int start = line;
//start is to remember when we find a line
		int deep = 1;
//deep is the ultimate iterator the one that will say how far down when went
//each time we find a line$

//Whilst it's blank we will go down
		while(IsBlankLine(img -> image, line) == 0 && line < maxline)
		{
			howlong++;
			deep++;
			line++;
		}

//We go back on the howlong and line to point to the last line with black
//on it
		howlong--;
		line--;

//We use these two last variables to find the furthest black pixel
//and the closest black pixel so we can crop it correctly
		int oldfurthest = 0;
		int oldclosest = img -> image -> w;
		int keep = howlong;

//We go down the line and find the closest and the furthest black pixel
		while(howlong >= 0)
		{
			int closest = FindClosest(img -> image,line);

			if(closest < oldclosest)
			{
				oldclosest = closest;
			}

			int furthest = FindFurthest(img -> image,line);
			if(furthest > oldfurthest)
			{

				oldfurthest = furthest;
			}
			howlong--;
			line--;;
			WefounIt = 1;
		}

		howlong++;
		line++;

		if(WefounIt == 1)
		{
//We go and Copy and save the line and iterate the line number
			i++;
			int newdimensionx = oldfurthest - oldclosest;
			int newdimensiony = keep - howlong;
			CopyAndSaveText( img -> image, oldclosest, start,
                             newdimensionx , newdimensiony, i);
			WefounIt = 0;
		}
//We add the iteration to line
		line += deep;
	}
}








