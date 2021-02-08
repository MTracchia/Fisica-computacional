#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define RAND_MAX 2147483647	

#define L 3
#define F 4
#define Q 2

typedef struct agent
{
	int features[F];
} AGENT; 

void INITIALIZATION(AGENT grid[]);
int SIMILARITIES (AGENT grid[], int active_agent, int first_neighbour);
int ACTIVE_AGENT (void);
float HOMOPHILIA (int similarity);
int FIRST_NEIGHBOURS(int active_agent);
void INTERACTION (AGENT grid[], int active_agent, int first_neighbour_agent);
void AGENTS_ID (AGENT grid[]);
void FRAGMENTS_ID(AGENT grid[]);

int main()
{
	srand(time(NULL));
	AGENT grid[L*L];
	int active_agent = 0, first_neighbour_agent = 0;

	//grid =(int*)malloc(L*L*sizeof(struct agente));
	INITIALIZATION(grid);
	active_agent = ACTIVE_AGENT();
	first_neighbour_agent = FIRST_NEIGHBOURS(active_agent);
	INTERACTION(grid,active_agent,first_neighbour_agent);
	printf("active_agent:%d, first_neighbour:%d\n",active_agent,first_neighbour_agent);

	printf("\n");
		//ESTE FOR ES PARA IMPRIMIR EL ESTADO FINAL
		for (int i = 0; i < L*L; i++)
			{
				for (int j = 0; j < F; j++)
					{
						grid[i].features[j];
						printf("%4d",grid[i].features[j]);
					}
			printf("\n");
		}
		printf("\n");

	FRAGMENTS_ID(grid);
	AGENTS_ID(grid);
	return 0;
}


//*************************************************INITIALIZATION*************************************************
void INITIALIZATION (AGENT grid[])
	{
		for (int i = 0; i < L*L; i++)
			{
				for (int j = 0; j < F; j++)
					{
						/*Each attribute is assigned a value between 0 and Q*/
						grid[i].features[j] = rand() % Q;
						printf("%4d",grid[i].features[j]);
					}
			printf("\n");
		}
		printf("\n");
	}
//*************************************************SIMILARITIES*************************************************
int SIMILARITIES (AGENT grid[], int active_agent, int first_neighbour)  
	{
		/*This function returns the number of equals attributes of the two agents selected*/
		int similarity = 0;
		for (int i = 0; i < F; i++)
			{  
				if (grid[active_agent].features[i] == grid[first_neighbour].features[i])
					{
						similarity++;
					}
			}
		return similarity;	
	}
//*************************************************ACTIVE-AGENT*************************************************
int ACTIVE_AGENT (void)
	{
		/*Generation of a random number from 0 to L*L for select an agent.*/
		return (rand() % (L*L));
	}
//*************************************************HOMOPHILIA*************************************************
float HOMOPHILIA (int similarity)
	{
		return ((float)similarity/(float)F);
	}
//*************************************************FIRST-NEIGHBOURS*************************************************
int FIRST_NEIGHBOURS(int active_agent)
	{	
		/*I turn the "active_agent" (from a vector) to matrix notation of the form  n = i*L+j 
		in "i" and "j" through the "/" and "%" division*/
		int i=active_agent/L;
		int j=active_agent%L;
		/*Calculate the first_neighbour_agent*/
		int i_left = i - 1;
		int i_right = i + 1;
		int j_up = j - 1;
		int j_down = j + 1;
		/*First neighbours vector*/
		int vecNeigh[] = {i_left,i_right,j_up,j_down};
		int first_neighbour = 0,random_fn = 0;
		/*SELECTION PROCESS*/
		do {
				random_fn = rand() % 4; 
			} while ( (vecNeigh[random_fn] <0) || (vecNeigh[random_fn] >=L));
		if (random_fn == 0)
			{first_neighbour = vecNeigh[random_fn]*L + j;} 
				else if (random_fn == 1)
					{first_neighbour = vecNeigh[random_fn]*L + j;}
						else if (random_fn == 2)
							{first_neighbour = i*L + vecNeigh[random_fn];}
								else if (random_fn == 3){first_neighbour = i*L + vecNeigh[random_fn];}
		return first_neighbour;
	}
