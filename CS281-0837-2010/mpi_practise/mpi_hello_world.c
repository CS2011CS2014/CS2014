#include <stdio.h>
#include <mpi.h>

int main(){

    /**
     * Initialize the MPI environment
     * Get the world size
     * Get the rank of each processor in the MPI world
     * Get processor name (optional)
     * Print the processor name and rank in the MPI world
     */

    // Initializing the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Printing a hello world message
    //printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

    // Finalizing the MPI environment
    MPI_Finalize();
}
