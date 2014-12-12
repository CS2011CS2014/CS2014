/*

	This program illustrates peer to peer communication using MPI
	The functions used here are MPI_Send and MPI_Recv
	In this case, a processor with rank 0 sends a message to the processor with rank 1.
*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    int rank_no,nodes,tag=0;
    char message[30];
    MPI_Status status;

    //Initializing MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&nodes);

        //If the rank number is 0, create message and send to 1
        if(rank_no==0)
        {
            strcpy(message,"Hey, Hawayu!");
            MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
	    printf("Processor: %d Message sent: '%s' To processor: 1\n",rank_no,message);
        }

        //If rank number is 1, receive message from 0
        else if(rank_no==1)
        {
            MPI_Recv(message,50,MPI_CHAR,0,tag, MPI_COMM_WORLD,&status);
            printf("Processor: %d Received message: '%s' From processor: 0 \n",rank_no,message);
        }

    MPI_Finalize();
    return 0;
}
