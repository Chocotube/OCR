#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNet.h"
#include "Training.h"
#include <SDL2/SDL.h>
#include <dirent.h>
#include "surface.h"
#include "Save.h"



int main(int argc, char *argv[])
{
    
	int res = 0;
	if (argc < 2)
	{
		res = 1;
		printf("main: usage: train_path test_path \n");
	}
	else
	{
		char *character_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,";
		int tab[] = {900,100,64};
		network *ocr = network_init(tab, 3);
        save(ocr,"neuron.txt");
        
		training_batch *batch = training_batch_init(64, character_list, argv[1], 448);

		mini_batch_list *mini_list = mini_batch_list_init(batch, 56);
		test_batch *test = test_batch_init(64, argv[2], character_list);
        
        
        printf("Ta cru hahahahah\n");

		train(ocr, mini_list, 100000, 8, test);
        printf("done\n");
	}
	return res;
}
