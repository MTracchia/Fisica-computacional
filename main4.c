#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define RAND_MAX 2147483647

#define L 10
#define F 10
//#define Q 2
	 //A partir de Q = 55 la funcion se acerca a cero

struct agente
{
	int atributos[F];
};

void INICIALIZACION (struct agente red[], int Q);
int INTERACCION(struct agente red[], int agente_activo, int agente_vecino);
int AGENTE_ACTIVO(void);
int AGENTE_VECINO(int);
int CLASIFICAR(struct agente red[]);


int main()
{
srand(time(NULL));
/*
struct agente red[L*L];
int agente_activo, agente_vecino;
//int Q = 2;
long fragmento, suma = 0;
double promedio,promedio_norm;
*/



struct agente red[L*L];
int agente_activo, agente_vecino;
int Q = 2;
long fragmento, suma = 0, sum_1 = 0;
double promedio,promedio_norm,sigma;
long frags [100];




for (int Q = 2; Q < 100; Q++)
{
	
		for (int prom = 0; prom < 100; prom++)
		{
			
		

			INICIALIZACION(red,Q);

			for (int i = 0; i < 5000000; i++)
			{
			agente_activo = AGENTE_ACTIVO();
			agente_vecino = AGENTE_VECINO(agente_activo);
			INTERACCION(red, agente_activo, agente_vecino);
			}

			//printf("\n\n");

			/*
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
			*/

			fragmento = CLASIFICAR(red);
			suma = suma + fragmento;
			frags[prom] = fragmento;
			
			}

			


promedio = (double)suma/(double)100;
promedio_norm = promedio/(double)(L*L);




for (int l = 0; l < 100; l++)
			{
				sum_1 += ((promedio - frags[l])*(promedio - frags[l]));
			}

double sigma_norm;
sigma = (sqrt((double)sum_1/(double)100));

sigma_norm = sigma/(double)(L*L);


printf("%d       %f       %f\n",Q, promedio_norm, sigma_norm);
suma = 0;
promedio = 0.0;
sum_1 = 0;
sigma = 0.0;
sigma_norm = 0.0;



/*
printf("%d         %f\n",Q, promedio_norm);
suma = 0;
promedio = 0.0;
*/

}

return 0;
}

//-------------------------------------------------------------INICIALIZACION
void INICIALIZACION (struct agente red[], int Q){
int q_num = 0;
for (int i = 0; i < L*L; i++)
	
	{
		for (int j = 0; j < F; j++)
			{
				q_num = rand() % Q;
				red[i].atributos[j] = q_num; 
				//printf("%4d",red[i].atributos[j]);
			}
		//printf("      %d",i);
		//printf("\n");
	}
//printf("\n");
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

//para primeros y segundo vecinos------
int random1, random2, aux1, aux2,aux3, agentes_seleccionados[3],random_selection;

//para vecinos estrella--------
int fila = elemento_activo_random/L;

int random_vecino;
int indice_vecino;
i_izq = i - 1;
i_der = i + 1;
j_sup = j - 1;
j_inf = j + 1;
int vecAux[] = {i_izq,i_der,j_inf,j_sup}; 
//int vecAux[] = {i_sup,i_inf,j_der,j_izq};
int auxiliar;

//-------------------------------------------------------------------------------------------------------------------------------
//--VECINOS ESTRELLA--

/*
do
{
	random1 = rand() % 2;
} while ((vecAux[random1] <0) || (vecAux[random1] >=L));
do
{
	random2 = 2 + rand() % 2;
} while ((vecAux[random2] <0) || (vecAux[random2] >=L));
aux1 = vecAux[random1]*L + j;
aux2 = i*L + vecAux[random2];
//------------------------------------
if ( fila%2 == 0)
{
							if (vecAux[random2] == j_sup)
								{
									aux3 = vecAux[random2] + vecAux[random1]*L;
								} else if (vecAux[random2] == j_inf)
											{
												aux3 = -1;
											}
	
} else if ( fila%2 == 1) 
		{
							if (vecAux[random2] == j_inf)
								{
									aux3 = vecAux[random2] + vecAux[random1]*L;
								} else if (vecAux[random2] == j_sup)
											{
												aux3 = -1;
											}
		}
agentes_seleccionados[0] = aux1;
agentes_seleccionados[1] = aux2;
agentes_seleccionados[2] = aux3;
do {
random_selection = rand() % 3;
if (random_selection == 0)
{
	indice_vecino = aux1;
}
else if (random_selection == 1)
{
	indice_vecino = aux2;
}
else if (random_selection == 2)
{
	indice_vecino = aux3;
}
 } while (indice_vecino < 0);
//printf("%d    %d      %d       fila:%d\n", aux1,aux2,aux3,fila);
*/
//-----------------------------------------------------------------------------------------------------------------------------------------
//--PRIMEROS Y SEGUNDOS VECINOS--



do
{
	random1 = rand() % 2;
} while ((vecAux[random1] <0) || (vecAux[random1] >=L));
do
{
	random2 = 2 + rand() % 2;
} while ((vecAux[random2] <0) || (vecAux[random2] >=L));
aux1 = vecAux[random1]*L + j;
aux2 = i*L + vecAux[random2];
aux3 = vecAux[random2] + vecAux[random1]*L;
agentes_seleccionados[0] = aux1;
agentes_seleccionados[1] = aux2;
agentes_seleccionados[2] = aux3;
random_selection = rand() % 3;
if (random_selection == 0)
{
	indice_vecino = aux1;
}
else if (random_selection == 1)
{
	indice_vecino = aux2;
}
else if ((random_selection == 2))
{
	indice_vecino = aux3;
}


//-----------------------------------------------------------------------------------------------------------------------------------
// --PRIMEROS VECINOS--
/*
do {
	random_vecino = rand() % 4; //ahora es hasta el 7
	} while ( (vecAux[random_vecino] <0) || (vecAux[random_vecino] >=L));
auxiliar = vecAux[random_vecino];
if (random_vecino == 0)
	{indice_vecino = auxiliar*L + j;} 
		else if (random_vecino == 1)
			{indice_vecino = auxiliar*L + j;}
				else if (random_vecino == 2)
					{indice_vecino = i*L + auxiliar;}
						else if (random_vecino == 3){indice_vecino = i*L + auxiliar;}
*/

return indice_vecino;
}

