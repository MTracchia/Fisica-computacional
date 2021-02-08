#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

int main()
{
	srand(time(NULL));
	int q = 50, q_value = 0, f = 5, dim = 0;
	//dim = f*(pow (q,f));  20 tambien podria ser pow (q,f)
	// 20 es lxl
	dim = f*20;
	int vec[dim];
	for (int i = 0; i < dim; i++)
	{
		q_value = rand() % q;
		*(vec + i) = q_value;	
	}
	for(int j=0; j<20; j++)
	{
	   for(int k=0; k<f; k++)
		{
		   printf("%5d", *(vec + f*j+k));
		}
	printf("\n\n");
	}
	return 0;
}
