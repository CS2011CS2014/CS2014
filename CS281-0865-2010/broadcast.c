/*
* Program to show hot to use the MPI_Bcast() method
*
* @author melch
*/

#include <mpi.h>
#include <stdio.h>
int main (int argc, char *argv[]){
        int rank,size,msg=1500;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Bcast(&msg,i,MPI_INT,0,MPI_COMM_WORLD);

	    if(rank==0)
	    {
	    printf("Main process broadcasting message: %d \n",msg);
	    }
	    else
	    {
	    printf("Process %d receiving broadcasted message: %d \n",rank,msg);
	    }

        MPI_Finalize();
	return 0;

	}


