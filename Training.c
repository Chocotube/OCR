#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNet.h"
#include "Training.h"
#include <SDL2/SDL.h>
#include <dirent.h>
#include "surface.h"

/*Actual NeuralNetwork*/


training_data *training_data_init(char path[], char *tab, char character, int size, char name[])
{
	training_data *data = (training_data *) malloc(sizeof(training_data));
	char *filePath = malloc(len(path) * sizeof(char *) + len(name) * sizeof(char));
    sprintf(filePath, "%s/%s", path, name);
    SDL_Surface *surf = LoadImage(filePath);
    double *array = malloc(sizeof(double) * 900);
    for (int i = 0; i < 900; i++)
    {
        array[i] = 0;
    }
    surfToArr(surf, array);
    data->input = array;
   
	data->t_size = size;
	data->c = character;
   // printf(" the char you are looking for is = %c\n",data->c);
	data->target = target_list_init(character, tab, size);


	return data;

}

int len(char *tab)
{
	int i = 0;
	while (tab[i] != '\0')
	{
		++i;
	}
	return i;
}



training_batch *training_batch_init(int size, char *tab, char path[], int n)
{
    training_batch *t_batch = (training_batch*) malloc(sizeof(training_batch));
    t_batch->b_size = n;
    t_batch->batch = malloc(sizeof(training_data)*n);
	struct dirent *de;
    DIR *dr = opendir(path);
    char *point = ".";
    char *pointpoint = "..";
    if (dr == NULL)
    {
        printf("Could not open current directory" );
    }
    int i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (strcmp(de->d_name, point) != 0 && strcmp(de->d_name, pointpoint) != 0)
        {
            puts(de->d_name);
            char c = de->d_name[0];
            t_batch->batch[i] = training_data_init(path, tab, c, size, de->d_name);
            ++i;
        }
    }
	return t_batch;
}

mini_batch *mini_batch_init(int size, training_batch *data, int start, int end)
{
	mini_batch *new_batch  = (mini_batch *) malloc(sizeof(mini_batch));
	new_batch->mb_size = size;
	new_batch->small_batch = (training_data **) malloc(size * sizeof(training_data *));
	training_data **new_data = new_batch->small_batch;
    
    int i = start;
    int j = 0;
    int jEnd = end - start;

	while (i < end && j < jEnd)
	{
		new_data[j] = data->batch[i];
        printf("all is good\n");
        printf("%c, ",data->batch[i]->c);
        
        i++;
        j++;
	}
	
	return new_batch;
}

mini_batch_list *mini_batch_list_init(training_batch *data, int mb_size)
{
	int size = data->b_size;
	//training_data **t_data = data->batch;
	/*for (int i = 0; i < size - 1; ++i)
	{
		int j = i + rand() /(RAND_MAX / (size - i) + 1);
		training_data *t = t_data[j];
		t_data[j] = t_data[i];
		t_data[i] = t;
	}*/
	
	mini_batch_list *mini_list = (mini_batch_list *) malloc(sizeof(mini_batch_list));
	mini_list->nb_batch = size / mb_size;
	mini_list->mini_data = (mini_batch **) malloc((size / mb_size) * sizeof(mini_batch *));

	mini_batch **new_batch = mini_list->mini_data;
	
	int k = 0;
	while (k < size)
	{
		for (int l = 0; l < (size / mb_size); ++l)
		{
			int end = k + mb_size;
			new_batch[l] = mini_batch_init(mb_size, data, k, end);
            //printf("");
            k += mb_size;
		}
		
	}
	return mini_list;

}

test_batch *test_batch_init(int size, char path[], char *tab)
{
	test_batch *t_batch = (test_batch *) malloc(sizeof(test_batch));
    t_batch->tb_size = size;
	t_batch->char_list = tab;
    t_batch->test_batch = (training_data **) malloc(sizeof(training_data *) * size);
	struct dirent *de;
    DIR *dr = opendir(path);
    if (dr == NULL)
    {
        printf("Could not open current directory" );
    }
    int i = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] != '.')
        {
            char c = de->d_name[0];
            t_batch->test_batch[i] = training_data_init(path, tab, c, size, de->d_name);
            ++i;
        }
    }
    
	return t_batch;
}






