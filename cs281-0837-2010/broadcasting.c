#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void broadcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator){
    int my_rank;
    MPI_Comm_rank(communicator, &my_rank);
    int world_size;
    MPI_Comm_size(communicator, &world_size);


    if(my_rank == root){
        /**
         * The root node broadcasts a message to other nodes
         */
        int i;
        for(i = 0; i < world_size; i++){
            if(i != my_rank){
                MPI_Send(data, count, datatype, i, 0, communicator);
            }
        }
    }else{
        /**
         * Nodes receiving the message broadcast by the root node
         */
         MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char* argv){
    MPI_Init(NULL, NULL);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int data;
    if(my_rank == 0){
        int data = 100;
        printf("Node 0 broadcasting data %d\n", data);
        broadcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        broadcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Node %d receiving data %d from root Node\n", my_rank, data);
    }

    MPI_Finalize();
}
