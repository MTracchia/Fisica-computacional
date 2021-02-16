#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define N 216     //SIEMPRE MULTIPLE DE ELEVADO AL CUBO!!
#define L 10
#define T 2.0
#define MASA 1.0
#define RC 2.5
#define H 0.001
#define POINTS 5000
#define R0 0.1

//-------------------Prototipos----------------------
void set_box (float *);
float Random (void);
float gaussiana(float, float);
float set_v (float *);
void Delta_X (float *, float *,float *);
void tabla (float *Vlj, float *Flj, float *r, float *r2);
float interaccion (float *, float *, float *, float *, float *);
void verlet (float *,float *,float *,float *, float *,float *);
int save_lammpstrj(char *filename, float* x, float* v, int frame);

float max_norm(float *f){
	float res = 0, norma;
	for(int i = 0; i < N; i++){
		norma = 0;
		for(int k = 0; k < 3; k++){
			norma += f[3*i+k]*f[3*i+k];
		}
		norma = sqrt(norma);
		if(norma > res)	res = norma;
	}
	return res;
}


int main()
{

float *posicion, *velocidad,*fuerzas,*fuerza_vieja,*Vlj,*Flj,*r,*r2;

srand(time(NULL));

posicion=(float *)malloc(3*N*sizeof(float));
velocidad=(float *)malloc(3*N*sizeof(float));
fuerzas=(float *)malloc(3*N*sizeof(float));
fuerza_vieja=(float *)malloc(3*N*sizeof(float));
Vlj=(float *)malloc(POINTS*sizeof(float));
Flj=(float *)malloc(POINTS*sizeof(float));
r=(float *)malloc(POINTS*sizeof(float));
r2=(float *)malloc(POINTS*sizeof(float));


//inicializa a cero los vectores fuerzas r Flj y Vlj
for (int m=0;m<POINTS;m++)
{
	
	*(r+m)=0.0;
	*(Flj+m)=0.0;
	*(Vlj+m)=0.0;
}


set_box(posicion);
set_v(velocidad);
tabla(Vlj,Flj,r,r2);


for (int t=0;t<500;t++)
{

//printf("%f\n",*(Vlj+t));
verlet(fuerza_vieja,fuerzas,posicion,velocidad,Flj,Vlj);
save_lammpstrj("mi_archivo.lammpstrj",posicion,velocidad,t);


}

free(posicion);
free(velocidad);
free(fuerzas);
free(fuerza_vieja);
free(Vlj);
free(r);
free(Flj);
free(r2);

return 0;
}

//----------------------------------INICIALIZACION DE POSICIONES----------------------------------

void set_box (float *posicion)

{

int n=(int)cbrt(N), i=0;
float dl=(float)L/cbrt(N);    

for (int x=0;x<n;x++)

 {	
	for (int y=0;y<n;y++)
		
	   {	
		for (int z=0;z<n;z++)

		    {  
			 *(posicion + 3*i)=(float)(dl*((float)x+0.5));
			 *(posicion + 3*i+1)=(float)dl*((float)y+0.5);
			 *(posicion + 3*i+2)=(float)dl*((float)z+0.5);
		     i++;
		    }

	     }
  
  }


}

//-------------------------FUNCION RANDOM-------------------------------

float Random (void) {return ((float)rand()/(float)RAND_MAX);}  

//-----------------------FUNCION GAUSSIANA----------------------

float gaussiana (float nu, float sigma)

{
int n=10;
float z=0.0;

for (int i=0;i<n;i++) z+=Random();
z=sqrt(12.0*(float)n)*(z/(float)n-0.5);
return (z*sigma+nu);
}

//-----------------------INICIALIZACION DE VELOCIDADES-----------------

float set_v (float *velocidad)

{
float sigma=sqrt(T);
for (int i=0; i<3*N; i++) *(velocidad+i)=gaussiana(0.0,sigma);

//Esto es para restar la velecidad de cada particula la Vcm en cada componente

float Vcm[3]={0.0,0.0,0.0};

for (int i=0;i<N;i++)
    {
	 for (int k=0;k<3;k++) *(Vcm+k)+=(*(velocidad+3*i+k)/(float)N);
    }

for (int i=0;i<N;i++)

    { 
	 for (int k=0;k<3;k++) *(velocidad+3*i+k)-=*(Vcm+k);
    }

//Calculo la energia cinetica (total)

float Ec=0.0;
     
for (int m=0;m<3*cbrt(N);m++) Ec=Ec+*(velocidad+m)**(velocidad+m)*0.5*MASA;
    
return (Ec/(float)N);

}

//---------------------------Delta_X-------------------------------

void Delta_X (float *x_1, float *x_2, float *delta)
{
	int k;
//al invocar en el main pasarlo con los indices
	for(k=0;k<3;k++) {                                  
		
		delta[k]=(*(x_1+k))-(*(x_2+k));                      
		
		if(delta[k]>0.5*(float)L) delta[k]=delta[k]-(float)L;
					             
		else{
				if(delta[k]<-0.5*(float)L) delta[k]=delta[k]+(float)L;			   				
		    }

			     		}


}

