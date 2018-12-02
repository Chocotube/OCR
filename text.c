#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include <string.h>
#include "text.h"
#include "surface.h"

char findChar(char path[])
{
    while (path[i] != "\0" && path[i] != "_")
    {
        i++;
    }
    if (path[i] == "_")
    {
        char type = path[i+1];
        if (type == "l")
            res = ocr_neuralnet(net, 
        else if (type == "s")
            res = " ";
        else if (type == "r")
            res = "\n";
        else if (type == "b")
            res = "\n\n\n";
        
    return "c";
}

int rebuild(int n, int max)
{
    char *array[] = malloc(sizeof(char) * n * sizeof(char) * max);
    struct dirent *de;
    DIR *dr = opendir("./Letters");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }
    int i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        array[i] = de->d_name;
        i++;
    }
    sort(array, n);
    closedir(dr);
    return 0;
}

static int myCompare (const void * a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}

void sort(const char *arr[], int n) 
{
    qsort (arr, n, sizeof (const char *), myCompare);
}
