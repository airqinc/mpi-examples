#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int rank, data[100];
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0){
		printf("Process %d: Sending message to process 1\n", rank);
		MPI_Send(data, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if (rank == 1){
		MPI_Recv(data, 100, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printf("Process %d: Recieving message from process %d\n", rank, status.MPI_SOURCE);
	}
	
	MPI_Finalize(); return 0;
}