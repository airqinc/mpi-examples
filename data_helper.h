#include <unistd.h>

void dumpData ( int rank , int numProc , int dataPerProcess ,
  float* v , const char * label , int sync )
  {
    for ( int p = 0; p < numProc ; p ++ ) {
      if ( rank == p ) {
        // It ’s my turn to display data ...
        printf ( " Process %d: %s = " , rank , label );
        for ( int j = 0; j < dataPerProcess ; j ++ ) {
          printf ( " %.2f " , v [ j ] );
        }
        printf ( " \n" );
        fflush ( stdout );
      }
      if ( sync ) {
        MPI_Barrier ( MPI_COMM_WORLD );
        // usleep ( 10000 ); // pause 0.01 seconds for I / O (Does not work on pk2?)
      }
    }
  }

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
