#ifndef TEXT_H
#define TEXT_H
#include "NeuralNet.h"

char findChar(char path[], network *net);
char* rebuild(int n, char *res, network *net);
void sort(char **arr, int n);

#endif 
