// mpicc scatter_gather.c -o scatter_gather && mpiexec scatter_gather
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

float calc_avg(float *data, int num_elements) {
  float sum = 0;
  int i;
  for (i = 0; i < num_elements; i++) {
    sum += data[i];
  }
  return sum / num_elements;
}

int main(int argc, char** argv) {
  int num_elements_per_proc = 50;
  int max_random_value = 500;
  srand(7);

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // buffer for root process
  float *rands = NULL;
  if (world_rank == 0) {
    rands = create_rands(num_elements_per_proc * world_size, max_random_value);
  }

  // buffer for each process
  float *buff_rands = (float *)malloc(sizeof(float) * num_elements_per_proc);

  // Scatter data from the root process to all processes
  MPI_Scatter(rands, num_elements_per_proc, MPI_FLOAT, buff_rands,
              num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // Compute the average of subset
  float sub_avg = calc_avg(buff_rands, num_elements_per_proc);

  // Gather all partial averages down to the root process
  float *sub_avgs = NULL;
  if (world_rank == 0) {
    sub_avgs = (float *)malloc(sizeof(float) * world_size);
  }
  MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // compute total average from partial averages
  if (world_rank == 0) {
    float avg = calc_avg(sub_avgs, world_size);
    printf("Processor %d: Avg of all elements is %f\n", world_rank, avg);
    // Compute the average across the original data for comparison
    float original_data_avg =
      calc_avg(rands, num_elements_per_proc * world_size);
    printf("Processor %d: Avg of original data is %f\n", world_rank, original_data_avg);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
