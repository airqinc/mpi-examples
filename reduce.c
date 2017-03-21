#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "data_helper.h"

int main(int argc, char** argv) {
  const int ELEMENTS_PER_PROC = 3;
  const int MAX_RANDOM_VAL = 10;
  const int SEED = 7;
  srand(SEED);


  MPI_Init(NULL, NULL);

  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Create a random array of elements on all processes.
  float *rands = NULL;
  rands = create_rands(ELEMENTS_PER_PROC, MAX_RANDOM_VAL);

  dumpData ( world_rank , world_size , ELEMENTS_PER_PROC , rands , " Data " , 1);

  // Sum the numbers locally
  float local_sum = 0;
  int i;
  for (i = 0; i < ELEMENTS_PER_PROC; i++) {
    local_sum += rands[i];
  }

  // Print the random numbers on each process
  printf(" Process %d: Local sum = %f, avg = %f\n",
         world_rank, local_sum, local_sum / ELEMENTS_PER_PROC);

  // Reduce all of the local sums into the global sum
  float global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // Print the result
  if (world_rank == 0) {
    printf("Process 0: Total sum = %f, avg = %f\n", global_sum,
           global_sum / (world_size * ELEMENTS_PER_PROC));
  }

  // Clean up
  free(rands);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
