#include <stdio.h>
#include <mpi.h>

<<<<<<< HEAD
int main(int argc, char* argv[]){

    int i, rank, nodes;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(i=0; i < nodes; i++){
        MPI_Barrier(MPI_COMM_WORLD);
        if(i == rank)
            printf("Hello from %i of %i!\n", rank, nodes);
    }

    MPI_Finalize();
    return 0;

    //mpicc -g hello.c -o helloworld
    //mpirun -n 4 ./hello
}
=======

int main(int argc, char* argv[])
{
	int my_rank, my_size;
	MPI_Init (&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &my_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("Hello world, I am processor %d of %d \n", my_rank, my_size);
	MPI_Finalize();
	return 0;
}
>>>>>>> 471849e98d4679004aeaad1f3d49800435173043
