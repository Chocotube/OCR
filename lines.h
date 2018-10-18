#ifndef LINES_H
#define LINES_H

typedef struct Element Element;

struct Element
{
    int data[2];
    Element *next;
};
    
typedef struct List List;

struct List
{
    Element *first;
};

Element* createElement(int data[2]);
List* createList();
void insertHead(List *list, Element *element);
List* arrToBoundList(int arr[], int len);

#endif
