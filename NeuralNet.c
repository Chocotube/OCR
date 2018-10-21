#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include"NeuralNet.h"

#define NUMPAT 4
#define NUMIN  2
#define NUMHID 2
#define NUMOUT 1

#define rando() ((double)rand()/((double)RAND_MAX+1))

void NeuralNetXOR()
{
	int    i, j, k, p, np, op, ranpat[NUMPAT+1], epoch;
	int    NumPattern = NUMPAT, NumInput = NUMIN, NumHidden = NUMHID;
	int    NumOutput = NUMOUT;
	double Input[NUMPAT+1][NUMIN+1]={{0,0,0},{0,0,0},{0,1,0},{0,0,1},{0,1,1}};
    double Target[NUMPAT+1][NUMOUT+1] = {{0,0},{0,0},{0,1},{0,1},{0,0}};
	double SumH[NUMPAT+1][NUMHID+1], WeightIH[NUMIN+1][NUMHID+1];
	double Hidden[NUMPAT+1][NUMHID+1]; 
	double SumO[NUMPAT+1][NUMOUT+1], WeightHO[NUMHID+1][NUMOUT+1];
	double Output[NUMPAT+1][NUMOUT+1];
	double DeltaO[NUMOUT+1], SumDOW[NUMHID+1], DeltaH[NUMHID+1];
	double DeltaWeightIH[NUMIN+1][NUMHID+1], DeltaWeightHO[NUMHID+1][NUMOUT+1];
	double Error, eta = 0.7, alpha = 0.9, smallwt = 0.5;

	/* initializing the weights & delta weights 
	going from the input to the hidden layer*/
	
	for (j = 1; j <= NumHidden; j++)
	{
		for (i = 0; i <= NumInput; i++)
		{
			DeltaWeightIH[i][j] = 0.0;
			WeightIH[i][j] = 2.0 * (rando() - 0.5) * smallwt;
		}
	}

	/* initializing the weights & delta weights
	 going from the hidden layer to the output */

	for (k = 1; k <= NumOutput; k++)
	{
		for (j = 0; j <= NumHidden; j++)
		{
			DeltaWeightHO[j][k] = 0.0;
			WeightHO[j][k] = 2.0 * (rando() - 0.5) * smallwt;
		}
	}

	/* Repeating the learning porcess */
	for (epoch = 0; epoch < 100000; epoch++)
	{
		/* here we randomize the order of traning patterns */
		for (p = 1; p <= NumPattern; p++)
		{
			ranpat[p] = p;
		}
		for (p = 1; p <= NumPattern; p++)
		{
			np = p + rando() * (NumPattern + 1 - p);
			op = ranpat[p];
			ranpat[p] = ranpat[np];
			ranpat[np] = op;
		}
		Error = 0.0;

		/* We repeat the process for all training patterns */
		for ( np = 1; np <= NumPattern; np++)
		{
			p = ranpat[np];
			
			/* We  now compute the hidden unit activations */
			for (j = 1; j <= NumHidden; j++)
			{
				SumH[p][j] = WeightIH[0][j];
				for (i = 1; i <= NumInput; i++)
				{
					SumH[p][j] += Input[p][i] * WeightIH[i][j];
				}
				Hidden[p][j] = 1.0/(1.0 + exp(-SumH[p][j]));
			}

			/* And now the output unit activations and errors */
			for (k = 1; k <= NumOutput; k++)
			{
				SumO[p][k] = WeightHO[0][k];
				for (j = 1; j <= NumHidden; j++)
				{
					SumO[p][k] += Hidden[p][j] * WeightHO[j][k];
				}

				/* Using the sigmoid function we get these outputs*/
				Output[p][k] = 1.0/(1.0 + exp(-SumO[p][k]));
				Error += 0.5 * pow((Target[p][k] - Output[p][k]),2);
				DeltaO[k] = (Target[p][k] - Output[p][k]); 
				DeltaO[k] *= Output[p][k] * (1.0 - Output[p][k]);
			}

			/* Here we 'back-propagate' the errors to the hidden layer */
			for (j = 1; j <= NumHidden; j++)
			{
				SumDOW[j] = 0.0;
				for (k =1; k <= NumOutput; k++)
				{
					SumDOW[j] += WeightHO[j][k] * DeltaO[k];
				}
				DeltaH[j] = SumDOW[j] * Hidden[p][j] * (1.0 - Hidden[p][j]);
			}

			/* Updating the wights from th input layer to the hidden one*/
			for (j = 1; j <= NumHidden; j++)
			{
				DeltaWeightIH[0][j] = eta*DeltaH[j]+alpha*DeltaWeightIH[0][j];
				WeightIH[0][j] += DeltaWeightIH[0][j];
				for (i = 1; i <= NumInput; i++)
				{
					DeltaWeightIH[i][j] = eta * Input[p][i] * DeltaH[j];
					DeltaWeightIH[i][j] += alpha * DeltaWeightIH[i][j];
					WeightIH[i][j] += DeltaWeightIH[i][j];
				}
			}

			/* Updating the weights from the hidden layer to the output one*/
			for (k = 1; k <= NumOutput; k++)
			{
				DeltaWeightHO[0][k] = eta * DeltaO[k];
				DeltaWeightHO[0][k] += alpha * DeltaWeightHO[0][k];
				WeightHO[0][k] += DeltaWeightHO[0][k];
				for (j = 1; j <= NumHidden; j++)
				{
					DeltaWeightHO[j][k] = eta * Hidden[p][j] * DeltaO[k];
					DeltaWeightHO[j][k] += alpha * DeltaWeightHO[j][k];
					WeightHO[j][k] += DeltaWeightHO[j][k];
				}
			}
		}

		if( epoch % 100 == 0) 
		{
			fprintf(stdout, "\nEpoch %-5d :   Error = %f", epoch, Error);
		}
		/* We Stop learning when the amount of error is minimal */
		if (Error < 0.0004) break;
	}

		
	/* We now print the networks outputs */		 
	fprintf(stdout, "\n\nNETWORK DATA - EPOCH %d\n\nPat\t", epoch); 
  
   	for( i = 1 ; i <= NumInput ; i++) 
	{
       		fprintf(stdout, "Input%-4d\t", i);
   	}
    	for( k = 1 ; k <= NumOutput ; k++) 
	{
       		fprintf(stdout, "Target%-4d\tOutput%-4d\t", k, k);
   	}
   	for( p = 1 ; p <= NumPattern ; p++ ) 
	{        
    	fprintf(stdout, "\n%d\t", p);
       	for(i = 1 ; i <= NumInput ; i++) 
		{
           		fprintf(stdout, "%f\t", Input[p][i]);
      	}
       	for(k = 1 ; k <= NumOutput ; k++) 
		{
            fprintf(stdout, "%f\t%f\t", Target[p][k], Output[p][k]);
        }
    }
   	fprintf(stdout, "\n\nGoodbye!\n\n");
		
	
}



