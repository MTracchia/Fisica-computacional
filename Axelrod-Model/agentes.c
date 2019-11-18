#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define L 10
#define F 4
#define Q 20	



struct agente
{
int atributos[F];
};


int main()
{

srand(time(NULL));
struct agente red[L*L];
int q = 20, q_value = 0;

//red =(int*)malloc(L*L*sizeof(struct agente));
//*(red+3)->atributos[4]=3;	


//Inicializa los estados de los agentes y también los imprime
for (int i = 0; i < L*L; i++)
{
	for (int j = 0; j < F; j++)
	{
		q_value = rand() % Q;
		red[i].atributos[j]=q_value;
		printf("%5d",red[i].atributos[j]);
	}
printf("\n");
}

return 0;
}
