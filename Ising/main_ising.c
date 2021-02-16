#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

/************constantes simbolicas*****************/
#define P 0.5
#define DIM 32
#define B 0
#define J 0.1
#define PASOS 100000
#define K 100
#define LONG 1000.0
#define INICIO 5000.0

/**********prototipos****************/
void poblar(int,float,int *);
int imprimir(int ,int *);
float prob_aceptacion (float);
float metropolis (int, int, float, int *, int);
float DeltaE (int, int *, float);
float magnetizacion_promedio(int *, int);
void correlacion(float *);


int main(){

srand(time(NULL));
int dim=DIM, red[DIM*DIM]={0};
float magnetizacion_promedio_vector[PASOS]={0},p=P, j=J;

poblar(dim,p,red);

for (int iter=0;iter<PASOS;iter++){
DeltaE(dim,red,j);
magnetizacion_promedio(red,dim);
magnetizacion_promedio_vector[iter]=magnetizacion_promedio(red,dim);
}

correlacion(magnetizacion_promedio_vector);

return 0;

}

/*******************************************************POBLAR****************************************************************/

void poblar(int dim, float p, int *red)

{
int i;
float random;

for(i=0;i<dim*dim;i++)
{
random = ((float)rand()/(float)RAND_MAX);

if (random<p){
     *(red+i)=-1;
} else {*(red+i)=1;}

}

}

/***********************************************************IMPRIMIR**************************************************************/

int imprimir (int dim, int *red)
{
int k;
int j;
for(j=0;j<dim;j++)
{
for(k=0;k<dim;k++)
{
printf("%5d",*(red+dim*j+k));
}
printf("\n\n");
}
return 0;
}

/*****************************************************PROBABILIDAD DE ACEPTACION******************************************************/

float prob_aceptacion (float DeltaE)
{
return (float)(exp(-DeltaE));
}

/********************************************************METROPOLIS***********************************************************/

float metropolis (int spin_random_i, int spin_random_j, float DeltE, int *red, int dim){

float random;

random=(float)rand()/(float)RAND_MAX;


if (random < prob_aceptacion(DeltE))
{

*(red+(dim*spin_random_i)+spin_random_j)=*(red+(dim*spin_random_i)+spin_random_j)*(-1);

return 1;
}else{
return 0;
}

}

/*******************************************************DeltaE******************************************************************/

float DeltaE (int dim, int *red, float j){

int spin_random_i=0,spin_random_j=0,up=0,down=0,right=0,left=0;
float DeltE=0;

//Selección random del spin
spin_random_i= rand() % dim;
spin_random_j= rand() % dim;

//Seleccion de los spines derredores del spin random
up=(spin_random_i-1+dim)%dim;
down=(spin_random_i+1+dim)%dim;
left=(spin_random_j-1+dim)%dim;
right=(spin_random_j+1+dim)%dim;

//Calculo la energia
DeltE=(float)(j*(*(red+(dim*spin_random_i)+spin_random_j)*(*(red+(dim*up)+spin_random_j)+*(red+(dim*down)+spin_random_j)+*(red+(dim*spin_random_i)+left)+*(red+(dim*spin_random_i)+right))));

//Acepto o no acepto el delta de energia con metrópolis
if ( DeltE < 0){
*(red+(dim*spin_random_i)+spin_random_j)=*(red+(dim*spin_random_i)+spin_random_j)*(-1);
} 
else metropolis(spin_random_i,spin_random_j,DeltE,red,dim);

return DeltE;
}

/*************************************************MAGNETIZACION********************************************************************/

float magnetizacion_promedio (int *red,int dim){

int magn=0;

for (int barrido=0;barrido<(dim*dim);barrido++){
magn=magn+*(red+barrido);

}

return (float)(magn)/(float)(dim*dim);

}

/****************************************************COEFICIENTE DE CORRELACION*************************************************/

void correlacion(float *magnetizacion_promedio_vector){

float suma1=0,suma2=0,suma3=0,termino1=0,termino2=0,termino3=0,coef=0,coef_suma[K]={0},coef_promedio=0;
int k;

//Agarro de a 1000 numeros 
for(int j=5000;j<PASOS;j=j+1000){

//Para una tira selecciono los k 
for(k=0;k<100;k++){

//Para cada valor de k calculo los terminos del coeficiente de correlacion
for(int i=j;i<((j+1000)-k);i++){ 
suma1=suma1+(magnetizacion_promedio_vector[i]*magnetizacion_promedio_vector[i+k]);
}
termino1=(float)suma1/(float)(1000-k);


//Para cada valor de k calculo los terminos del coeficiente de correlacion-recordar que termino2 lo uso dos veces
for(int m=j;m<(j+1000);m++){
suma2=suma2+magnetizacion_promedio_vector[m];
suma3=suma3+pow(magnetizacion_promedio_vector[m],2);
}

termino2=pow((float)suma2/(float)(1000),2);
termino3=(float)suma3/(float)(1000);

//Calculo el coeficiente de correlacion

coef=(float)(termino1-termino2)/(float)(termino3-termino2);

//Para cada valor de k sumo los coeficientes
coef_suma[k]=coef_suma[k]+coef;

//Limpio las variables
suma1=0;
suma2=0;
suma3=0;
termino1=0;
termino2=0;
termino3=0;
coef=0;

}

}

//cociente=(PASOS/LONG)-((INICIO/1000));
//Calculo el promedio dividiendo por la cantidad de intervalos

for(int l=0;l<k;l++){

coef_promedio=((float)coef_suma[l]/(float)95);

printf("Coef(k:%d)=%f\n",l,coef_promedio);

coef_promedio=0;

}

}
