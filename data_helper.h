#include <unistd.h>

void dumpData ( int rank , int numProc , int dataPerProcess ,
  float* v , const char * label , int sync )
  {
    for ( int p = 0; p < numProc ; p ++ ) {
      if ( rank == p ) {
        // It ’s my turn to display data ...
        printf ( " Processor %2d: %s = " , rank , label );
        for ( int j = 0; j < dataPerProcess ; j ++ ) {
          printf ( " %.2f " , v [ j ] );
        }
        printf ( " \n" );
        fflush ( stdout );
      }
      if ( sync ) {
        MPI_Barrier ( MPI_COMM_WORLD );
        usleep ( 10000 ); // pause 0.01 seconds for I / O
      }
    }
  }
