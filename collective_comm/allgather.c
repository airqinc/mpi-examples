#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "data_helper.h"

int main(int argc, char** argv) {
  const int ELEMENTS_PER_PROC = 3;
  const int MAX_RANDOM_VAL = 10;
  const int SEED = 7;

  MPI_Init(NULL, NULL);

  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // buffer for root process
  float *rands = NULL;
  if (world_rank == 0) {
    rands = create_rands(ELEMENTS_PER_PROC * world_size, MAX_RANDOM_VAL, world_rank);
  }

  // buffer for each process
  float *buff_rands = (float *)malloc(sizeof(float) * ELEMENTS_PER_PROC);

  // Scatter data from the root process to all processes and print it
  MPI_Scatter(rands, ELEMENTS_PER_PROC, MPI_FLOAT, buff_rands,
              ELEMENTS_PER_PROC, MPI_FLOAT, 0, MPI_COMM_WORLD);
  dumpData ( world_rank , world_size , ELEMENTS_PER_PROC , buff_rands , " Data " , 1);

  // Compute the average of subset
  float sub_avg = calc_avg(buff_rands, ELEMENTS_PER_PROC);

  // Compute the average of each subset and print it
  float *avgs = NULL;
  // if (world_rank == 0) {
  avgs = (float *)malloc(sizeof(float) * world_size);
  // }
  MPI_Allgather(&sub_avg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, MPI_COMM_WORLD);

  float avg = calc_avg(avgs, world_size);
  printf(" Process %d: Avg of all elements is %f\n", world_rank, avg);

  if (world_rank == 0) {
    free(rands);
  }
  free(buff_rands);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