/*train*/
void train(network *net, mini_batch_list *batch, int epoch, 
								double eta, test_batch *t_data)
{
	double error = 1;
	int nb_mini = batch->nb_batch;
	mini_batch **tab = batch->mini_data;
	int nb_test = t_data->tb_size;
	int i = 0;
    /*for (int i = 0; i < 64; i++)
    {
        printf("%f \n",in[i]);
    }*/
	while(i < epoch && error > 0.01)
	{
        
        //printf("number of things i don't have %d\n",nb_mini);
		for (int j = 0; j < nb_mini; ++j)
		{
        //    printf(" I'm fucking not ok right now %d\n", j);
			update_mini_batch(net, tab[j], eta);
        //    printf(" HAHAHAHHAHAHAHAHHAHAHHAHAHAHAHAH \n");
		}
		
        //printf("MAYBE MMAUEBHBFVBZ\n");
        
		if(epoch % 100 == 0)
		{
        //    printf(" WHAAAAAAAAAAAAAATTTTTTTTTT \n");
			error = evaluate(net,t_data)/nb_test;
			//printf("\nEpoch %-5d :	Error = %f\n", epoch, error);
		}

		++i;
	}
}

void update_mini_batch(network *net, mini_batch *mini, double eta)
{   
  //  printf("yes yes yes yes\n");
    
	int size = mini->mb_size;
	training_data **mini_tab = mini->small_batch;
    
    for (int i = 0; i < 56; i++){
    for (int j = 0; j < 900; j++)
        {
           // printf("%c, ",mini_tab[i]->c);
            //printf("%f, ",mini_tab[i]->input[j]);
            
        }
        //printf("\n%d\n\n",i);
        
    }
    
	for (int i = 0; i < size; ++i)
	{
        //printf("personne la vie BEST PRESIDENT %d\n", i);
		double *in = mini_tab[i]->input;
        //printf("%c\n",mini_tab[i]->c);
        for (int j = 0; j < 900; j++)
        {
            //printf("%f, ",in[j]);
            
        }
        //printf("\n\n\n");

		double *targ = mini_tab[i]->target;
        for (int k = 0; k < 64; k++)
        {
            //printf("%f, \n",targ[k]);
            
        }
        
        //printf("\n\n\n");
		backprop(net, in, targ);
        
    //printf("le stylo BEST PRESIDENT\n");
	}
	
    //printf("no my mom doesn' like u\n");
	

	update_weights_bias(net, size, eta);
    
    //printf("but I do\n");
}

void backprop(network *net, double *input, double *target)
{   
    //printf("MACRON BEST PRESIDENT\n");
    
	feedforward(input,net);
    
    //printf("MACRON BEST PRESIDENT\n");
    
    /*for (int i = 0; i < 900; i++)
    {
        printf("%d ,", (int)input[i]);
    }*/
	int nb_lay  = net->nb_layer;
	layer **lay_tab = net->layers;
	
	double *d_cost = cost_derivative(lay_tab[nb_lay - 1], target);
	double *delta = get_delta(lay_tab[nb_lay - 1], d_cost);

	update_delta_bias(lay_tab[nb_lay - 1], delta);
	update_delta_weights(lay_tab[nb_lay - 1], lay_tab[nb_lay -2], delta);

	for (int i = 2; i < nb_lay ; ++i)
	{
		layer *lay = lay_tab[nb_lay - i];
		int nb_neural = lay->nb_neuron;

		layer *next_lay = lay_tab[nb_lay - (i - 1)];

		double *new_cost = update_delta_cost(next_lay, nb_neural, delta);
		delta = get_delta(lay, new_cost);

		update_delta_bias(lay,delta);

		layer *prev_lay = lay_tab[nb_lay - (i + 1)];
		update_delta_weights(lay, prev_lay, delta);
	}
}

double evaluate(network *net, test_batch *data)
{
	int results = 0;
	int nb_lay = net->nb_layer;

	int size = data->tb_size;
	training_data **t_data = data->test_batch;
	char *list = data->char_list;

	for (int i = 0; i < size; ++i)
	{
		double *in = t_data[i]->input;
		feedforward(in, net);


		char tar = t_data[i]->c;

		layer **lay_tab = net->layers;

		int nb_n = lay_tab[nb_lay - 1]->nb_neuron;
		neuron **output = lay_tab[nb_lay -1]->neurons;

		double *output_target  = (double *) malloc(nb_n * sizeof(double));

		for (int j = 0; j < nb_n; ++j)
		{
			output_target[j] = output[j]->activation;
		}

		
		results += get_char(output_target, list ,size) == tar;
	}

	return results;
}

