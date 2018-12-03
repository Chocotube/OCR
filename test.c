#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save42(double tab[], int len)
{
	FILE *file_pointer;
	file_pointer = fopen("neurones.db", "w");
	int m = 0;
	//*res = (char*) malloc(90000000 * sizeof(char));
	--len;
	while(m < len)
	{
		fprintf(file_pointer,"%lf\n",tab[m]);
		++m;
	}
	fprintf(file_pointer,"%lf",tab[m]);
    
	fclose(file_pointer);
	return m;
}

void printtab(double *end, double *begin)
{
	 for (int line = 0; begin != end; ++begin)
	{
		if (line > 72)
		{
			printf("|`|\n");
			line = 0;
		}

		line += printf("| %lf ", *begin);
	}

    printf("|\n");
}
double* load(char filename[], int len)
{
	double *ptr;
	int i = 0;
	ptr = malloc(sizeof(double)*len);
	FILE *file_pointer;
	file_pointer = fopen(filename,"r");
	while(i < len)
	{
		++i;
		fscanf(file_pointer,"%lf",ptr);
		ptr++;
	}
	ptr--;
	fclose(file_pointer);
	return ptr;
}



