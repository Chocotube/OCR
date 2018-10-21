#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "Cutimage.h"
#include "NeuralNet.h"



int main()
{
    printf("Hello and welcome to Dev house's OCR\n");

	printf("proof of concept AI\n");

	//Shows the neural network understanding the XOR function
	NeuralNetXOR();

	printf("Now for the Cutting text part\n");

	//ImageData is a structure that contains the image data
	imageData *img = NULL;
	//allocating memory for image
	img = (imageData *) malloc(sizeof(imageData));
	//Loading the image
	Loadimage(img);
	//greyscaling the image
	greyscale(img);
	//Black or white the image
	BlackOrWhite(img,0.5f);
//If ever you have problems getting the black/white constraste right change the
//0.5f
	FindText(img);

	printf("Credits : marc.gayed, adrien.guell, frederico-jose.silva,");
	printf("jake.penney\n");
	return 0;

}
