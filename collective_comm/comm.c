#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "data_helper.h"

int main(int argc, char *argv[])  {
  int  world_rank, world_size, new_rank, sendbuf, recvbuf;
  MPI_Group   orig_group, new_group;   // required variables
  MPI_Comm    new_comm;   // required variable

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  sendbuf = world_rank;

  int *ranks1 = NULL;
  ranks1 = create_ranks(world_size, 1);
  int *ranks2 = NULL;
  ranks2 = create_ranks(world_size, 0);

  // extract the original group handle
  MPI_Comm_group(MPI_COMM_WORLD, &orig_group);

  //  divide tasks into two distinct groups based upon world_rank
  if (world_rank < world_size/2) {
    MPI_Group_incl(orig_group, world_size/2, ranks1, &new_group);
  }
  else {
    MPI_Group_incl(orig_group, world_size/2, ranks2, &new_group);
  }

  // create new new communicator and then perform collective communications
  MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
  MPI_Allreduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm);

  // get world_rank in new group
  MPI_Group_rank (new_group, &new_rank);
  printf("world_rank = %d newrank = %d recvbuf = %d\n",world_rank,new_rank,recvbuf);
  MPI_Finalize();

  return 0;
}
