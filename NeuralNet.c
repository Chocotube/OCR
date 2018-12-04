#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNet.h"
#include "Training.h"


char bmpToChar(network *net, double *in)
{
    for (int i = 0; i < 900; i++)
    {
        printf("%d", (int)in[i]);
    }
	char *character_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,";
	int size = 64;
	feedforward(in, net);
	int nb_lay = net->nb_layer;
	layer **lay_tab = net->layers;
	int nb_n = lay_tab[nb_lay - 1]->nb_neuron;
	neuron **output = lay_tab[nb_lay - 1]->neurons;
	double *output_target  = (double *) malloc(nb_n * sizeof(double));
	for (int j = 0; j < nb_n; ++j)
	{
		output_target[j] = output[j]->activation;
	}
	return get_char(output_target, character_list ,size);
}

/**/
network *network_init(int *nb, int size)
{
	network *new_net = (network *) malloc(sizeof(network));
	new_net->nb_layer = size;
	new_net->layers = (layer **) malloc(size * sizeof(layer *));
	layer **layer_tab = new_net->layers;
	
	*layer_tab = first_layer_init(nb[0]);
	
	for (int i = 1; i < size; i++)
	{
		int j = i - 1;
		*(layer_tab + i) = layer_init(*(layer_tab + j), nb[i]);
	}
	
	return new_net;
	
}

layer *first_layer_init(int size)
{
	layer *lay = (layer *) malloc(sizeof(layer));

	lay->nb_neuron = size;
	lay->neurons = (neuron **) malloc(size * sizeof(neuron *));
	neuron **neural_tab = lay->neurons;
	
	//init_at_zero(*(neural_tab), size);

	for (int i = 0; i < size; i++)
    {
        *(neural_tab + i) = first_layer_neuron_init(0);
    }

	return lay;
}

neuron *first_layer_neuron_init(double x)
{
	neuron *new_neuron = (neuron *) malloc(sizeof(neuron));
    
    new_neuron->nb_weights = 0;
    new_neuron->weights  = NULL;
    
    new_neuron->bias = 0;
    
    new_neuron->z = 0;
    new_neuron->activation = x;
    
    
    
    new_neuron->delta_weights = NULL;
    new_neuron->delta_bias = 0;
    
    return new_neuron;
}


layer *layer_init(layer *prev_lay, int size)
{
    int nb = prev_lay->nb_neuron;
    
    layer *lay = (layer *) malloc(sizeof(layer));
    lay->nb_neuron = size;
    lay->neurons = (neuron **) malloc(size * sizeof(layer *));
    neuron **neural_tab = lay->neurons;
        
    for (int i = 0; i < size; i++)
    {
        *(neural_tab + i) = neuron_init(nb);
    }
    
    return lay;
}

neuron *neuron_init(int nb_w)
{
    neuron *new_neuron = (neuron *) malloc(sizeof(neuron));
    
    new_neuron->nb_weights = nb_w;
    new_neuron->weights  = (double *) malloc(nb_w * sizeof(double));
	double *new_neuronweights = new_neuron->weights;
    weight_init(new_neuronweights, nb_w);
    
    new_neuron->bias = rando();
    
    new_neuron->z = 0;
    new_neuron->activation = 0;
    
    new_neuron->delta_weights = (double *) malloc(nb_w * sizeof(double));
    new_neuron->delta_bias = 0;
    
    return new_neuron;
    
}
/**/

/**/
void weight_init(double *weights, int nb)
{
    for (int i = 0; i < nb; i++)
    {
        *(weights + i) = rando();
    }
}

void init_at_zero(double *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(tab + i) = 0;
    }
}
/**/

/**/

double neuron_activation(double *weights, double bias, layer *lay)
{
    double z = 0;
    int size = lay->nb_neuron;
    neuron **neuron_tab = lay->neurons;
    
    for (int i = 0; i < size; i++)
    {
        z += (neuron_tab[i]->activation) * *(weights + i);
        
    }
    
    z += bias;
    
    return z;
}

void first_layer_input(double *input, layer *lay)
{
	int nb = lay->nb_neuron;
	neuron **tab = lay->neurons;

	for (int i = 0; i < nb; i++)
	{
		tab[i]->activation  = input[i];
	}
}


void feedforward(double *input, network *net)
{
	int nb_lay = net->nb_layer;
	layer **lay_tab = net->layers;
	first_layer_input(input, *lay_tab);
	
	for (int i = 1; i < nb_lay; i++)
	{
		int nb_neural = lay_tab[i]->nb_neuron;
		neuron **neural_tab = lay_tab[i]->neurons;
        

		for(int j = 0; j < nb_neural; j++)
		{
			double *weights = neural_tab[j]->weights;
			double bias = neural_tab[j]->bias;
			neural_tab[j]->z = neuron_activation(weights, bias, lay_tab[i - 1]);
			neural_tab[j]->activation = sigmoid(neural_tab[j]->z);
		}
	}
}

/**/
    
    
/**/
double sigmoid(double z)
{
    return 1/(1 + exp(-z));
}

double sigmoid_prime(double z)
{
	return sigmoid(z) * (1-sigmoid(z));
}
/**/
