#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"
#include "color.h"
#include "NeuralNet.h"
#include "text.h"
#include "resize.h"
#include "app.h"

int main(int argc, char *argv[])
{
    int res = 0;
	if (argc != 3)
    {
        printf("main: usage: path black_and_white_ratio\n");
        res = 1;
    }
	App *app;
	app = (App *) g_new(App,1);
	gtk_init(&argc,&argv);
	app_init(app);
	GET_UI_ELEMENT(GtkWidget, window1);
	gtk_widget_show_all(window1);
	gtk_main();


/*
    SDL_Surface *surf = LoadImage(argv[1]);
	surf = greyScale(surf);
    float ratio = atof(argv[2]);
	surf = blackAndWhite(surf, ratio);
    saveSurfaceAsBMP(surf, 0, 0);
	int n = cut(surf);
    char *str = malloc(sizeof(char) * n);
    str = rebuild(n, str);;
	return res;
    free(str);*/
	return res;
}
