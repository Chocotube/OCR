#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "Cutimage.h"
#include "CutLetter.h"



int IsBlankColonne(SDL_Surface *image,int colonne)
{
	int index = 0;
	int height = image -> h;
	while(index <= height && getpixel(image,colonne,index) > 0)
	{

		index++;
		printf("colonne %d,%d color : %d\n",colonne,index,getpixel(image,colonne,index));
	}
	if(index == height + 1)
	{
		printf("colonne %d is blank\n",colonne);
		return 1;
	}
	return 0;
}



int FindClosest2(SDL_Surface *image, int colonne)
{
	int index = 0;
	while(getpixel(image,colonne,index) > 0)
	{
		index++;
	}
	return index-1;
}



int FindFurthest2(SDL_Surface *image, int colonne)
{
	int height = image -> h;
	int index = height;
	while(getpixel(image,colonne,index) >  0)
	{
		index--;
	}
	return index+1;
}



void SaveLetter(SDL_Surface * image, int startx, int starty, int width, int height,int letterId, int LineNumber)
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


/*
void FindLetter(SDL_Surface *image, int line)
{
	int colonne = 0;
	int maxcolonne = image -> w;
	int i = 0;
	while(colonne < maxcolonne)
	{
		int WeFoundIt = 0;
		int howlong = 0;
		int start = colonne;
		int deep = 0;
		int go = 0;
		printf("Checkpoint 1 : %d\n",colonne);
		while(IsBlankColonne(image,colonne) == 0 && colonne < maxcolonne)
		{
			printf("going up at %d\n",colonne);
			howlong++;
			colonne++;
			deep++;
			go = 1;
		}



		//deep--;
		//howlong--;
		//colonne--;
		
		int oldfurthest = 0;
		int oldclosest = image -> h;
		int keep = howlong;

		while(howlong >= 0)
		{
			printf("goin down at %d\n",colonne);
			int closest = FindClosest2(image,colonne);
			if(closest < oldclosest)
			{
				oldclosest = closest;
			}

			int furthest = FindFurthest2(image,colonne);
			if(furthest > oldfurthest)
			{
				oldfurthest = furthest;
			}
			howlong--;
			colonne--;
			WeFoundIt = 1;
		}

		howlong++;
		colonne++;
		
		printf("Checkpoint2 : %d\n",colonne);
		if(WeFoundIt ==1)
		{
			
			i++;
			int newdimensiony = oldfurthest - oldclosest;
			int newdimensionx = keep - howlong;
			printf("howlong %d, oldclosest %d , newdimensionx %d, newdimensiony, %d\n",keep,oldclosest,newdimensionx,newdimensiony);
			SaveLetter(image, start, oldfurthest, newdimensionx, newdimensiony, line, i);
			WeFoundIt = 0;
		}
		if(go == 0)
		{
			deep = 1;
		}
		colonne += deep;
	}
}*/
void FindLetter(SDL_Surface *image , int line)
{
	int colonne = 0;
	int maxcolonne = image -> w;
	int letterId = 0;
	while(colonne < maxcolonne)
	{
		while(IsBlankColonne(image,colonne) == 1 && colonne < maxcolonne)
		{
			colonne++;
		}
		if(colonne != maxcolonne)
		{
			int start = colonne;
			while(IsBlankColonne(image,colonne) == 0 && colonne < maxcolonne)
			{
				colonne++;
			}
			int yndex = start;
			int closestbot = image -> h;
			int closesttop = 0;
			while(yndex != colonne)
			{
				printf("closesttop %d , closestbot %d \n",closesttop,closestbot);
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
				printf("closesttop1 %d , closestbot1 %d \n",closesttop1,closestbot1);
			}
			int width = colonne - start;
			int height = closesttop - closestbot;
			printf("hello");
			SaveLetter(image,start,closestbot,width,height,line,letterId);
			letterId++;
		}



















}









}

