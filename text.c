#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include "text.h"
#include "surface.h"

char findChar(char path[])
{
    
    char type;
    return "c";
}

int rebuild(int n)
{
    
    struct dirent *de;  // Pointer for directory entry 
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("./Letters"); 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    {
        printf("Could not open current directory" );
        return 0;
    }
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
    closedir(dr);
    return 0;
}
