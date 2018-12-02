#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include <string.h>
#include "text.h"
#include "surface.h"

char findChar(char path[])
{
    char res = ' ';
    int i = 0;
    printf("\npath is : %s\n", path);
    while (path[i] != '\0' && path[i] != '_')
    {
        i++;
    }
    if (path[i] == '_')
    {
        char type = path[i+1];
        if (type == 'l')
            res = 'l';//ocr_neuralnet(net, surfToArr(LoadImage(path)));
        else if (type == 's')
            res = 's';
        else if (type == 'r')
            res = 'r';
        else if (type == 'b')
            res = 'b';
    }
    printf("char is : %c\n", res);
    return res;
}

void rebuild(int n, int max, char *res)
{
    char *array[n];
    struct dirent *de;
    DIR *dr = opendir("./Letters");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
    }
    int i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        puts(de->d_name);
        array[i] = de->d_name;
        i++;
    }
    sort(array, n);
    for (int i = 0; i < n; i++)
    {
        puts(array[i]);
    }
    for (int i = 0; i < n; i++)
    {
        *res = findChar(array[i]);
        printf("char is : %c\n", *res);
        res++;
    }
    closedir(dr);
    printf("%d\n", (int)&res);
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
