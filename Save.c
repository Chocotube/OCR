//k

#include <stdio.h>
#include "Save.h"
#include "NeuralNet.h"


void save(Network *net, char file[])
{
	FILE * fp;

	fp = fopen (file,"w");

	int nb_lay = net->nb_layer;
	layer *lay_tab = n->layers;
	
	for (size_t i = 1; i < nb_lay; i++)
	{
		int nb_neural = lay_tab[i]->nb_neuron;
		int prev_nb_neural = lay_tab[i - 1]->nb_neuron;
		neuron *neural_tab = lay_tab[i]->neurons;


		for(size_t j = 0; i < nb_neural; j++)
		{
			double *weights = neural_tab[j]->weights;

			for (int k = 0; k < prev_nb_neural; ++k)
			{
				fprintf(fp, "%f\n", weights[k]);
			}

			double bias = neural_tab[j]->bias;
			fprintf(fp, "%f\n",bias);
		}
	}

	fclose(fp);
}


void load(Network *net, char *file)
{

}