//*************************************************INTERACTION*************************************************
void INTERACTION (AGENT grid[], int active_agent, int first_neighbour_agent)
	{
		int similarity = 0,random_feature = 0;
		float homophilia = 0.0, random_for_prob_interaction = 0.0;
		/*Similirity is the amount of attributes of the agents.*/
		similarity = SIMILARITIES(grid,active_agent,first_neighbour_agent);
		/*Homophilia is the degree of kinship of the two agents.*/
		homophilia = HOMOPHILIA(similarity);
		/*This random number serves for compare it with the homophilia.*/
		random_for_prob_interaction = (float)rand()/(float)RAND_MAX;
		/*INTERACTION PROCESS. Note that if the agents are exactly equals there's no interaction.*/
		if((random_for_prob_interaction < homophilia)  && (similarity != F))			
			{	
				do {random_feature = rand() % F;} 
					while (grid[active_agent].features[random_feature] == grid[first_neighbour_agent].features[random_feature]);
				grid[active_agent].features[random_feature] = grid[first_neighbour_agent].features[random_feature];
				printf(" similarity:%d,   homophilia:%f\n", similarity, homophilia);
			} 
	}
//*************************************************AGENTS-ID*************************************************
void AGENTS_ID (AGENT grid[])
	{
		int elements[L*L] = {0}, frag_ag = 0, sim = 0, count_k = 0;
		for (int i = 1; i < L*L; i++)  /*This takes the comparator element*/
			{
				count_k = i+1; /*if all the elements compared are different from the index element i increases the value of frag*/
				for (int k = 0; k < i; k++) /*Here I always move from the beginning to the element compared*/
					{
						for (int j = 0; j < F; j++)
							{
								if (grid[i].features[j]==grid[k].features[j])
									{
										sim++;
									}
								}
						if (sim == F)
							{
								elements[i] = elements[k];
								count_k--;
							}
						sim = 0;
					}			
				if (count_k == (i + 1))
					{
						frag_ag++;
						elements[i] = frag_ag;
					}
			}	
	
	//PARA IMPRIMIR LOS AGENTES CLASIFICADOS
	for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
				{	
					printf("%4d  ", *(elements + L*i + j));
				}
	printf("\n\n");
		}
	}

