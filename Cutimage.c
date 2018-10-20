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
		while(IsThisLineGood(line,img) == 1 && line < maxline)
		{
			printf("going down m8\n");
			howlong++;
			line++;
		}
		int smallestspace = 0;
		int oldclosest = 0;
		int oldfurthest = img -> image -> w;
		int keep = howlong;
		while(howlong > 0)
		{
			printf("fuck boi i m going back up  %d \n",line);
			List* blackbits = arrToBoundList(img,line);
			printf("i have no idea");
			int closest = blackbits -> first -> data2;
			if(closest > oldclosest)
			{
				oldclosest = closest;
			}
			while(blackbits -> first -> next != NULL)
			{
				printf("wow you re good\n");
				blackbits -> first = blackbits -> first -> next;
			}
			int furthest = blackbits -> first -> data1;
			if(furthest > oldfurthest)
			{
				oldfurthest = furthest;
			}
			howlong--;
			line--;
			printf("OH DJADJA\n");
			WefounIt = 1;
		}
		if(WefounIt == 1)
		{
			i++;
			char buf[200];
			int newdimensionx = oldfurthest - oldclosest;
			int newdimensiony = keep - howlong;
			SDL_Rect *mynewrectangle;
			mynewrectangle -> x = oldclosest;
			mynewrectangle -> y = howlong;
			mynewrectangle -> w = newdimensionx;
			mynewrectangle -> h = newdimensiony;
			SDL_Rect *destination;
			destination -> x = 0;
			destination -> y = 0;
			destination -> w = newdimensionx;
			destination -> y = newdimensiony;
			SDL_Surface *Myresult = SDL_CreateRGBSurface(0,newdimensionx,newdimensiony,32,0,0,0,0);
			SDL_BlitSurface(img -> image,mynewrectangle ,Myresult ,destination);
			sprintf(buf, "line_%d.bmp", i);
			SDL_SaveBMP(Myresult,buf);
			WefounIt = 0;
		}

		line += keep + 1;
		//save
	}
}




