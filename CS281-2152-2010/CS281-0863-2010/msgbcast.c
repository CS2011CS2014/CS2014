#include <mpi.h>
#include <stdio.h>
#include <string.h>
int main (int argc, char *argv[]){
int process_rank,size;
char message[50];
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

strcpy(message,"BROADCAST MESSAGE");

MPI_Bcast(&message,1,MPI_INT,0,MPI_COMM_WORLD);

    if(process_rank==0)
    {
    printf("Master broadcasting message- %s \n",message);
    }
    else
    {
    printf("Process %d received broadcast message-%s \n",process_rank,message);
    }

      MPI_Finalize();
      return 0;
}
