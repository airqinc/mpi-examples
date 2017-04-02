#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int world_rank, world_size;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&world_size);
  MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
  if(world_rank == 0) {
    printf("root process: wait for me...\n");
    sleep(1);
    printf("Hello, world.  I am %d of %d\n", world_rank, world_size);fflush(stdout);
    usleep(1000); //time for IO
  } else {
    printf("Hello, world.  I am %d of %d\n", world_rank, world_size);fflush(stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  printf("Bye, world.  I was %d of %d\n", world_rank, world_size);fflush(stdout);
  MPI_Finalize();
  return 0;
}
