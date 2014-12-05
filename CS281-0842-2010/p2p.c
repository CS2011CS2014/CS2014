/* P2P.c */
/*This is a Point to Point communication whereby each process both sends to another process and 
receives from another process. In this case process 0 sends to process 1 and receives from process 4, 
process 1 sends to process 2 and receives from process 0, process 2 sends to process 3 and receives 
from process 1... and so on.
*/

/*Output for 5 processes */
#include <stdio.h>
#include <mpi.h>
#ifndef SENDSIZE
#define SENDSIZE 1
#endif

int main (int argc, char * argv[] )
{
	int i, rank, nodes, myData[SENDSIZE], theirData[SENDSIZE];
	MPI_Status sendStatus;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	myData[0] = rank;
	MPI_Send(myData, SENDSIZE, MPI_INT, (rank + 1) % nodes, 0,  MPI_COMM_WORLD);
	MPI_Recv(theirData, SENDSIZE, MPI_INT, (rank + nodes -1 ) % nodes,
	         0, MPI_COMM_WORLD, &sendStatus);
	
	printf("%i sent %i; received %i\n", rank, myData[0], theirData[0]);

	MPI_Finalize();
	return 0;
}
