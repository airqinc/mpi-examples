#include <unistd.h>

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

  float *create_rands(int num_elements, int max) {
    float *rands = (float *)malloc(sizeof(float) * num_elements);
    for (int i = 0; i < num_elements; i++) {
      rands[i] = rand() % max;
    }
    return rands;
  }

  float calc_avg(float *data, int num_elements) {
    float sum = 0;
    for (int i = 0; i < num_elements; i++) {
      sum += data[i];
    }
    return sum / num_elements;
  }
