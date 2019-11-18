#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define L 10
#define F 4


struct agente
{
int atributos[F];
};


int main()
{

struct agente red[L*L];

//red =(int*)malloc(L*L*sizeof(struct agente));
//*(red+3)->atributos[4]=3;	

//Arrancar con inicializacion

red[12].atributos[3]=6;
printf("%d\n",red[12].atributos[3]);

return 0;
}