//-------------------------------------------------------------INTERACCION
int INTERACCION (struct agente red[], int agente_activo, int agente_vecino){
int similitudes = 0, diferencias = 0, vector_diferencias[F], componente_random, atributo_seleccionado;
float homofilia = 0.0, random;
/*Comparo el agente activo con su vecino, componente a componente (o atributo por atributo).
Por cada atributo que ambos tengan en común, la variable similitudes sube una unidad.*/

/*  //ESTO ES PARA IMPRIMIR EL AGENTE ACTIVO Y SU VECINO
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
if((random < homofilia)  && (similitudes != F) && (similitudes != 0))	
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
else return 1;


similitudes = 0;
diferencias = 0;



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




int CLASIFICAR(struct agente red[]) {


int s1, s2, frag = 2;
int nodos[L*L], cantidades[L*L];
int sim1=0,sim2=0, min=0,max=0;  //contadores de similitud para HK

//Inicilializo con ceros el vector de nodos
for (int m = 0; m < L*L; m++)
{
	nodos[m] = 0;
	cantidades[m] = 0;
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
		if (*(hist + nodos[j]) < 0)
        {
            nodos[j] = -(*(hist + nodos[j])); 
        }

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

			
			if (*(hist + nodos[j*L]) < 0)
        		{
            		nodos[j*L] = -(*(hist + nodos[j*L])); 
        		}
				


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
											
						if (*(hist + nodos[i+j*L-1])<0)
    							{
      								nodos[i+j*L-1] = -(*(hist + nodos[i+j*L-1]));
   	 							}
  
						if (*(hist + nodos[i+j*L-L])<0)
    							{
      								nodos[i+j*L] = -(*(hist + nodos[i+j*L]));
   								}

						min = nodos[i+j*L-1];
						max = nodos[i+j*L-L];							
							
						nodos[i+j*L] = min;
						*(hist + max) = -min;
						*(hist + min) = min;
					}	
				else if (nodos[i+j*L-1] > nodos[i+j*L-L])
					{
							if (*(hist + nodos[i+j*L-1])<0)
    							{
      								nodos[i+j*L-1] = -(*(hist + nodos[i+j*L-1]));
   	 							}
  
							if (*(hist + nodos[i+j*L-L])<0)
    							{
      								nodos[i+j*L] = -(*(hist + nodos[i+j*L]));
   								}

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

//Corrijo etiquetas
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
/*
for (int i = 0; i < L; i++)
{
	for (int j = 0; j < L; j++)
	{	
		printf("%5d", *(nodos + L*i + j));
	}
printf("\n\n");
}
*/
//printf("\n\n");

//-----Esto es para imprimir el vector historial
/*
for (int imp = 0; imp < L*L; imp++)
{
	printf("%4d", *(hist + imp));
}
*/
//printf("\n");


//ESTO ES PARA ENCONTRAR EL CLUSTER DE MAYOR TAMAÑO

for (int i = 0; i < L*L; i++)
{
	cantidades[i]=0;

}





//Clasifico a los clusters segun su tamaño
for (int cont = 0; cont < L*L; cont++)
{
	cantidades[*(nodos + cont)]++;
}


int max_frag = 0;

//Imprimo el vector con la estiqueta y el tamaño de los clusters
/*for (int i = 0; i < L*L; i++)
{
	
	if (*(cantidades + i))
	{
		printf("et:%d - masa:%d| ",i,*(cantidades + i));
	}
	
}
printf("\n");
*/		

//Busco el cluster de mayor tamaño
max_frag = *(cantidades);

int maxf;
int auxiliar;
for ( maxf = 1; maxf < L*L; maxf++)
{
			
		if (*(cantidades + maxf) > max_frag)
		{
			max_frag = *(cantidades + maxf);
			auxiliar = maxf;
		}
}
//printf("cluster maximo: %d     et: %d\n", max_frag, auxiliar);

return max_frag;


}
