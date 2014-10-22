/*
 * p2p.c
 *
 * CS281-3340/2010
 * MORRIS IRIGA
 *
 * Program that demonstrates the peer-to-peer capabilities
 * of processes utilising the OpenMPI library.
 * One process sends a message to a second and the second confirms that
 * it has indeed recieved the message.
 *
 */


#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	//Variable declaration
	FILE *fp;
	int rank_no, items, tag = 0;
	char message[30];
	MPI_Status status;

	//Program initialization
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_no);
	MPI_Comm_size(MPI_COMM_WORLD, &items);

	// First processor sends a message
	if (rank_no == 0)
	{
		strcpy(message, "Hello World!");
		printf("Processor %d says \" %s \" to processor 1.\n", rank_no, message);

		// Print message to p2p.txt
		fp = fopen("p2p.txt", "w");
		fprintf(fp, "Processor %d says \"%s\" to processor 1.\n", rank_no, message);
		fclose(fp);

		MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);

	}

	// Second processor confirms it has recieved the message
	else if (rank_no == 1)
	{
		MPI_Recv(message, 50, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		printf("Processor %d has received message \" %s \" from processor 0.\n", rank_no, message);

		// Print message receipt confirmation to p2p.txt
		fp = fopen("p2p.txt", "a");
		fprintf(fp, "Processor %d received message \" %s \" from processor 0.\n", rank_no, message);
		fclose(fp);
	}

	MPI_Finalize();
}
