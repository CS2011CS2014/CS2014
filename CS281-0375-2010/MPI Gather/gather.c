/**
 * Reg No: CS281-0375/2010
 * Name: Gedion Kyalo Kitili
 * 
 * MPI_Gather example using MPI
 */

#include <stdio.h>
#include <mpi.h>

void main(int argc,char * argv[] )
{
	int rank,size;
	int sendbuf[]={0,1,2,3,4};
	int recvbuf[1];
	int  gatherbuf[5];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Scatter(sendbuf,1,MPI_INT,recvbuf,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		printf("\n Root Process Scattering Data in MyArray: [ %d ,%d ,%d ,%d ,%d ] to be doubled by each 			processor \n\n",sendbuf[0], sendbuf[1] , sendbuf[2] , sendbuf[3] , sendbuf[4] );
	}

	printf("Processer %d has received data: %d and doubled it to give %d \n",rank, recvbuf[0], recvbuf[0]*2 );

	int myresult=recvbuf[0]*2;

	MPI_Gather(&myresult,1,MPI_INT,&gatherbuf,1,MPI_INT,0,MPI_COMM_WORLD );

	if(rank==0)
	{
		printf("\n\n Root process has gathered results. MyArray is now : [ %d ,%d ,%d ,%d ,%d ] \n", 			gatherbuf[0], gatherbuf[1], gatherbuf[2], gatherbuf[3], gatherbuf[4] );
	}

	MPI_Finalize();

}// end main
