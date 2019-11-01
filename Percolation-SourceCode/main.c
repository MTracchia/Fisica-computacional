
//---------------------ARCHIVOS DE CABECERA--------------------

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include "prototipos.h"
#include "poblar.c"
#include "imprimir.c"
#include "HoshenKopelmanAlgorithm.c"
#include "percolacion.c"
#include "clusters.c"

#define RAND_MAX 

int main( int argc, char *argv[])
{

srand(time(NULL));

// "p" es la probabilidad de ocupación de los nodos de la grilla
// "dim" es la dimensión de la grilla

float p;
int dim;

if ( argc == 3 )
  {
    sscanf(argv[1],"%d",&dim);
    sscanf(argv[2],"%f",&p);  
  }

//Trabajo con la grilla como un vector de longitud dim*dim
//luego se imprime en forma de matriz -- ver "imprimir"

int red[dim*dim];

poblar(dim,p,red);
clasificar(red, dim);
imprimir( dim, red);
percolacion(red,dim);
clusters(red,dim);

return 0;
}
