#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <gtk/gtk.h>
#include "app.h"
#include "surface.h"
#include "cut.h"
#include "color.h"
#include "NeuralNet.h"
#include "text.h"
#include "resize.h"
#include "Save.h"

GObject * app_get_ui_element(App * app, const gchar *name)
{
	const gchar *s;
	GSList *list;
	GObject *res = NULL;
	list =  app -> objects;

	do{
			s = gtk_buildable_get_name(list -> data);
			if(strcmp(s, name) == 0)
			{
				res = list -> data;
			}
	}while((list = g_slist_next(list)));

	return res;
}

void app_init (App * app)
{
    GError *err = NULL;
    app->definitions = gtk_builder_new ();
    gtk_builder_add_from_file (app->definitions,UI_DEFINITIONS_FILE, &err);
    
    if (err != NULL) 
	{
		g_printerr("Error while loading app definitions file: %s\n",err->message);
		g_error_free (err);
		gtk_main_quit ();
	}
	gtk_builder_connect_signals (app->definitions, app);
    app->objects = gtk_builder_get_objects (app->definitions);

//initialise stuff here
}

int loadimg(int ar, char* argv2[])
{
	gtk_init(&ar, &argv2);
	GtkWidget *window, *image;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"delete_event",G_CALLBACK(gtk_main_quit),NULL);

	image = gtk_image_new_from_file("test.bmp");
	gtk_container_add(GTK_CONTAINER(window),image);
	gtk_widget_show_all(window);



	gtk_main();
	return 0;
}

//handlers

void quitbutton()
{
	gtk_main_quit();
}

void gobutton(GtkButton *button, App *app)
{
	*button = *button;
	GET_UI_ELEMENT(GtkEntry, entry1);
	GET_UI_ELEMENT(GtkEntry, output1);
	GET_UI_ELEMENT(GtkEntry, entry2);
	const gchar *word = gtk_entry_get_text(entry1);
	const gchar *ratio = gtk_entry_get_text(entry2);
	char ch[120];
	char num[120];
	sprintf(num,"%s",ratio);
	sprintf(ch, "%s", word);
	printf("%f",atof(num));
	SDL_Surface *surf = LoadImage(ch);
	surf = greyScale(surf);
	surf = blackAndWhite(surf, 0.5);
    saveSurfaceAsBMP(surf, 0, 0);
	int n = cut(surf);
    char *str = malloc(sizeof(char) * (n + 3));
	int array[] = {900, 100, 63};
	network *net= network_init(array, 3);
    str = rebuild(n, str, net);
	gtk_entry_set_text(output1, str);
}

