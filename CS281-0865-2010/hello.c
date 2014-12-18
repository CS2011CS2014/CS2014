/* hello.c */
#include <stdio.h>
#include <mpi.h>

int main (int argc, char * argv[])
{
	int index=0, rank, nodes;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	whilw(index< nodes)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		if (index == rank) printf("Hello from %d of %d!\n", rank, nodes);
		index++;
	}
	MPI_Finalize();
	return 0;
}
