/*
CS281-0853/2010
NAMATITI W BENEDICT
Assignment 1

PEER-TO-PEER COMMUNICATION:
This is a simple program to send a message from one processor to another
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{

    //Declare variables
    FILE *fp;
    int rank_no,items,tag=0;
    char message[30];
    MPI_Status status;

    //Initialize program and variables
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

        //Have processor with rank 0 send the message
        if(rank_no==0)
        {
            strcpy(message,"Hello World!");
            printf("Processor %d: Sending message '%s' to processor 1..\n",rank_no,message);

            //print to text file
            fp=fopen("p2p.txt","w");
            fprintf(fp,"Processor %d: Sending message '%s' to processor 1..\n",rank_no,message);
            fclose(fp);

            MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);

        }

        //Have processor with rank 1 receive the message
        else if(rank_no==1)
        {
            MPI_Recv(message,50,MPI_CHAR,0,tag, MPI_COMM_WORLD,&status);
            printf("Processor %d: Received message '%s' from processor 0 \n",rank_no,message);

            //print results to text file
            fp=fopen("p2p.txt","a");
            fprintf(fp,"Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
            fclose(fp);
        }

    MPI_Finalize();
    }
