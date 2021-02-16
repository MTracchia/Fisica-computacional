#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

/******Prototipos******/

float random_walk (float);
float prob_aceptacion(float *, int);
float aceptados (float);

int main()
{

FILE *fp;
fp=fopen("DATA1a.dat","w");

float aceptados_porciento=0, delta, random;
int i=0,k;
const int N=101;

for (delta=0.0;delta<10.0;delta=delta+0.01)
{
	printf("%f      %f\n", delta, aceptados(delta));
	fprintf(fp,"%f               %f\n",delta, aceptados(delta));
}

//for(k=0;k<N+1;k++){
//printf("%f   %f\n",*(vecX+k),exp(-pow(*(vecX+k),2)/2));     //imprimo vector de posiciones 
//fprintf(fp,"%f   %f\n",*(vecX+k),exp(-pow(*(vecX+k),2)/2));
//}
fclose(fp);
//printf("%f", random_walk());

return 0;
}

/****************************PASO X********************************/

float random_walk (float delta)

{
float random, paso;
//random=rand()%2;
random=1.0*rand()/RAND_MAX;
paso=(((2*random)-1)*delta);
return paso;
}

/*****************PROBABILIDAD DE ACEPTACION***************************/

float prob_aceptacion (float *vecX,int i)

{
return (float)(exp(-pow(*(vecX+(i+1)),2)/2)/exp(-pow(*(vecX+i),2)/2));
}


float aceptados (float delta){
int i=0, aceptados1=0;
float vecX[10001]={0}, random=0, acep_porciento;

srand(time(NULL)); 
while (i<10000)

{
vecX[i+1]=vecX[i]+random_walk(delta);
random=(float)rand()/(float)RAND_MAX;

if (random < prob_aceptacion(vecX,i))
{
aceptados1++;
}else{
vecX[i+1] = vecX[i];
}
i++;
} 

acep_porciento=((float)aceptados1/(float)10000.0);
return acep_porciento;

}
