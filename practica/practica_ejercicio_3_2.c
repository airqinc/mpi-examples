#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

void delay(unsigned int mseconds);

int main(int argc, char** argv){

	srand(100);

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
	
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(argc!=3 && rank==0){
            printf("\n >> Wrong params...\n");
			printf(" >> A( m x n ) * B( n x p ) = C( m x p )\n");
			printf(" >> Usage: mpiexec -n [numProcesses = dimM] ./ejercicio4 [dimN] [dimP]\n\n");
            MPI_Finalize();
            exit(0);
    }
	else if(argc!=3){ MPI_Finalize(); exit(0);}

    //Get the params
    int dim_m = size;
    int dim_n = atoi(argv[1]);
	int dim_p = atoi(argv[2]);

	//Reservamos espacio de memoria para todas las matrices (allocation)
	float random;
	float valor;
    int i,j;

	float *matrixA = (float*) malloc( dim_m * dim_n * sizeof( float ));
	float *matrixB = (float*) malloc( dim_n * dim_p * sizeof( float ));
	float *matrixC = (float*) malloc( dim_m * dim_p * sizeof( float ));

	//Creamos la matriz si somos el proceso 0
	
	if(rank==0){
		printf(" \n >> Procesador %s, proceso %d de %d procesos existentes.\n >> Tengo que multiplicar dos matrices de dimensiones: A ( %d x %d ) y  B ( %d x %d )\n",processor_name, rank, size, dim_m, dim_n, dim_n, dim_p);
		//Crear la matriz A
		for (i=0;i<dim_m;i++){
			for(j=0;j<dim_n;j++){
				random = (float)rand()/(float)RAND_MAX;
				random = random*10;
				matrixA[i * dim_n + j]= random;
			}
		}

		//Crear la matriz B
		for (i=0;i<dim_n;i++){
			for(j=0;j<dim_p;j++){
				random = (float)rand()/(float)RAND_MAX;
				random = random*10;
				matrixB[i * dim_p+ j]= random;
            }
		}

		//Imprimir la matriz A
		printf("\n >> A matrix is...\n\n");
		for (i=0;i<dim_m;i++){
			printf("| ");
			for(j=0;j<dim_n;j++){
				valor=matrixA[i * dim_n + j];
				printf("%f\t",valor);
            }
			printf("|\n");
		}

		//Imprimir la matriz B
		printf("\n >> B matrix is...\n\n");
		for (i=0;i<dim_n;i++){
			printf("| ");
			for(j=0;j<dim_p;j++){
				valor=matrixB[i * dim_p+ j];
				printf("%f\t",valor);
	            }
			printf("|\n");
		}
	}

	//Apartado 1: Envía la matriz B a todos los procesos, imprimela con cada proceso [utiliza delay(1000*rank) para que la salida se vea ordenada]

	//Apartado 2: Envía una fila de la matriz A a cada proceso e imprime el buffer recibido para comprobar que funciona

	//Apartado 3: Calcula la matriz e imprimela con el proceso 1

	if(rank==0){
		delay(3000);
		//Imprimir la matriz C
		printf("\n >> C matrix is...\n\n");
		for (i=0;i<dim_m;i++){
			printf("| ");
			for(j=0;j<dim_p;j++){
				valor=matrixC[i * dim_p + j];
				printf("%f\t",valor);
			}
			printf("|\n");
		}
	}
	printf("\n");

    // Finalize the MPI environment.
    MPI_Finalize(); return 0;
}
void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
