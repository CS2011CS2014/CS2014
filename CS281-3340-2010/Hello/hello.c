/*
*
*	broadcast.c
*
*	CS281-3340/2010
*	Morris Iriga
*
*	Demonstration of message broadcast using MPI
*
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	int rank, size, i, msg = 1500;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Root process broadcasting message: %d \n", msg);
	}
	else
	{
		printf("Process %d received broadcast message: %d \n", rank, msg);
	}

	MPI_Finalize();

	return 0;

}