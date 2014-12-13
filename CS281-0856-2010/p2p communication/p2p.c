/**
 * 
 * 
 * 
 * Peer to Peer communication example using MPI
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
	int my_rank,p,tag=0;
	char msg [20];
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if(my_rank==0)
	{
		strcpy(msg,"Howdy, there");
		MPI_Send( msg,strlen(msg)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD );
		printf("Mesage sent by process %d\n",my_rank);
	}


	if(my_rank==1)
	{
		MPI_Recv( msg,20,MPI_CHAR,0,tag,MPI_COMM_WORLD,&status );
		printf("Mesage received by process %d is: %s \n",my_rank,msg);
	}

	return 0;
}
