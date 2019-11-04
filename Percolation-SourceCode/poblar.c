//#include <stdio.h>

int poblar(int dim, float p, int *red)
{
int i;
float random;
for(i=0;i<dim*dim;i++)
	{
		random = ((float)rand()/(float)RAND_MAX);
		*(red+i)=0;
			if (random<p)
     			*(red+i)=1;
	}
return 0;
}
