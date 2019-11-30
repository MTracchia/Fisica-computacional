#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define RAND_MAX 2147483647

#define L 4
#define F 4
#define Q 9  //A partir de Q = 55 la funcion se acerca a cero

struct agente
{
	int atributos[F];
};

void INICIALIZACION (struct agente red[]);
void INTERACCION(struct agente red[], int agente_activo, int agente_vecino);
int AGENTE_ACTIVO(void);
int AGENTE_VECINO(int);
void CLASIFICAR(struct agente red[]);


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
		printf("      %d",i);
		printf("\n");
	}

printf("\n\n");
CLASIFICAR(red);



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
		//red[agente_activo].atributos[i];  
		//red[agente_vecino].atributos[i];
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

//similitudes = 0;
//diferencias = 0;



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




void CLASIFICAR(struct agente red[]) {


int s1, s2, frag = 2;
int nodos[L*L];
int sim1=0,sim2=0, min=0,max=0;  //contadores de similitud para HK

//Inicilializo con ceros el vector de nodos
for (int m = 0; m < L*L; m++)
{
	nodos[m] = 0;
}
//primer valor de "nodos" es igual frag = 2
nodos [0] = frag;

int hist[L*L], sim = 0;

//Incilizacion del vector historial
for (int i = 0; i < L*L; i++) {*(hist + i) = i;}


//Segmento de codigo que agregue etiquetas a la primera fila 
for (int j = 1; j < L; j++)
{
	for (int k = 0; k < F; k++)
	{
		if (red[j-1].atributos[k] == red[j].atributos[k])
		{
			sim++;
		}	
	}
	if (sim == F)
	{
		nodos[j] = nodos[j-1];
	} else {
		frag++;
		nodos[j] = frag;
	}
sim = 0 ;
}
//--------------------------------------------------------------


//Corrijo etiqueta pero por columna respecto del primer elemento
for (int j = 1; j < L; j++)
{
		for (int k = 0; k < F; k++)
		{
			if (red[j*L-L].atributos[k] == red[j*L].atributos[k])
			{
				sim++;
			}	
		}
		if (sim == F)
		{
			nodos[j*L] = nodos[j*L-L];
		} else {
			frag++;
			nodos[j*L] = frag;
		}
	sim = 0 ;

	//Aca comenzaria el proceso de comparacion para agregar etiquetas 

	//Me muevo de izq a der -- las filas estan fijadas por j
	for (int i = 1; i < L; i++)
	{
		//Comparo atributos
		for (int iter = 0; iter < F; iter++)
		{
			//s2 = *(red+j+i*dim-dim);  arriba                       
			//s1 = *(red+j+i*dim-1);  abajo
			//los elementos que tomo
			red[i+j*L-L].atributos[iter];	//arriba
			red[i+j*L-1].atributos[iter];  //abajo
			red[i+j*L].atributos[iter]; //Elemento que comparo

			//Comparo componente a componente los tres agentes
			if (red[i+j*L].atributos[iter] == red[i+j*L-1].atributos[iter]) //abajo
			{
				sim1++;
			}

			if (red[i+j*L].atributos[iter] == red[i+j*L-L].atributos[iter]) //arriba
			{
				sim2++;
			}
		
		}
		
			//Asigno etiqueta al elemento comparador(todavia no es sseguro si es la original)
			//se analizan los distintos casos
			if (sim1 == F && sim2 != F)
			{
				nodos[i+j*L] = nodos [i+j*L-1];
			}

			else if (sim1 != F && sim2 == F)
			{
				nodos[i+j*L] = nodos [i+j*L-L];
			}

			else if (sim1 != F && sim2 != F)
			{
				frag++;
				nodos[i+j*L] = frag;
			}
			
			else if (sim1 == F && sim2 == F)
			{
				if (nodos[i+j*L-1] == nodos[i+j*L-L])
				{
					nodos[i+j*L] = nodos[i+j*L-1];		
				
				} 	
				else if (nodos[i+j*L-1] < nodos[i+j*L-L])
					{
											
						min = nodos[i+j*L-1];
						max = nodos[i+j*L-L];							
							
						nodos[i+j*L] = min;
						*(hist + max) = -min;
						*(hist + min) = min;
					}	
				else if (nodos[i+j*L-1] > nodos[i+j*L-L])
					{
						max = nodos[i+j*L-1];
						min = nodos[i+j*L-L];							
							
						nodos[i+j*L] = min;
						*(hist + max) = -min;
						*(hist + min) = min;				
					}

			}

		sim1 = 0;
		sim2 = 0;
	}


}




for (int corr = 0; corr < L*L; corr++)
{
	
        s1=*(nodos+corr);
        while (*(hist+s1)<0)
            {
              s1=-(*(hist+s1));
            }
     *(nodos+corr)=s1;
     
}










//Para imprimir en forma de matriz
for (int i = 0; i < L; i++)
{
	for (int j = 0; j < L; j++)
	{	
		printf("%2d  ", *(nodos + L*i + j));
	}
printf("\n");
}

printf("\n\n");

for (int imp = 0; imp < L*L; imp++)
{
	printf("%4d", *(hist + imp));
}
printf("\n");
}



















