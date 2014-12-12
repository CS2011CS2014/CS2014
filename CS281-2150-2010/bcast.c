/*
	This program broadcasts a message from the ROOT node to all other nodes.
	Every processor makes a call to the MPI_Bcast function 
	The ROOT creates the message and broadcasts it.
	Apart from the ROOT, every other processor prints a message to show the message received.
*/

#include <stdio.h>
#include <mpi.h>
#include <string.h>
#define ROOT 0

int main(int argc, char *argv[]){
	int rank_no, nodes;
	char message[30];
	
	//Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_no);
	MPI_Comm_size(MPI_COMM_WORLD, &nodes);

	//If rank is 0, create the message and broadcast it
	if(rank_no==ROOT){
		strcpy(message, "This is a broadcast message!");
		MPI_Bcast(&message, 30, MPI_CHAR, ROOT, MPI_COMM_WORLD);
	}
	else{
		MPI_Bcast(&message, 30, MPI_CHAR, ROOT, MPI_COMM_WORLD);
		printf("Processor: %d Received message: '%s' From process: %d\n", rank_no, message, ROOT);
	}
	

	MPI_Finalize();
	return 0;
}




