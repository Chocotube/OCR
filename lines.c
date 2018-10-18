#include <stdio.h>
#include <stdlib.h>
#include "lines.h"

/* 
 
    Déclaration et initiation :
    *ptr = NULL ou &variable
    
    Ailleur :
    ptr  : adresse de la variable pointée
    *ptr : valeur de  la variable pointée
    &ptr : adresse du pointeur
 
 
 */


Element* createElement(int data[2])
{
    Element* element = malloc(sizeof(Element));
    
    if (element != NULL)
    {
        element->data[2] = *data;
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
    element->next = list->first;
    list->first = element;
}



List* arrToBoundList(int arr[], int len)
{
    List *res = createList();
	int i = len-1, first = 0, last = 0;
    while (i > 0)
	{
		if (arr[i] != 0)
		{
			last = i;
			while (arr[i] != 0)
            {
                i--;
            }
            first = i;
            int element[2] = {first, last};
            insertHead(res, createElement(element));
        }
        i--;
    }
    return res;
}

int main()
{
    //int arr[11] = {1,1,1,1,0,0,1,1,1,0,0};
    //List* list = arrToBoundList(arr, 11);
    int a1[2] = {2, 6};
    Element* element = createElement(a1);
    int a = element->data[0];
    int b = element->data[1];
    printf("[%d, %d] -> ", a, b);
    
    /*Element* element = list->first;
    while(element != NULL)
    {
        int a = element->data[0];
        int b = element->data[1];
        printf("[%d, %d] -> ", a, b);
        element = element->next;
    }
    printf("NULL\n");*/
    
    return 0;
}
