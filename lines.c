#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "lines.h"
#include "grey.h"

/* 
 
    Déclaration et initiation :
    *ptr = NULL ou &variable
    
    Ailleur :
    ptr  : adresse de la variable pointée
    *ptr : valeur de  la variable pointée
    &ptr : adresse du pointeur
 
 
 */

/*
Element* createElement(int data1, int data2)
{
    Element* element = malloc(sizeof(Element));
    
    if (element != NULL)
    {
        element->data1 = data1;
        element->data2 = data2;
        //printf("1first = %d\n", element->data1);
        //printf("1last = %d\n", element->data2);
        element->next =  NULL;
    }
    
    return element;
}


List* createList()
{
    List *list = malloc(sizeof(List));
    
    if (list != NULL)
        list->first = NULL;
    return list;
}

void insertHead(List *list, Element *element)
{
    if (list == NULL || element == NULL)
        return;
    
    if (list->first != NULL)
    {
    //printf("3first = %d\n", list->first->data1);
    //printf("3last = %d\n", list->first->data2);
    }
    element->next = list->first;
    list->first = element;
    if (element->next != NULL)
    {
        //printf("first = %d\n", element->next->data1);
        //printf("last = %d\n", element-> next->data2);
    }
    else
	{
        //printf("null\n");
	}
}

List* arrToBoundList(imageData *img, int y)
{
    List *res = createList();
	
	int x = (img -> image -> w);

	int i = x - 1, first = 0, last = 0;
    while (i > 0)
	{
		int pxl = (int)getpixel(img -> image,i,y);
		
		if (pxl == 4294967295)
		{
			printf("FOUND line : %d",y);
			last = i;
			while (i > 0 && pxl == 4294967295)
            {
				pxl = getpixel(img -> image,i,y);
                i--;
            }
            first = i + 1;
            
            insertHead(res, createElement(first, last));
        }
        i--;
    }
    return res;
}
*/
//int main()
//{
    /*  
    int arr[21] = {1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,0};
    List* list = arrToBoundList(arr, 21);*/
    /*int a0[2] = {2, 6};
    int *a1 = a0;
    printf("[%d, %d] \n", a1[0], a1[1]);
    Element* element = createElement(a1);
    int a = element->data[0];
    int b = element->data[1];
    printf("[%d, %d] -> ", a, b);*/
    /*
    Element* element = list->first;
    
    printf("2first = %d\n", element->next->data1);
    printf("2last = %d\n", element->next->data2);
    while(element != NULL)
    {
        int a = element->data1;
        int b = element->data2;
        printf("[%d, %d] -> ", a, b);
        element = element->next;
    }
    printf("NULL\n");
    */
  //  return 0;
//}
