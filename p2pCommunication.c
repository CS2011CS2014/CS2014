/*An MPI program in which the process with rank 0 uses
MPI_Send() to send a message to the process with rank 1
The receiving process i.e. process with rank 1 uses 
MPI_Recv to receive a message */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
	//initializing the variables
	int rank, processes, tag=0;
	char message[20];
	MPI_Status status;

	//initializing the MPI runtime system
	MPI_Init(&argc, &argv);
	//returning the rank of the calling process in the communicator MPI_COMM_WORLD
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	//returning the total no of processes in the communicator in variable processes
	MPI_Comm_size(MPI_COMM_WORLD,&processes);
	// sending the message
	if (rank == 0) {
		//This is the message to be sent
		strcpy (message, "Hello World");
		MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
		
	}

	// Receiving the message
	if (rank == 1){
		MPI_Recv(message, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		printf("%s from processor %i of %i!\n",message, rank, processes);
		MPI_Finalize();
	}




}