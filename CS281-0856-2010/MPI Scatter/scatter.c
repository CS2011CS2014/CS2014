/**
 * 
 * 
 * 
 * MPI_Scatter example using MPI
 */

#include <stdio.h>
#include <mpi.h>

void main(int argc,char * argv[] )
{
	int rank,size;
	int sendbuf[]={0,1,2,3,4};
	int recvbuf[1];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Scatter(sendbuf,1,MPI_INT,recvbuf,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		printf("Root Process Scattering Data in Array: [ %d ,%d ,%d ,%d ,%d ] \n",sendbuf[0], sendbuf[1] , 			sendbuf[2] , sendbuf[3] , sendbuf[4] );
	}

	printf("Processer %d has received data: %d \n",rank, recvbuf[0] );

	MPI_Finalize();

}
