#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    const int PING_PONG_LIMIT = 10;

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Making sure there are at least two nodes
    if(world_size < 2){
        fprintf(stderr, "World size must be at least two for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int partner_rank = (world_rank + 1) % 2;
    int ping_pong_count = 0;

    int tag = 0;

    while(ping_pong_count < PING_PONG_LIMIT){
        if(world_rank == ping_pong_count % 2){
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, tag, MPI_COMM_WORLD);
            printf("%d sent and incremented ping_pong_count %d to %d\n", world_rank, ping_pong_count, partner_rank);
        }else{
            //MPI_Status status;
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d received ping_pong_count %d from %d\n", world_rank, ping_pong_count, partner_rank);
        }
    }
    MPI_Finalize();
}
