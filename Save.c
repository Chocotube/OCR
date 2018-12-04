#include <stdio.h>
#include "Save.h"
#include "NeuralNet.h"


void save(network *net, char file[])
{
	FILE * fp;

	fp = fopen (file,"w");

	int nb_lay = net->nb_layer;
	layer **lay_tab = net->layers;
	
	for (int i = 1; i < nb_lay; i++)
	{
		int nb_neural = lay_tab[i]->nb_neuron;
		int prev_nb_neural = lay_tab[i - 1]->nb_neuron;
        
		neuron **neural_tab = lay_tab[i]->neurons;


		for(int j = 0; j < nb_neural; j++)
		{
			double *weights = neural_tab[j]->weights;
            

			for (int k = 0; k < prev_nb_neural; ++k)
			{
				fprintf(fp, "%lf\n", weights[k]);
			}

			double bias = neural_tab[j]->bias;
			fprintf(fp, "%lf\n",bias);
		}
	}

	fclose(fp);
}


void load(network *net, char *file)
{
	FILE * fp;

	fp = fopen (file,"r");

	int nb_lay = net->nb_layer;
	layer **lay_tab = net->layers;
	
	for (int i = 1; i < nb_lay; i++)
	{
		int nb_neural = lay_tab[i]->nb_neuron;
		int prev_nb_neural = lay_tab[i - 1]->nb_neuron;
		neuron **neural_tab = lay_tab[i]->neurons;


		for(int j = 0; i < nb_neural; j++)
		{
			double *weights = neural_tab[j]->weights;

			for (int k = 0; k < prev_nb_neural; ++k)
			{
				fscanf(fp, "%lf", &weights[k]);
			}

			double bias = neural_tab[j]->bias;
			fscanf(fp, "%lf", &bias);
		}
	}

	fclose(fp);
}

