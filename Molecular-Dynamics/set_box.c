
//Arreglo de celdas dentro de la celda principal
void set_box (float *posicion)
{
int n=(int)cbrt(N), i=0; //n=(int)cbrt(N) para que no sobren espacios
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