/**/


/*Upadtes*/

double *get_delta(layer *lay, double *d_cost)
{
	int nb_neural = lay->nb_neuron;
	neuron **neural_tab = lay->neurons;

	double *delta = (double *) malloc(nb_neural * sizeof(double));


	for (int i = 0; i < nb_neural; ++i)
	{
		delta[i] = d_cost[i] * sigmoid_prime(neural_tab[i]->z);
	}

	return delta;
}

void update_weights_bias(network *net, int size, double eta)
{
	int nb_lay = net->nb_layer;
	layer **lay_tab = net->layers;
	
	for (int i = 1; i < nb_lay; i++)
	{
		int nb_neural = lay_tab[i]->nb_neuron;
		neuron **neural_tab = lay_tab[i]->neurons;

		for(int j = 0; j < nb_neural; j++)
		{
			int nb_w = neural_tab[j]->nb_weights;
			double *w = neural_tab[j]->weights;
			double *d_w = neural_tab[j]->delta_weights;
			for (int k = 0; k < nb_w; ++k)
			{
				w[k] -= (eta/size) * d_w[k];
			}
			neural_tab[j]->bias -= (eta/size) * neural_tab[j]->delta_bias; 
		}
	}
}

double *update_delta_cost(layer *lay, double size, double *old_delta)
{
	int nb_neural = lay->nb_neuron;
	neuron **neural_tab = lay->neurons;

	double *cost = (double *) malloc(size * sizeof(double));

	for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < nb_neural; ++k)
			{
				double *w = neural_tab[k]->weights;
				cost[j] += w[j] * old_delta[k];
			}
		}
	return cost;
}

void update_delta_bias(layer *lay, double *delta)
{
	int nb_neural = lay->nb_neuron;
	neuron **neural_tab = lay->neurons;

	for (int i = 0; i < nb_neural; ++i)
	{
		neural_tab[i]->delta_bias += delta[i];
	}
}

void update_delta_weights(layer *lay, layer *prev_lay, double *delta)
{
	int nb_neural = lay->nb_neuron;
	neuron **neural_tab = lay->neurons;

	neuron **neural_prev_tab = prev_lay->neurons;

	for (int i = 0; i < nb_neural; ++i)
	{
		int nb_w = neural_tab[i]->nb_weights;
		double *d_w = neural_tab[i]->delta_weights;

		for (int j = 0; j < nb_w; ++j)
		{

			d_w[j] += neural_prev_tab[j]->activation * delta[i];
		}
	}
}
/**/



/*misc*/

char get_char(double *tab, char *char_list, int size)
{
	int max = tab_max(tab, size);
	char c = char_list[max];

	return c;
}

int tab_max(double *tab, int size)
{
	int res = tab[0];
	for (int i = 1; i < size; ++i)
	{
		if (res < tab[i])
		{
			res = tab[i];
		}
	}

	return res;
}

double *target_list_init(char c, char *tab, int size)
{
	double *target = (double *) malloc(size * sizeof(double));

	for (int i = 0; i < size; ++i)
	{
		if(c == tab[i])
		{
			target[i] = 1;
		}
		else
		{
			target[i] = 0;
		}
	}

	return target;
}

/**/




/**/

double *cost_derivative(layer *last_lay, double *y)
{
	int nb_neural = last_lay->nb_neuron;
	double *cost = (double *) malloc(nb_neural * sizeof(double));
	neuron **neural_tab = last_lay->neurons;

	for (int i = 0; i < nb_neural; i++)
	{
		cost[i] = neural_tab[i]->activation - y[i];
	}

	return cost;
}


double cost_function(layer *last_lay, double *y)
{
	double cost = 0;
	int nb_neural = last_lay->nb_neuron;
	neuron **neural_tab = last_lay->neurons;

	for (int i = 0; i < nb_neural; i++)
	{
		cost += 0.5*pow((neural_tab[i]->activation - y[i]),2);
	}

	return (cost/nb_neural);
}
/**/
