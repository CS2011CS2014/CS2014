#include <mpi.h>
#include <stdio.h>
int main (int argc, char *argv[]){
        MPI_Init(&argc,&argv);
        int my_rank,size,i,message=2100;
        
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Bcast(&message,1,MPI_INT,0,MPI_COMM_WORLD);

	    if(my_rank==0)
	    {
	    printf("Root process broadcasting message: %d \n",message);
	    }
	    else
	    {
	    printf("Process %d received broadcast message: %d \n",my_rank,message);
	    }

        MPI_Finalize();
	return 0;
	
	}
