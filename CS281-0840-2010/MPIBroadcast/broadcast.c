/*A program to broadcast 999 by a root process 0 to all other processes.

MPI_Bcast is the function used used by the root process to send the message and by the receiving processes to receive the broadcasted message.*/

#include <mpi.h>
#include <stdio.h>
int main (int argc, char *argv[]){
        int rank,size,i,msg=999;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Bcast(&msg,1,MPI_INT,0,MPI_COMM_WORLD);

	    if(rank==0)
	    {
	    printf("The root process broadcasting message: %d \n",msg);
	    }
	    else
	    {
	    printf("Process %d received broadcast message: %d \n",rank,msg);
	    }

        MPI_Finalize();
	return 0;
	
	}
