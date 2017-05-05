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

	//Creamos la matriz si somos el proceso 0
	float random;
	float valor;
        int i,j;

	float *matrixA = (float*) malloc( dim_m * dim_n * sizeof( float ));
	float *matrixB = (float*) malloc( dim_n * dim_p * sizeof( float ));
	float *matrixC = (float*) malloc( dim_m * dim_p * sizeof( float ));

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

	//Broadcast B
	MPI_Bcast(matrixB,dim_n*dim_p,MPI_FLOAT,0, MPI_COMM_WORLD);

	delay(1000*rank);
	
	//Imprimir la matriz B
	printf("\n[%d] >> B matrix is...\n\n",rank);
	for (i=0;i<dim_n;i++){
		printf("| ");
		for(j=0;j<dim_p;j++){
			valor=matrixB[i * dim_p+ j];
			printf("%f\t",valor);
		}
		printf("|\n");
	}

	//A cada proceso le enviamos una fila de la matriz A
	int bufLen = dim_n;
	float bufRecv [bufLen];

	//Scatter A rows
	MPI_Scatter(matrixA, bufLen, MPI_FLOAT, bufRecv, bufLen, MPI_FLOAT, 0, MPI_COMM_WORLD);

	delay(1000*rank);

	//Imprimir buffer recibido
	printf("\n >> %d received buffer is...\n\n",rank);
	for (i=0;i<bufLen;i++){
		printf("%f ",bufRecv[i]);
	}

	printf("\n");

	int bufLen2 = dim_p;
	float bufSend [bufLen2]; 
	float b;
	float a;
	float sum;

	//calcular fila de la matriz C
	for (i=0;i<dim_p;i++){
		sum=0;
		for(j=0;j<dim_n;j++){
			b=matrixB[j*dim_p + i];
			a=bufRecv[j];
			sum=sum+a*b;
		}
		bufSend[i]=sum;
	}

	printf("\n >> %d sending buffer is...\n\n",rank);
	for (i=0;i<bufLen2;i++){
		printf("%f ",bufSend[i]);
	}
	printf("\n");

	
	MPI_Gather(bufSend, bufLen2, MPI_FLOAT, matrixC, bufLen2, MPI_FLOAT, 0, MPI_COMM_WORLD);

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
