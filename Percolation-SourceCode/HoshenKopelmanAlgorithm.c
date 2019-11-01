
//Acá están todas las funciones asociadas con el algoritmo de Hoshen Kopelman


//-----------------CLASIFICAR---------------------

int clasificar (int *red, int dim)
{

int frag=2, s1, s2;
//int s1, s2;
int N = dim*dim;
int hist[N];

//int *hist = (int *) malloc(dim*dim*sizeof(int)); - Vector historial con memoria dinámica 

//iteradores
int i;
int j;
int k;

//vector historial
for (k=0;k<dim*dim;k++){*(hist+k)=k;}
  
if (*red)
  {
    *(red)=frag;
    frag++;
  }

for (i=1;i<dim;i++)
  {
    s1 = *(red+i-1);
    frag=actualizar(red+i, hist, frag, s1);
  }

for (i=1;i<dim;i++)
{
  s2 = *(red+i*dim-dim);   //elementos de la primera columna.
  frag=actualizar(red+dim*i,hist,frag,s2);   //primer valor que entra: elementos de la primera columna adelantados un paso respecto de s2.

 for (j=1;j<dim;j++)
  {
   s1 = *(red+j+i*dim-1);  //elementos de cada columna adelantados un paso 
   s2 = *(red+j+i*dim-dim);  //primeros elementos de cada columna

    if (s1*s2){ 
          EtFals(red, hist, s1, s2, i*dim+j);
              }   
     else      
          
          if (s1) {
             frag=actualizar (red+i*dim+j, hist,frag,s1);   
                  }
   
          else  {
              frag=actualizar (red+i*dim+j, hist,frag,s2);   
                }
    }
}
corregir_etiqueta(red, hist, dim, s1);

return 0;
}


//-----------------ACTUALIZAR---------------------

int actualizar (int *local, int *hist,int  frag, int s1)
{
 
if (*local)
{
  if (s1)
    {
      while (*(hist + s1) < 0)
        {
            s1 = -(*(hist + s1)); 
        }
  *local=s1; 
    }

  else
    {
      *local=frag;
      frag++;
    }
}

return frag;
}



//-----------------ETIQUETA FALSA---------------------

int EtFals (int *red, int *hist, int s1, int s2, int i)  
{
if (*(red+i)) 
{
int min, max;
  
while (*(hist + s1)<0)
    {
      s1 = -(*(hist + s1));
    }
  
while (*(hist + s2)<0)
    {
      s2 = -(*(hist + s2));
    }

if (s1<s2)
    {
      min = s1;
      max = s2;
    }

else 
    {
      min = s2;
      max = s1;
    }

if (min<max)
  { 
    *(red + i) = min;
    *(hist + max) = -min;
    *(hist + min) = min;
  }

else 
  {
    *(red + i) = min;
    *(hist + max) = min;
    *(hist + min) = min;
  }
}

return 0;
}


//-----------------CORREGIR ETIQUETA---------------------

int corregir_etiqueta(int *red,int *hist,int dim, int s1)
{
   int i;
  
   for(i=0;i<dim*dim;i++)
     {
        s1=*(red+i);
        while (*(hist+s1)<0)
            {
              s1=-(*(hist+s1));
            }
     *(red+i)=s1;
     }
   
return 0;
}

