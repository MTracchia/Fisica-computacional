
int imprimir (int dim, int *red)
{
int k, j;
	
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
