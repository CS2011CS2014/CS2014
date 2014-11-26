/**
 * Reg No: CS281-0375/2010
 * Name: Gedion Kyalo Kitili
 * 
 * B cast example using MPI
 */

#include <mpi.h>
#include <stdio.h>
int main (int argc, char *argv[]){
  int rank,size,i,msg=1500;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Bcast(&msg,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
      printf("Root process broadcasting message: %d \n",msg);
    }
    else
    {
      printf("Process %d received broadcast message: %d \n",rank,msg);
    }

  MPI_Finalize();
 return 0;
}// end main
