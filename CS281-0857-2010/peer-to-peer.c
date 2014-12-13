/*
CS281-0857/2010
Njogu Ngugi Benson
Ass 1
M.P.I

Peer-to-Peer communication = communication between two processors
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
				    //variables declared
    FILE *fp;
    int rank_no,items,tag=0;
    char message[30];
    MPI_Status status;
		       		//Initializing
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

		        	//processor with rank 0 send the message 'Hello World'
        if(rank_no==0)
        {
            strcpy(message,"Hello World!");
            printf("Processor %d: Sending message '%s' to processor 1..\n",rank_no,message);
	    fp=fopen("p2p.txt","w");
            fprintf(fp,"Processor %d: Sending message '%s' to processor 1..\n",rank_no,message);
            fclose(fp);
            MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
        }

			        //processor with rank 1 receive the message
        else if(rank_no==1)
        {
            MPI_Recv(message,50,MPI_CHAR,0,tag, MPI_COMM_WORLD,&status);
            printf("Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
            fp=fopen("p2p.txt","a");
            fprintf(fp,"Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
            fclose(fp);
        }

    MPI_Finalize();
    }
