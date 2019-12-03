nt elemento_activo_random, i, j;
//Convierto el vector de agentes en una matriz de agentes
elemento_activo_random = agente_activo;
i=elemento_activo_random/L; //columna   // n = i*L+j
j=elemento_activo_random%L; //fila

int i_izq, i_der, j_sup, j_inf;

//para primeros y segundo vecinos------
int random1, random2, aux1, aux2,aux3, agentes_seleccionados[3],random_selection;

//para vecinos estrella--------
int fila = elemento_activo_random/L;

int random_vecino;
int indice_vecino;
i_izq = i - 1;
i_der = i + 1;
j_sup = j - 1;
j_inf = j + 1;
int vecAux[] = {i_izq,i_der,j_inf,j_sup}; 
//int vecAux[] = {i_sup,i_inf,j_der,j_izq};
int auxiliar;

//-------------------------------------------------------------------------------------------------------------------------------
//--VECINOS ESTRELLA--

do
{
	random1 = rand() % 2;
} while ((vecAux[random1] <0) || (vecAux[random1] >=L));

do
{
	random2 = 2 + rand() % 2;
} while ((vecAux[random2] <0) || (vecAux[random2] >=L));


aux1 = vecAux[random1]*L + j;
aux2 = i*L + vecAux[random2];

//------------------------------------
if ( fila%2 == 0)
{
							if (vecAux[random2] == j_sup)
								{
									aux3 = vecAux[random2] + vecAux[random1]*L;
								} else if (vecAux[random2] == j_inf)
											{
												aux3 = -1;
											}
	
} else if ( fila%2 == 1) 
		{
							if (vecAux[random2] == j_inf)
								{
									aux3 = vecAux[random2] + vecAux[random1]*L;
								} else if (vecAux[random2] == j_sup)
											{
												aux3 = -1;
											}
		}
//-------------------------------------

agentes_seleccionados[0] = aux1;
agentes_seleccionados[1] = aux2;
agentes_seleccionados[2] = aux3;

do {

random_selection = rand() % 3;
if (random_selection == 0)
{
	indice_vecino = aux1;
}
else if (random_selection == 1)
{
	indice_vecino = aux2;
}
else if (random_selection == 2)
{
	indice_vecino = aux3;
}
 } while (indice_vecino < 0);

 //printf("%d    %d      %d       fila:%d\n", aux1,aux2,aux3,fila);


 
return indice_vecino;