//-----------------------TABLA DE FUERZAS----------------------------

void tabla (float *Vlj, float *Flj, float *r, float *r2)
{
	
	float dl=(float)(RC-R0)/(float)POINTS;
	float inversa_r,r3,r6,rc3,rc6,inversa_rc;
	
	for (int i=0;i<POINTS;i++)
	{
		*(r+i)=(float)i*dl+R0;
		*(r2+i)=(i*dl)*(i*dl)+R0*R0+2.0*(float)i*dl*R0;
		//*(Vlj+i)=(float)2.0;  //potencial ficticio
		
		inversa_r=1.0/(*(r+i));
		r3=inversa_r*inversa_r*inversa_r;
		r6=r3*r3;
		inversa_rc=1.0/((float)POINTS*dl+R0);
		rc3=inversa_rc*inversa_rc*inversa_rc;
		rc6=rc3*rc3;

		*(Vlj+i)=4.0*(r6*r6-r6)-4.0*(rc6*rc6-rc6);
		
		*(Flj+i)=24.0*inversa_r*(2.0*r6*r6-r6);
	}


}

//------------------------INTERACCION--------------------------------

float interaccion (float *posicion, float *Flj, float *fuerzas, float *Vlj, float *fuerza_vieja)

{
  float norma2,delta[3],Dx,Dy,Dz;
  float dl=(float)(RC-R0)/(float)POINTS,ep=0.0,Fx,Fy,Fz;
  float norma;
  int indice;

  for (int ini=0;ini<3*N;ini++) 

	{
		*(fuerza_vieja+ini)=*(fuerzas+ini);
		*(fuerzas + ini)=0.0;
	}
	
	for (int i=0; i<N-1;i++)
	{

		for (int j=i+1;j<N;j++)
			{
				Delta_X(posicion+3*i+0,posicion+3*j+0,delta);
				Dx=delta[0];
				Dy=delta[1];
				Dz=delta[2];
				norma2=Dx*Dx+Dy*Dy+Dz*Dz;
				norma=(float)sqrt((double)norma2); 
				if (norma<RC) 
				{

					//printf("%f       %f\n",norma,norma2 );
					
					indice=(int)((norma-R0)/dl);
					Fx=Dx*(*(Flj+indice))/norma;
					Fy=Dy*(*(Flj+indice))/norma;
					Fz=Dz*(*(Flj+indice))/norma;
					ep+=(*(Vlj+indice));

					*(fuerzas+3*i+0)+=Fx;
					*(fuerzas+3*i+1)+=Fy;
					*(fuerzas+3*i+2)+=Fz;

					*(fuerzas+3*j+0)-=Fx;
					*(fuerzas+3*j+1)-=Fy;
					*(fuerzas+3*j+2)-=Fz;
				}
			}

}

return (ep/(float)N);

}

//-------------------------------ALGORITMO DE VERLET---------------------------------

void verlet (float *fuerza_vieja,float *fuerzas,float *posicion,float *velocidad,float *Vlj,float *Flj)

{
	
float Ep,Ec = 0.0;

	for (int i=0;i<3*N;i++)
	{
		*(posicion+i)=*(posicion+i)+(*(velocidad+i))*H+0.5*((*(fuerzas+i))*H*H/(float)MASA);

		if (*(posicion+i)>(float)L) *(posicion+i)-=(float)L;
		     else if (*(posicion+i)<0.0) *(posicion+i)+=(float)L;
	}

Ep=interaccion(posicion,Flj,fuerzas,Vlj,fuerza_vieja);

for (int j=0;j<3*N;j++)
	{
		*(velocidad+j)=*(velocidad+j)+(*(fuerza_vieja+j)+(*(fuerzas+j)))*H/2.0;
		Ec += 0.5**(velocidad+j)**(velocidad+j)/(float)N;
//		printf("%f\n",*(fuerzas + j));
	}


printf("%f\n",Ec+Ep);

}


int save_lammpstrj(char *filename, float* x, float* v, int frame){
  FILE *fp;
  if (frame) fp = fopen(filename, "a"); // Si frame==0, es el primero y por lo tanto
  else fp = fopen(filename, "w");       // tiene que crear un nuevo archivo
  // Header que usa lammps
	fprintf(fp, "ITEM: TIMESTEP\n%d\nITEM: NUMBER OF ATOMS\n%d\nITEM: BOX BOUNDS pp pp pp\n", frame, N);
	for(int l = 0; l < 3; l++){
		fprintf(fp, "0 %f\n", (float)L); // Limites de la caja en x-y-z
	}
	fprintf(fp, "ITEM: ATOMS id x y z vx vy vz \n"); // "Nombre de las columnas"
	for(int i = 0; i < N; i++){
		fprintf(fp, "%d %f %f %f %f %f %f\n", i, x[3*i], x[3*i+1], x[3*i+2], v[3*i], v[3*i+1], v[3*i+2]);
	}
  fclose(fp);
  return 0;
}