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

	return 0;
}


//*************************************************INITIALIZATION*************************************************
void INITIALIZATION (AGENT grid[])
	{
		for (int i = 0; i < L*L; i++)
			{
				for (int j = 0; j < F; j++)
					{
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
		/*I generate a random number from 0 to L*L called "random_active_element" (from a vector).
		Then, turn it to matrix notation of the form  n = i*L+j in "i" and "j" through the "/" and "%" division*/
		int i=active_agent/L;
		int j=active_agent%L;
		int first_neighbour, random_neighbour,random_fn;
		/*Calculate the first_neighbours*/
		int i_left = i - 1;
		int i_right = i + 1;
		int j_up = j - 1;
		int j_down = j + 1;
		/*First_neighbours*/
		int vecNeigh[] = {i_left,i_right,j_up,j_down};
		/*SELECTION PROCESS*/
		do {
				random_fn = rand() % 4; 
			} while ( (vecNeigh[random_fn] <0) || (vecNeigh[random_fn] >=L));
		random_neighbour = vecNeigh[random_fn];
		if (random_fn == 0)
			{first_neighbour = random_neighbour*L + j;} 
				else if (random_fn == 1)
					{first_neighbour = random_neighbour*L + j;}
						else if (random_fn == 2)
							{first_neighbour = i*L + random_neighbour;}
								else if (random_fn == 3){first_neighbour = i*L + random_neighbour;}
		return first_neighbour;
	}

//*************************************************INTERACTION*************************************************
void INTERACTION (AGENT grid[], int active_agent, int first_neighbour_agent)
	{
		int similarity = 0,random_feature = 0;
		float homophilia = 0.0, random_for_prob_interaction = 0.0;
		
		similarity = SIMILARITIES(grid,active_agent,first_neighbour_agent);
		homophilia = HOMOPHILIA(similarity);
		
		random_for_prob_interaction = (float)rand()/(float)RAND_MAX;
		

		if((random_for_prob_interaction < homophilia)  && (similarity != F))			
			{	
				do {random_feature = rand() % F;} 
					while (grid[active_agent].features[random_feature] == grid[first_neighbour_agent].features[random_feature]);
				grid[active_agent].features[random_feature] = grid[first_neighbour_agent].features[random_feature];
				printf(" similarity:%d,   homophilia:%f\n", similarity, homophilia);
				

				//Forma antigua de cambiar los atributos en caso de interaccion
				/*
				for (int j = 0; j < F ; j++)
					{
		   				if (grid[0].features[j] != grid[1].features[j])
		   					{   							
			   					vector_diferencias[diferencias] = j;
			   					diferencias++;
		   					}
					}	
				componente_random = rand() % diferencias; 
				atributo_seleccionado = vector_diferencias[componente_random];
				grid[0].features[atributo_seleccionado]=grid[1].features[atributo_seleccionado];
				*/ 
	
			} 
	}























