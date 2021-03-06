/* hello.c */
#include <stdio.h>
#include <mpi.h>

int main (int argc, char * argv[])
{
	int i, rank, nodes;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (i=0; i < nodes; i++)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		if (i == rank) printf("Hello from %i of %i!\n", rank, nodes);
	}
	MPI_Finalize();
	return 0;
}
