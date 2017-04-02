#include <unistd.h>

/* prints process data */
void dumpData (int world_rank, int world_size, int dataPerProcess, float* v, const char * label, int sync) {
  for (int p = 0; p < world_size; p++) {
    if (world_rank == p) {
      printf (" Process %d: %s = " , world_rank , label);
      for (int j = 0; j < dataPerProcess; j++) {
        printf (" %.2f " , v[j]);
      }
      printf (" \n");
    }
    if (sync) {
      MPI_Barrier (MPI_COMM_WORLD);
      // usleep ( 1000 ); // pause 0.1 seconds for I / O (Does not work on pk2?)
    }
  }
}

/* prints a matrix of rows x columns with a label */
void dumpMatrix(float* matrix, int rows, int columns, const char * label){
  printf("matriz %s\n", label);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("\t%f ", matrix[i * columns + j]);
      if(j == columns - 1){
        printf("\n");
      }
    }
  }
}

/* creates an array of random num_elements between 0 and max with a given seed */
float *create_rands(int num_elements, int max, int seed) {
  srand(seed);
  float *rands = (float *)malloc(sizeof(float) * num_elements);
  for (int i = 0; i < num_elements; i++) {
    rands[i] = rand() % max;
  }
  return rands;
}

/* creates a matrix (rows x columns) of random numbers between 0 and max with a given seed */
float *create_rands_matrix(int rows, int columns, int max, int seed) {
  srand(seed);
  float *rands = (float *)malloc(sizeof(float) * rows * columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      rands[i * columns + j] = rand() % max;
    }
  }
  return rands;
}

/* calculates average for an array of num_elements */
float calc_avg(float *data, int num_elements) {
  float sum = 0;
  for (int i = 0; i < num_elements; i++) {
    sum += data[i];
  }
  return sum / num_elements;
}

int *create_ranks(int world_size, int first) {
  int *ranks = (int *)malloc(sizeof(int) * world_size);
  int j;
  if(first){
    j = 0;
  }
  else{
    j = world_size/2;
  }
  for (int i = 0; i < world_size/ 2; i++) {
    ranks[i] = j;
    j++;
  }
  return ranks;
}
