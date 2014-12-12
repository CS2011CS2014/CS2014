
/*
NAME: DENNIS MWANGI BARU
REG.NO:CS281-0835/2010
UNIT: PARALLEL SYSTEMS
UNIT CODE: ICS 2410
ASSIGNMENT:
// An example of a function that implements MPI_Bcast using MPI_Send and MPI_Recv
*/

#include <mpi.h> 		//contains the MPI function types declarations
#include <stdio.h>		//standard buffer input/output
#include <stdlib.h>		//standard library definitions

//sends a message from the root process to all processes in the group
void Bcast(void* data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator) {

  int world_rank;
  int world_size;

//determines the rank of the calling process in the communicator  
  MPI_Comm_rank(communicator, &world_rank);

//Determines the size of the group assocaited with the communicator 
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) 
  {
    // If we are the root process, send our data to everyone
    int i;
    for (i = 0; i < world_size; i++) 
	{
      if (i != world_rank) 
	{
        MPI_Send(data, count, datatype, i, 0, communicator);
  	}
    	}
  } 
// If we are a receiver process, receive the data from the root
 else 
{
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
// Initialize the MPI system
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int data;
  if (world_rank == 0) {
    data = 1963;;
    printf("Process 0 broadcasting number %d\n", data);
   Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
   Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received number %d from root process\n", world_rank, data);
  }

  MPI_Finalize();//Terminates the MPI enviroment
}
