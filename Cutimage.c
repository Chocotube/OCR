#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "lines.h"


int IsThisLineGood(int line ,imageData *img)
{
	int res = 0;
	List* tst = arrToBoundList(img,line);
	if (tst != NULL)
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
}



void FindText(imageData *img)
{
	int line = 0;
	int maxline = img -> image -> h;
	while(line < maxline)
	{
		printf("hey\n");
		int i = 0;
		int WefounIt = 0;
		
		int howlong = 0;
		int start = line;
		while(IsThisLineGood(line,img) == 1 && line < maxline)
		{
			//printf("going down m8\n");
			howlong++;
			printf("%d\n",line);
			line++;
		}
		howlong--;
		line--;
		int smallestspace = 0;
		int oldclosest = 0;
		int oldfurthest = img -> image -> w;
		int keep = howlong;
		while(howlong >= 0)
		{
			//printf("fuck boi i m going back up  %d \n",line);
			List* blackbits = arrToBoundList(img,line);
			int closest = blackbits -> first -> data2;
			if(closest > oldclosest)
			{
				oldclosest = closest;
			}
			while(blackbits -> first -> next != NULL)
			{
				//printf("wow you re good\n");
				blackbits -> first = blackbits -> first -> next;
			}
			int furthest = blackbits -> first -> data1;
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
			
			//printf("%d ,oldclosest , %d oldfurthest ,%d, start , %d keep , %d , howlong",oldclosest,oldfurthest,start,keep,howlong);
			i++;
			int newdimensionx = oldfurthest - oldclosest;
			int newdimensiony = keep - howlong;

			CopyAndSaveText( img -> image, oldclosest, start, newdimensionx , newdimensiony, i);
			WefounIt = 0;

		}
		printf("%d",start);
		line += keep + 1;
		//save
	}
}








