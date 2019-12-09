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
	}