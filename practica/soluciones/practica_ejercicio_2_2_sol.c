#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank, numprocs, filas, columnas, i, j, k, indice=0;
	int reparto;
    MPI_Status status;
	
	//Tomo los parámetros y los guardo
	if (argc == 3) {
		filas = atoi(argv[1]);
		columnas = atoi(argv[2]);
		if (filas == 0 || columnas == 0) {
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
 
	if (((float)filas/(float)numprocs) - filas/numprocs != 0) {
		printf("El cociente filas/procesos no es entero.\n");
		MPI_Finalize();
		exit(3);
	}
	
	reparto = filas/numprocs;
	int A[filas*columnas], B[filas*columnas], 
	filasAB[columnas*2*reparto],
	filasASumar[columnas*2*reparto],
	filasSuma[columnas*reparto],
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
		
		//Envío las filas a sumar
		for (k = 0; k < numprocs; k++) {
			//Creo un array con las filas de A y B a sumar por cada proceso
			for (i = 0; i < columnas*reparto; i++) {
				filasAB[i] = A[i+columnas*reparto*k];
			}
			for (i = 0; i < columnas*reparto; i++) {
				filasAB[i+columnas*reparto] = B[i+columnas*reparto*k];
			}
			
			/*printf("Tarea para el proceso %d:\n",k);
			for (i = 0; i < columnas*2*reparto; i++) {
				printf("%d|",filasAB[i]);
			}printf("\n");*/
			//Envío el array
			if (k == 0)
				MPI_Sendrecv(&filasAB[0], columnas*2*reparto, MPI_INT, k, 123, 
					filasASumar, columnas*2*reparto, MPI_INT, k, 123, 
					MPI_COMM_WORLD, &status);
			else
				MPI_Send(&filasAB[0], columnas*2*reparto, MPI_INT, k, 123, MPI_COMM_WORLD);
		}
		//Sumo la parte que le toca al proceso 0 y lo meto en la solución
		for (i = 0; i < columnas*reparto; i++) {
			resultado[i] = filasASumar[i] + filasASumar[i+columnas*reparto];
		}
		/*printf("Resultado del proceso 0:\n");
			for (i = 0; i < columnas*reparto; i++) {
				printf("%d|",resultado[i]);
			}printf("\n");*/
		//Espero el resultado del resto y lo voy añadiendo a la solución
		for (k = 1; k < numprocs; k++) {
			MPI_Recv(filasSuma, columnas*reparto, MPI_INT, k, 123, MPI_COMM_WORLD, &status);
			for (i = 0; i < columnas*reparto; i++)
				resultado[i + columnas*reparto*k] = filasSuma[i];
		}
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
		//Recibo las filas a sumar
		MPI_Recv(filasASumar, columnas*2*reparto, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
		//Sumo las filas
		for (i = 0; i < columnas*reparto; i++) {
			filasSuma[i] = filasASumar[i] + filasASumar[i+columnas*reparto];
		}
		/*printf("Resultado del proceso %d:\n",rank);
			for (i = 0; i < columnas*reparto; i++) {
				printf("%d|",filasSuma[i]);
			}printf("\n");*/
		//Envío de vuelta el resultado
		MPI_Send(&filasSuma[0], columnas*reparto, MPI_INT, 0, 123, MPI_COMM_WORLD);
		
	}
/*
    MPI_Send(&myid, 1, MPI_INT, left, 123, MPI_COMM_WORLD);
	MPI_Recv(buffer, 1, MPI_INT, right, 123, MPI_COMM_WORLD, &status);
    printf("Proc %d - Sent: %d, Received: %d.\n", myid, myid, buffer[0]);
	*/
    MPI_Finalize();
    return 0;
}
