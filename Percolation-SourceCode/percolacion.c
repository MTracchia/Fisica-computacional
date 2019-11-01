
/*
Procedimiento que devuelve si el sistema percoló o no. Para el primer
caso se indica la etiqueta del cluster percolante
*/

void percolacion (int *red, int dim)


{
int i, j, k, l, m, x = 0, y = 0;// i y j son iteradores

//Vector para la parte superior de la matriz
int vec1[dim*dim];

//Vector para la parte inferior de la matriz
int vec2[dim*dim];


//Inicializo los vectores de arriba 
for (int l = 0;l < dim*dim; l++)
  
  {   
    vec1[l]=0; 
    vec2[l]=0;
  }


for (i = 0;i < dim; i++)  
    
    {
      x = *(red + i);
      *(vec1+x) = 1; 
    }

*vec1 = 0;


for (m = 0;m < dim; m++) 
    
    {
      y = *(red + (m + dim*dim - dim));
      *( vec2 + y ) = 1;    
    }

*vec2 = 0;

j=2;


while (j < dim*dim && vec1[j]*vec2[j]==0)
    
    {
      j++;
    }
    

if (j == dim*dim) 
    
    {
      j=0;
      k=j;
    }

      else 
        {
          k=j;
        }


k == 0 ? printf("No percolo\n\n"):printf("Cluster percolante %d\n\n",k);

}