
/*
Este procedimiento imprime en pantalla la masa (M) del cluster (C) de 
la forma Cl(C)--M:(M). También imprime cuántos clusters de masa M hay en 
la red de la forma M:(M)--#Cantidad.
*/

void clusters (int *red, int dim)

{

int i, j, k, l, m, x = 0,y = 0, vecM[dim*dim], vecC[dim*dim+1];


//Inicializo los vectores masa M y cantidad C
for (i=0;i<dim*dim+1;i++)
	{   
		vecM[i]=0; 
		vecC[i]=0;
	}

//Para el vector de masas-Sus posiciones son las etiquetas
for (j=0;j<dim*dim;j++)  
	{
		x=*(red+j);
		vecM[x]=vecM[x]+1;
	}

//Para el vector de cantidades-Sus posiciones son las masas
for (l=2;l<dim*dim+1;l++) 
	{
		y=*(vecM+l);
		vecC[y]=vecC[y]+1;
	}


//Para que imprima el vector de masas
for (k=2;k<dim*dim;k++) 
	{
		if(vecM[k])
			{
				printf("Cl%d--M:%d  ",k,vecM[k]);
			}
	}

printf("\n\n");

//Para que imprima el vector de cantidades
for (m=1;m<dim*dim+1;m++) 
	{
		if(vecC[m])
			{
				printf("M:%d--#%d  ",m, vecC[m]);
			}
	}

printf("\n\n");

}
