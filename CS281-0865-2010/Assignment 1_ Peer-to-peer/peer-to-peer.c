/*
CS281-0865/2010
Wanga Melchsedech
Assignment 1
PEER-TO-PEER COMMUNICATION:
Task: A program in which one process sends a message to another process
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{

    //Variable declaration
    FILE *fp;
    int rank_no,items,tag=0;
    char message[30];
    MPI_Status status;

    //Program initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

        //Has the processor with rank 0 send a message
        if(rank_no==0)
        {
            strcpy(message,"Hello World!");
			printf("PROGRAM OUTPUT:\n");
            printf("Processor %d Sending message '%s' to processor 1.\n",rank_no,message);

            //print to text file output1.txt
            fp=fopen("output1.txt","w");
			fprintf(fp,"PROGRAM OUTPUT:\n");
            fprintf(fp,"Processor %d Sending message '%s' to processor 1.\n",rank_no,message);
            fclose(fp);

            MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);

        }

        //Has processor with rank i received a message
        else if(rank_no==1)
        {
            MPI_Recv(message,50,MPI_CHAR,0,tag, MPI_COMM_WORLD,&status);
            printf("Processor %d Received message '%s' from processor 0.\n",rank_no,message);

            //print results to text file output1.txt
            fp=fopen("output1.txt","a");
            fprintf(fp,"Processor %d Received message '%s' from processor 0.\n",rank_no,message);
            fclose(fp);
        }

    MPI_Finalize();
    }
