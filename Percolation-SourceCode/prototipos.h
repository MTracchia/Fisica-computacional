#ifndef PROTOTIPOS
#define PROTOTIPOS

int poblar(int dim, float p, int *red);
int clasificar (int *red, int dim);
int actualizar (int *local, int *hist,int  frag, int s1);
int EtFals (int *red, int *hist, int s1, int s2, int i);
int corregir_etiqueta(int *red,int *hist,int dim, int s1);
void percolacion (int *red, int dim);
void Masa_y_cantidad_de_clusters (int *red, int dim);
int imprimir (int dim, int *red);

#endif