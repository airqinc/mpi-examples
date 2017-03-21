// http://www.math-cs.gordon.edu/courses/cps343/presentations/MPI_Collective.pdf

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <unistd.h>

// #include "data_helper.h"

const int SIZE_PER_PROCESS = 1;


void dumpData ( int rank , int numProc , int dataPerProcess ,
  int* v , const char * label , int sync )
  {
    for ( int p = 0; p < numProc ; p ++ ) {
      if ( rank == p ) {
        printf ( " Process %2d : %-8s = " , rank , label );
        for ( int i = 0; i < numProc ; i ++ ) {
          for ( int j = 0; j < dataPerProcess ; j ++ ) {
            int k = i * dataPerProcess + j ;
            printf ( " %04d " , v [ k ] );
          }
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


  int main ( int argc , char * argv [] )
  {
    int numProc , rank ;
    MPI_Init ( & argc , & argv );
    MPI_Comm_size ( MPI_COMM_WORLD , & numProc );
    MPI_Comm_rank ( MPI_COMM_WORLD , & rank );
    // Construct array of data for this process .
    // The values in the array have the form RXYY where
    // " R " is rank of this process ,
    // " X " is the group number (1.. number_of_processes );
    // this is also the destination rank , and
    // " YY " is a counter value that starts at 00 and
    // works up to SIZE_PER_PROCESS -1.
    // int* u = new int [ numProc * SIZE_PER_PROCESS ];

    int *u = (int *)malloc(sizeof(int) * numProc * SIZE_PER_PROCESS);

    // int* v = new int [ numProc * SIZE_PER_PROCESS ];
    int *v = (int *)malloc(sizeof(int) * numProc * SIZE_PER_PROCESS);
    for ( int i = 0; i < numProc ; i ++ ) {
      for ( int j = 0; j < SIZE_PER_PROCESS ; j ++ ) {
        int k = i * SIZE_PER_PROCESS + j ;
        u [ k ] = 1000 * rank + 100 * i + j ;
        v [ k ] = 0;
      }
    }
    // Display constructed data
    dumpData ( rank , numProc , SIZE_PER_PROCESS , u , " Before " , 1);
    // Each process participates in the all - to - all operation
    MPI_Alltoall ( u , SIZE_PER_PROCESS , MPI_INT ,
      v , SIZE_PER_PROCESS , MPI_INT ,
      MPI_COMM_WORLD );
      // Display received data
    dumpData ( rank , numProc , SIZE_PER_PROCESS , v , " After ", 1 );
    // Clean up
    // delete [] u ;
    free(u);
    // delete [] v ;
    free(v);
    MPI_Finalize ();
    return 0;
  }
