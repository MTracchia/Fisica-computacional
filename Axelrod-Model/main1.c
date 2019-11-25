#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define RAND_MAX 2147483647

#define L 4
#define F 4
#define Q 2

struct agente
{
	int atributos[F];
};

void inicializacion (struct agente red[]);
void Interaccion(struct agente red[]);
int elemento_activo(void);
int elemento_vecino (void);

int main()
{
srand(time(NULL));
struct agente red[L*L];



inicializacion(red);
Interaccion(red);



return 0;
}

//-------------------------------------------------------------INICIALIZACION
void inicializacion (struct agente red[]){
for (int i = 0; i < L*L; i++)
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
//------------------------------------------------------------ELEMENTO_ACTIVO
//Selecciono un agente al azar generando un número random entre 0 a L*L.
int elemento_activo(void) {return rand() % (L*L);}







//------------------------------------------------------------ELEMENTO_VECINO
int elemento_vecino (void) {


int elemento_activo_random, i, j;
//Convierto el vector de agentes en una matriz de agentes
elemento_activo_random = elemento_activo();
i=0; //columna   // n = i*L+j
j=3; //fila

int i_izq, i_der, j_sup, j_inf;


int random_vecino;
int indice_vecino;
i_izq = i - 1;
i_der = i + 1;
j_sup = j - 1;
j_inf = j + 1;

int vecAux[] = {i_izq,i_der,j_inf,j_sup};
int auxiliar;


do {
	random_vecino = rand() % 4;
	
} while ( (vecAux[random_vecino] <0) || (vecAux[random_vecino] >=L));

auxiliar = vecAux[random_vecino];



if (random_vecino == 0)
{
	indice_vecino = auxiliar*L + j;
} 
else if (random_vecino == 1)
{
	indice_vecino = auxiliar*L + j;
}
else if (random_vecino == 2)
{
	indice_vecino = i*L + auxiliar;
}
else if (random_vecino == 3)
{
	indice_vecino = i*L + auxiliar;
}







/*
do	{	
		random_vecino = rand() % 4;
			if (random_vecino == 0)
				{
					i--; //-= +=
				}
			else if (random_vecino == 1)
				{
					j--;
				}
			else if (random_vecino == 2)
				{
					i++;
				}
			else if (random_vecino == 3)
				{
					j++;
				}
	} while  (i < 0 || i >= L || j < 0 || j >= L);
int indice_vecino;
indice_vecino = (i*L) + j;
i=0;
j=0;
*/

return indice_vecino;
}

//-------------------------------------------------------------INTERACCION
void Interaccion (struct agente red[]){
int similitudes = 0, diferencias = 0, vector_diferencias[F], componente_random, atributo_seleccionado;
float homofilia = 0.0, random;
/*Comparo el agente activo con su vecino, componente a componente (o atributo por atributo).
Por cada atributo que ambos tengan en común, la variable similitudes sube una unidad.*/

/*
for (int i = 0; i < F; i++)
	{  
		red[0].atributos[i];  
		red[1].atributos[i];
			if (red[0].atributos[i] == red[1].atributos[i])
				{
					similitudes++;
				}
	}
//Calculo la probabilidad de similitud -> homofilia.
homofilia = (float)similitudes/(float)F;																
printf("homofilia es %f\n", homofilia);
//Selecciono un número random para la interaccion.
random = (float)rand()/(float)RAND_MAX;
printf("random es %f\n",random);
/*La interaccion funciona de acuerdo a dos criterios; si random<homofilia Y si la cantidad 
de similitudes es distinta de F. Notar que si los dos agentes son iguales (similitud=F) no 
es necesaria la interacción, de ahí al operador &&.*/
/*if((random < homofilia)  && (similitudes != F))	
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
		atributo_seleccionado = vector_diferencias[componente_random]; //Selecciono el índice del atributo que va a cambiar debido a la interacción
		red[0].atributos[atributo_seleccionado]=red[1].atributos[atributo_seleccionado]; //Actualización del atributo del agente activo
	}  
*/


//------------------------------------------------------------------------------------------

//int indice = elemento_activo();
int indiceVec = elemento_vecino();



printf("\n");

for (int i = 0; i < F; i++){
				printf("%4d",red[0].atributos[i]);
}

printf("\n");


for (int j = 0; j < F; j++){
				printf("%4d",red[indiceVec].atributos[j]);
}

printf("\n");
printf("%d\n", indiceVec);

}




