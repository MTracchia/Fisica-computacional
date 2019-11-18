#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define RAND_MAX 2147483647

#define L 10
#define F 4
#define Q 2




struct agente
{
int atributos[F];
};



int main()
{

srand(time(NULL));
struct agente red[L*L];
int q = 20, similitudes = 0, diferencias = 0, vector_diferencias[F], componente_random, atributo_seleccionado;
float homofilia = 0.0, random;


//red =(int*)malloc(L*L*sizeof(struct agente));
//*(red+3)->atributos[4]=3;	
	

//Inicializa los estados de los agentes y también los imprime
for (int i = 0; i < 2; i++)
{
	for (int j = 0; j < F; j++)
	{
		red[i].atributos[j] = rand() % Q;
		printf("%4d",red[i].atributos[j]);
	}
printf("\n");
}

printf("\n");


//--------------------------------------------------------------
//Similitud e Interaccion

for (int i = 0; i < F; i++)
{  //ojo! todavía falta la parte de selección al azar
red[0].atributos[i];  //es el que considero el elemento activo
red[1].atributos[i];

	if (red[0].atributos[i] == red[1].atributos[i])
		{
			similitudes++;
		}
}
//printf("%d\n", similitudes);

homofilia = (float)similitudes/(float)F;																//int *hist = (int *) malloc(dim*dim*sizeof(int)); - Vector historial con memoria dinámica
printf("homofilia es %f\n", homofilia);

random = (float)rand()/(float)RAND_MAX;
printf("random es %f\n",random);

if((random < homofilia)  && (similitudes != 4))
	{					
		for (int j = 0; j < F ; j++)
			{
   				if (red[0].atributos[j] != red[1].atributos[j])
   				{   							
   					vector_diferencias[diferencias] = j;
   					diferencias++;
   				}
			}	
	componente_random = rand() % diferencias; 
	atributo_seleccionado = vector_diferencias[componente_random];
	red[0].atributos[atributo_seleccionado]=red[1].atributos[atributo_seleccionado];
	

	//Segmento de codigo para probar--------------------------------------------------
printf("\n");
for (int i = 0; i < 2; i++)
{
	for (int j = 0; j < F; j++)
	{
		printf("%4d",red[i].atributos[j]);
	}
printf("\n");
}




	//printf("%d   %d\n",vector_diferencias[0],vector_diferencias[1]);  //imprime la posicion en donde esta la primera diferencia y la segunda		
	}  

return 0;
}
