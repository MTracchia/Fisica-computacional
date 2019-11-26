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

void INICIALIZACION (struct agente red[]);
void INTERACCION(struct agente red[], int agente_activo, int agente_vecino);
int AGENTE_ACTIVO(void);
int AGENTE_VECINO(int);

int main()
{
srand(time(NULL));
struct agente red[L*L];
int agente_activo, agente_vecino;
INICIALIZACION(red);


for (int i = 0; i < 20000; i++)
{

agente_activo = AGENTE_ACTIVO();
agente_vecino = AGENTE_VECINO(agente_activo);
INTERACCION(red, agente_activo, agente_vecino);
}

printf("\n\n");


for (int i = 0; i < L*L; i++)
	{
		for (int j = 0; j < F; j++)
			{
				printf("%4d",red[i].atributos[j]);
			}
		printf("\n");
	}






return 0;
}

//-------------------------------------------------------------INICIALIZACION
void INICIALIZACION (struct agente red[]){
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
int AGENTE_ACTIVO(void) {return rand() % (L*L);}

//------------------------------------------------------------ELEMENTO_VECINO
int AGENTE_VECINO (int agente_activo) {


int elemento_activo_random, i, j;
//Convierto el vector de agentes en una matriz de agentes
elemento_activo_random = agente_activo;
i=elemento_activo_random/L; //columna   // n = i*L+j
j=elemento_activo_random%L; //fila

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
	{indice_vecino = auxiliar*L + j;} 
		else if (random_vecino == 1)
			{indice_vecino = auxiliar*L + j;}
				else if (random_vecino == 2)
					{indice_vecino = i*L + auxiliar;}
						else if (random_vecino == 3){indice_vecino = i*L + auxiliar;}
return indice_vecino;
}

//-------------------------------------------------------------INTERACCION
void INTERACCION (struct agente red[], int agente_activo, int agente_vecino){
int similitudes = 0, diferencias = 0, vector_diferencias[F], componente_random, atributo_seleccionado;
float homofilia = 0.0, random;
/*Comparo el agente activo con su vecino, componente a componente (o atributo por atributo).
Por cada atributo que ambos tengan en común, la variable similitudes sube una unidad.*/
/*
for (int i = 0; i < F; i++){
				printf("%4d",red[agente_activo].atributos[i]);
}
printf("\n");

printf("agente activo %d\n",agente_activo);


for (int j = 0; j < F; j++){
				printf("%4d",red[agente_vecino].atributos[j]);
}

printf("\n");
printf("agente vecino %d\n", agente_vecino);

*/


for (int i = 0; i < F; i++)
	{  
		red[agente_activo].atributos[i];  
		red[agente_vecino].atributos[i];
			if (red[agente_activo].atributos[i] == red[agente_vecino].atributos[i])
				{
					similitudes++;
				}
	}
//Calculo la probabilidad de similitud -> homofilia.
homofilia = (float)similitudes/(float)F;																
//printf("homofilia es %f\n", homofilia);
//Selecciono un número random para la interaccion.
random = (float)rand()/(float)RAND_MAX;
//printf("random es %f\n",random);
/*La interaccion funciona de acuerdo a dos criterios; si random<homofilia Y si la cantidad 
de similitudes es distinta de F. Notar que si los dos agentes son iguales (similitud=F) no 
es necesaria la interacción, de ahí al operador &&.*/
if((random < homofilia)  && (similitudes != F))	
	{					
		for (int j = 0; j < F ; j++)
			{
   				if (red[agente_activo].atributos[j] != red[agente_vecino].atributos[j])
   					{   							
   						vector_diferencias[diferencias] = j;
   						diferencias++;
   					}
			}	
		componente_random = rand() % diferencias; 
		atributo_seleccionado = vector_diferencias[componente_random]; //Selecciono el índice del atributo que va a cambiar debido a la interacción
		red[agente_activo].atributos[atributo_seleccionado]=red[agente_vecino].atributos[atributo_seleccionado]; //Actualización del atributo del agente activo
	}  
/*
printf("\n\n");
printf("%d\n",vector_diferencias[componente_random]);
printf("\n\n");
for (int i = 0; i < F; i++){
				printf("%4d",red[agente_activo].atributos[i]);
}
printf("\n");

printf("agente activo %d\n",agente_activo);


for (int j = 0; j < F; j++){
				printf("%4d",red[agente_vecino].atributos[j]);
}

printf("\n");
printf("agente vecino %d\n", agente_vecino);
*/







}




