#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float *create_rands(int num_elements, int max) {
  float *rands = (float *)malloc(sizeof(float) * num_elements);
  int i;
  for (i = 0; i < num_elements; i++) {
    rands[i] = rand() % max;
  }
  return rands;
}

int main(int argc, char** argv) {
  int num_elements_per_proc = 50;
  int max_random_value = 500;

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Create a random array of elements on all processes.
  srand(7);   // Seed the random number generator to get different results each time for each processor
  float *rands = NULL;
  rands = create_rands(num_elements_per_proc, max_random_value);

  // Sum the numbers locally
  float local_sum = 0;
  int i;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sum += rands[i];
  }

  // Print the random numbers on each process
  printf("Process %d: Local sum = %f, avg = %f\n",
         world_rank, local_sum, local_sum / num_elements_per_proc);

  // Reduce all of the local sums into the global sum
  float global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // Print the result
  if (world_rank == 0) {
    printf("Process 0: Total sum = %f, avg = %f\n", global_sum,
           global_sum / (world_size * num_elements_per_proc));
  }

  // Clean up
  free(rands);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
