#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "../collective_comm/data_helper.h"

int main(int argc, char** argv) {
  const int ELEMENTS_PER_PROC = 3;
  const int MAX_RANDOM_VAL = 10;
  const int ROWS_MULTIPLIER = 2;                                              /* Filas por cada proceso */
  const int COLUMNS = 5;

  MPI_Init(NULL, NULL);

  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rows = world_size * ROWS_MULTIPLIER;
  int data_per_process = COLUMNS * ROWS_MULTIPLIER;                           /* Datos que recibe cada proceso */
  float *a = NULL;
  float *b = NULL;
  float *c = NULL;

  float* ap = (float *) malloc(/* COMPLETAR */);              /* Buffers para cada proceso */
  float* bp = (float *) malloc(/* COMPLETAR */);
  float* cp = (float *) malloc(/* COMPLETAR */);

  if (world_rank == 0) {
    a = create_rands_matrix(rows, COLUMNS, MAX_RANDOM_VAL, world_rank);
    dumpMatrix(a, rows, COLUMNS, "a");
    b = create_rands_matrix(rows, COLUMNS, MAX_RANDOM_VAL, world_rank + 1000);
    dumpMatrix(b, rows, COLUMNS, "b");
    c = (float *)malloc(/* COMPLETAR */);

    /* COMPLETAR (1 línea). Usa MPI */
    /* COMPLETAR (1 línea). Usa MPI */

    for(int i = 0; i < /* COMPLETAR */; i++){
      /* COMPLETAR (1 línea) */
    }

    /* COMPLETAR (1 línea). Usa MPI */

    dumpMatrix(c, rows, COLUMNS, "c = a + b");
  }
  else{
    /* COMPLETAR (1 línea). Usa MPI */
    /* COMPLETAR (1 línea). Usa MPI */

    for(int i = 0; i < /* COMPLETAR */; i++){
      /* COMPLETAR (1 línea) */
    }
    /* COMPLETAR (1 línea). Usa MPI */

  }

  if (world_rank == 0) {
    free(a);
    free(b);
    free(c);
  }
  free(ap);
  free(bp);
  free(cp);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
