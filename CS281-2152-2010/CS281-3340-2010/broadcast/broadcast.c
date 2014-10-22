/*
* p2p.c
*
* CS281-3340/2010
* MORRIS IRIGA
*
* Program that demonstrates the broadcast capabilities
* of processes utilising the OpenMPI library.
* One process broadcasts a message and oher processes 
* confirm they have seen the message.
*
*/


#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	FILE *fp;
	int rank_no, items;
	char message[30];

	// Initialization
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_no);
	MPI_Comm_size(MPI_COMM_WORLD, &items);

	// Processor with rank 0 broadcasts the message
	if (rank_no == 0){

		strcpy(message, "Hello World!");
		printf("Processor %d: broadcasting message \" %s \" to %d other processors.\n\n", rank_no, message, items - 1);

		// Print broadcast message to broadcast.txt
		fp = fopen("broadcast.txt", "w");
		fprintf(fp, "Processor %d: broadcasting message \" %s \" to %d other processors.\n\n", rank_no, message, items - 1);
		fclose(fp);

		MPI_Bcast(&message, 30, MPI_CHAR, rank_no, MPI_COMM_WORLD);
	}


	// Other processors they have seen the broadcasted message
	else{
		MPI_Bcast(&message, 30, MPI_CHAR, 0, MPI_COMM_WORLD);

		printf("Processor %d: received message \" %s \" from processor 0.\n", rank_no, message);

		//print results to text file
		fp = fopen("broadcast.txt", "a");
		fprintf(fp, "Processor %d: received message \" %s \" from processor 0.\n", rank_no, message);
		fclose(fp);
	}

	MPI_Finalize();
}
