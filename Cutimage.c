#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "lines.h"
#include "CutLetter.h"

int IsThisLineGood(int line ,imageData *img)
{
	int res = 0;
	List* tst = arrToBoundList(img,line);
	if (tst -> first != NULL)
	{
		res = 1;
	}
	return res;
}

SDL_Rect MakeARectangle(int x ,int y, int w, int h)
{
	SDL_Rect res;
	res.x = x;
	res.y = y;
	res.w = w;
	res.h = h;
	return res;
}

int IsBlankLine(SDL_Surface *image,int line)
{
	int index = 0;
	int width = image -> w;
	while (index <  width && getpixel(image,index,line) != 0)
	{
		index++;
	}
	if(index == width)
	{
		return 1;
	}
	return 0;
}

int FindClosest(SDL_Surface *image, int line)
{
	int index = 0;
	int width = image -> w;
	while(getpixel(image,index,line) != 0)
	{
		index++;
	}
	return index;
}

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


/*void CopyAndSaveText(SDL_Surface * image, int startx, int starty, int width, int height, int LineNumber)
{
	SDL_Surface *Result;
	char buf[200];

	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	SDL_Surface *new = Result;
	FindLetter(new, LineNumber);
}*/





void CopyAndSaveText(SDL_Surface * image, int startx, int starty, int width, int height, int LineNumber)
{
	printf("yes");
	SDL_Surface *Result;
	char buf[200];

	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	sprintf(buf,"line_%d.bmp",LineNumber);
	SDL_SaveBMP(Result,buf);
	SDL_Surface *new = Result;
	printf("hey");
	FindLetter(new, LineNumber);
}
/*
void CopyAndSaveText(SDL_Surface * image, int startx, int starty, int width, int height, int LineNumber)
{
	SDL_Surface *Result;
	char buf[200];

	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	sprintf(buf, "line_%d.bmp", LineNumber);

	SDL_SaveBMP(Result,buf);
}*/
void FindText(imageData *img)
{
	int line = 0;
	int maxline = img -> image -> h;
	int i = 0;
	while(line < maxline)
	{
		int WefounIt = 0;
		int howlong = 0;
		int start = line;
		int deep = 1;
		while(IsBlankLine(img -> image, line)  == 0 && line < maxline)
		{
			howlong++;
			deep++;
			line++;
		}
		

		howlong--;
		line--;
		int smallestspace = 0;
		int oldfurthest = 0;
		int oldclosest = img -> image -> w;
		int keep = howlong;
		
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
			i++;
			int newdimensionx = oldfurthest - oldclosest;
			int newdimensiony = keep - howlong;

			CopyAndSaveText( img -> image, oldclosest, start, newdimensionx , newdimensiony, i);
			WefounIt = 0;
			printf("yes");


		}
		
		line += deep;
	}
}








