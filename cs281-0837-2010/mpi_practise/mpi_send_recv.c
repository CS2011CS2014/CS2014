#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]){

    int world_rank, tag = 0, world_size;
    char message[96];
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_rank == 0){
        strcpy(message, "SOS! I'm stuck with a stray thread. Help me");
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);

    }else if(world_rank == 1){
        MPI_Recv(message, 96, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("Process 1 received message >> %s >>from process 0\n", message);
    }

    MPI_Finalize();
    return 0;
}