//*************************************************FRAGMENTS-ID*************************************************
void FRAGMENTS_ID(AGENT grid[]) 
	{
		int s1 = 0, s2 = 0, frag = 2, nodes[L*L] ,sim = 0, sim1 = 0 ,sim2 = 0 ,min = 0, max = 0, hist[L*L];
		//Inicilializo con ceros el vector de nodes
		for (int m = 0; m < L*L; m++)
			{
				nodes[m] = 0;
			}
		//primer valor de "nodes" es igual frag = 2
		nodes [0] = frag;
		//Incilizacion del vector historial
		for (int i = 0; i < L*L; i++) {*(hist + i) = i;}
		//Segmento de codigo que agregue etiquetas a la primera fila 
		for (int j = 1; j < L; j++)
			{
				for (int k = 0; k < F; k++)
					{
						if (grid[j-1].features[k] == grid[j].features[k])
							{
								sim++;
							}	
					}
				if (sim == F)
					{
						if (*(hist + nodes[j]) < 0)
     				   		{
            					nodes[j] = -(*(hist + nodes[j])); 
        					}
						nodes[j] = nodes[j-1];
					} else {
								frag++;
								nodes[j] = frag;
							}
				sim = 0 ;
			}

		//Corrijo etiqueta pero por columna respecto del primer elemento
		for (int j = 1; j < L; j++)
			{
				for (int k = 0; k < F; k++)
					{
						if (grid[j*L-L].features[k] == grid[j*L].features[k])
							{
								sim++;
							}	
					}
			if (sim == F)
				{
					if (*(hist + nodes[j*L]) < 0)
        				{
            				nodes[j*L] = -(*(hist + nodes[j*L])); 
        				}
			nodes[j*L] = nodes[j*L-L];
				} else {
							frag++;
							nodes[j*L] = frag;
						}
		sim = 0 ;

	//Aca comenzaria el proceso de comparacion para agregar etiquetas 

	//Me muevo de izq a der -- las filas estan fijadas por j
	for (int i = 1; i < L; i++)
	{
		//Comparo features
		for (int iter = 0; iter < F; iter++)
			{
				//s2 = *(grid+j+i*dim-dim);  arriba                       
				//s1 = *(grid+j+i*dim-1);  abajo
				//los elementos que tomo
				grid[i+j*L-L].features[iter];	//arriba
				grid[i+j*L-1].features[iter];  //abajo
				grid[i+j*L].features[iter]; //Elemento que comparo

			//Comparo componente a componente los tres agentes
				if (grid[i+j*L].features[iter] == grid[i+j*L-1].features[iter]) //abajo
					{
						sim1++;
					}

				if (grid[i+j*L].features[iter] == grid[i+j*L-L].features[iter]) //arriba
					{
						sim2++;
					}
		
			}
		
			//Asigno etiqueta al elemento comparador(todavia no es sseguro si es la original)
			//se analizan los distintos casos
			if (sim1 == F && sim2 != F)
				{
					nodes[i+j*L] = nodes [i+j*L-1];
				}

			else if (sim1 != F && sim2 == F)
				{
					nodes[i+j*L] = nodes [i+j*L-L];
				}	

			else if (sim1 != F && sim2 != F)
				{
					frag++;
					nodes[i+j*L] = frag;
				}
			
			else if (sim1 == F && sim2 == F)
				{
					if (nodes[i+j*L-1] == nodes[i+j*L-L])
						{
							nodes[i+j*L] = nodes[i+j*L-1];		
						} 	
					else if (nodes[i+j*L-1] < nodes[i+j*L-L])
					{					
						if (*(hist + nodes[i+j*L-1])<0)
    							{
      								nodes[i+j*L-1] = -(*(hist + nodes[i+j*L-1]));
   	 							}
						if (*(hist + nodes[i+j*L-L])<0)
    							{
      								nodes[i+j*L] = -(*(hist + nodes[i+j*L]));
   								}

						min = nodes[i+j*L-1];
						max = nodes[i+j*L-L];							
							
						nodes[i+j*L] = min;
						*(hist + max) = -min;
						*(hist + min) = min;
					}	
				else if (nodes[i+j*L-1] > nodes[i+j*L-L])
					{
							
							if (*(hist + nodes[i+j*L-1])<0)
    							{
      								nodes[i+j*L-1] = -(*(hist + nodes[i+j*L-1]));
   	 							}
  
							if (*(hist + nodes[i+j*L-L])<0)
    							{
      								nodes[i+j*L] = -(*(hist + nodes[i+j*L]));
   								}
			
						max = nodes[i+j*L-1];
						min = nodes[i+j*L-L];							
							
						nodes[i+j*L] = min;
						*(hist + max) = -min;
						*(hist + min) = min;				
					}
				}

		sim1 = 0;
		sim2 = 0;
	}
			}


	//PARA CORREGIR ETIQUETA A PARTIR DEL VECTOR HISTORIAL
	for (int corr = 0; corr < L*L; corr++)
		{
	    	s1=*(nodes+corr);
	        while (*(hist+s1)<0)
	            {
	              s1=-(*(hist+s1));
	            }
	     	*(nodes+corr)=s1;
	}

	//PARA IMPRIMIR LOS FRAGMENTOS CLASIFICADOS
	for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
				{	
					printf("%4d  ", *(nodes + L*i + j));
				}
			printf("\n\n");
		}
	printf("\n\n");
	//PARA IMPRIMIR EL VECTOR HISTORIAL
	for (int imp = 0; imp < L*L; imp++)
		{
			printf("%4d", *(hist + imp));
		}
	printf("\n\n");

	}

