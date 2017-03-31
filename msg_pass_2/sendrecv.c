#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int myid, numprocs, left, right;
    int *buffer = NULL;
    int *buffer2 = NULL;
    MPI_Status status;
 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
 
    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;
    
    buffer = malloc(10*sizeof(int));
    buffer2 = malloc(10*sizeof(int));
    buffer[0] = myid;
    buffer2[0] = -1;

    MPI_Sendrecv(buffer, 1, MPI_INT, left, 123, buffer2, 1, MPI_INT, right, 123, MPI_COMM_WORLD, &status);
    printf("Proc %d - Sent: %d, Received: %d\n", myid, buffer[0], buffer2[0]);
    MPI_Finalize();
    free(buffer);
    free(buffer2);
    return 0;
}
