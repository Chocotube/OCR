#ifndef NEURALNET_H
#define NEURALNET_H

#define rando() ((double)rand()/((double)RAND_MAX+1))

/**/
typedef struct Neuron{
    
    int    nb_weights;
    double *weights;
    double bias;
    double z;
    double activation;
    double *delta_weights;
    double delta_bias;
    
}    neuron;

typedef struct Layer{
    
    int    nb_neuron;
    neuron **neurons;
    
}    layer;


typedef struct Network{
    
    int    nb_layer;
    layer  **layers;
    
}    network;




/**/
network *network_init(int *nb, int size);

layer *first_layer_init(int size);
neuron *first_layer_neuron_init(double x);

layer *layer_init(layer *prev_lay, int size);
neuron *neuron_init(int nb_w);
/**/

/**/
void weight_init(double *weights, int nb);
void init_at_zero(double *tab, int size);
/**/

/**/
double neuron_activation(double *weights, double bias, layer *lay);
void first_layer_input(double *input, layer *lay);
void feedforward(double *input, network *net);
/**/



/**/
double sigmoid(double x);
double sigmoid_prime(double x);
/**/




#endif

