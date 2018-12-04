#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include <string.h>
#include "text.h"
#include "surface.h"
#include "NeuralNet.h"
#include "Training.h"

char findChar(char path[], network *net)
{
    char res;
    int i = 0;
    while (path[i] != '\0' && path[i] != '_')
    {
        i++;
    }
    if (path[i] == '_')
    {
        char type = path[i+1];
        if (type == 'l')
        {
            double array[900];
            char *filePath = malloc(len(path) * sizeof(char *) + 10 * sizeof(char));
            sprintf(filePath, "./Letters/%s", path);
            puts(filePath);
            surfToArr(LoadImage(filePath), array);
            res = bmpToChar(net, array);
        }
        else if (type == 's')
            res = ' ';
        else if (type == 'r')
            res = '\n';
        else if (type == 'b')
            res = '\n';
    }
    return res;
}

char* rebuild(int n, char *res, network *net)
{
    char *array[n+3];
    struct dirent *de;
    DIR *dr = opendir("./Letters");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
    }
    int i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        array[i] = de->d_name;
        i++;
    }
    sort(array, n+3);
    int j = 0;
    for (int i = 3; i < n; i++)
    {
        res[j] = findChar(array[i], net);
        j++;
    }
    closedir(dr);
    return res;
}

void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void sort(char **m, int dim)
{
    int i, j, flag=1;

    for(i=0; i<dim-1 && flag==1; i++)
    {
        flag=0;
        for(j=0; j<dim-1; j++)
        {
            if(strcmp(m[j],m[j+1])>0)
            {
                swap(&m[j],&m[j+1]);
                flag=1;
            }
        }
    }
}
