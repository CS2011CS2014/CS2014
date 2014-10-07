#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc,char* argv[]){
    int my_rank, tag = 0;
    char message [48];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(my_rank == 0){
        strcpy(message, "Hello! This is a P2P message :-)");
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD );
        printf("Mesage has been sent by Node %d\n", my_rank);
    }

    if(my_rank == 1){
        MPI_Recv(message, 48, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status );
        printf("Mesage has been received by Node %d is: %s \n", my_rank, message);
    }

    MPI_Finalize();

    return 0;
}
