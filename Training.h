#ifndef TRAINING_H
#define TRAINING_H
#include "NeuralNet.h"

/**/
typedef struct Training_Data{

	double *input;
	int t_size;
	char c;
	double *target;

} 	training_data;

typedef struct Training_Batch{

	int b_size;
	training_data **batch;
	
}	training_batch;

/**/
typedef struct Mini_Batch{

	int mb_size;
	training_data **small_batch;
	
}	mini_batch;

typedef struct Mini_Batch_List{

	int nb_batch;
	mini_batch **mini_data;

} 	mini_batch_list;
/**/

typedef struct Test_Batch{

	int tb_size;
	char *char_list;
	training_data **test_batch;

} 	test_batch;
/**/



/*init*/

training_data *training_data_init(double *in, char *tab, char character, int size);
training_batch *training_batch_init(int size, char *tab, char path[], int n);
mini_batch *mini_batch_init(int size, training_batch *data, int start, int end);
mini_batch_list *mini_batch_list_init(training_batch *data, int mb_size);
test_batch *test_batch_init(int size, char path[], char *tab);



/**/




/*train*/

void train(network *net, mini_batch_list *batch, int epoch, double eta, test_batch *test_data);
void update_mini_batch(network *net, mini_batch *mini, double eta);
void backprop(network *net, double *input, double *target);
double evaluate(network *net, test_batch *data);
/**/



/*Updates*/

double *get_delta(layer *lay, double *d_cost);
void update_weights_bias(network *net, int size, double eta);
double *update_delta_cost(layer *lay, double size, double *old_delta);
void update_delta_bias(layer *lay, double *delta);
void update_delta_weights(layer *lay, layer *prev_lay, double *delta);
/**/

/*micioulanious*/
char get_char(double *tab, char *char_list, int size);
int tab_max(double *tab, int size);
double *target_list_init(char c, char *tab, int size);
/**/





/*Cost*/
double *cost_derivative(layer *last_lay, double *y);
double cost_function(layer *last_lay, double *y);
/**/

#endif
