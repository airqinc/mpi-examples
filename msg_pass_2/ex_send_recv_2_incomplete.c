#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {
	int rank, value = 0, size; MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	/** COMPLETA AQUÍ TU CÓDIGO
	Recuerda que cada proceso ha de recibir el mensaje 
	de su antecesor y enviarlo a su sucesor **/
	
	MPI_Finalize(); return 0;
}