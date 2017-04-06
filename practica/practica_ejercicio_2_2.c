#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank, numprocs, filas, columnas, i, j, k;
	int reparto;
    MPI_Status status;
	
	//Tomo los parámetros y los guardo
	if (argc == 3) {
		filas = atoi(argv[1]);
		columnas = atoi(argv[2]);
		if (filas <= 0 || columnas <= 0) {
			printf("Parámetros no válidos.\n");
			exit(1);
		}
	}
	else {
		printf("Faltan parámetros.\n");
		exit(2);
	}
 
	//Inicializo el entorno
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
	//////// PUEDES PODER LA RESTRICCIÓN DE QUE EL COCIENTE FILAS/PROCESOS SEA ENTERO ////////
	
	int A[filas*columnas], B[filas*columnas], 
	//////// DEFINE LAS DEMÁS ESTRUCTURAS QUE CREAS CONVENIENTE ////////
	resultado[filas*columnas];
	

	if (rank == 0) {
		//Creo las matrices
		srand(1);
		for (i = 0; i < filas*columnas; i++) {
			A[i] = rand()%100;
			B[i] = rand()%100;
		}
		printf("Matriz A:\n");
		for (i = 0; i < filas*columnas; i++) {
			for (j = 0; j < columnas; j++) {
				printf("%d\t",A[i+j]);
			}
			printf("\n");
			i+=columnas-1;
		}
		printf("Matriz B:\n");
		for (i = 0; i < filas*columnas; i++) {
			for (j = 0; j < columnas; j++) {
				printf("%d\t",B[i+j]);
			}
			printf("\n");
			i+=columnas-1;
		}
		
		//////// PON AQUÍ TU CÓDIGO ////////
		/* REPARTE LAS FILAS ENTRE LOS PROCESOS,
		   REALIZA LA SUMA Y RECIBE LOS RESULTADOS
		   PARA JUNTARLOS Y MOSTRAR LA MATRIZ SUMA*/
		
		//Imprimo el resultado
		printf("Matriz A + B:\n");
		for (i = 0; i < filas*columnas; i++) {
			for (j = 0; j < columnas; j++) {
				printf("%d\t",resultado[i+j]);
			}
			printf("\n");
			i+=columnas-1;
		}
	}
	
	else {
		//////// PON AQUÍ TU CÓDIGO ////////
		/* RECIBE LAS FILAS A SUMAR, REALIZA LA SUMA
		Y DEVUELVE EL RESULTADO*/
		
	}
    MPI_Finalize();
    return 0;
}
