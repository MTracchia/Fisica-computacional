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

void inicializacion (struct agente red[]);
void Interaccion(struct agente red[]);



int main()
{

srand(time(NULL));
struct agente red[L*L];


//red =(int*)malloc(L*L*sizeof(struct agente));
//*(red+3)->atributos[4]=3;	
	
inicializacion(red);
Interaccion(red);

return 0;
}


//-----------------------------------------------------------------------------------------------------INICIALIZACION

void inicializacion (struct agente red[])

{
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
}


//-----------------------------------------------------------------------------------------------------INTERACCION


void Interaccion (struct agente red[]){

int similitudes = 0, diferencias = 0, vector_diferencias[F], componente_random, atributo_seleccionado;
float homofilia = 0.0, random;

for (int i = 0; i < F; i++)
{  
red[0].atributos[i];  
red[1].atributos[i];

	if (red[0].atributos[i] == red[1].atributos[i])
		{
			similitudes++;
		}
}

homofilia = (float)similitudes/(float)F;																
printf("homofilia es %f\n", homofilia);

random = (float)rand()/(float)RAND_MAX;
printf("random es %f\n",random);

if((random < homofilia)  && (similitudes != F))
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
	}  
}


























