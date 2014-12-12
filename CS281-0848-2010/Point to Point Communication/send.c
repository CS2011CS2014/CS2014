
#include <stdio.h>
#include <mpi.h>
#ifndef SENDSIZE
#define SENDSIZE 1
#endif

int
main (int argc, char * argv[] )
{
	int i, rank, nodes, myData[SENDSIZE], theirData[SENDSIZE];
	MPI_Status xferStatus[2];
	MPI_Request xferRequest[2];

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	myData[0] = rank;
	MPI_Isend(myData, SENDSIZE, MPI_INT, (rank + 1) % nodes, 0,  MPI_COMM_WORLD, &xferRequest[0]);
	MPI_Irecv(theirData, SENDSIZE, MPI_INT, (rank + nodes -1) % nodes, 0, MPI_COMM_WORLD, &xferRequest[1]);

	MPI_Waitall(2,xferRequest,xferStatus);

	printf("%i sent %i; received %i\n", rank, myData[0], theirData[0]);

	MPI_Finalize();
	return 0;
}
