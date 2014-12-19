/*
CS281-0853/2010
NAMATITI W BENEDICT
Assignment 2

BROADCASTING AMONG PROCESSES:
This is a simple program to broadcast a message from one processor to all other processors.
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{

    //Declare variables
    FILE *fp;
    int rank_no,items;
    char message[30];

    //Initialize program and variables
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

    //Have processor with rank 0 broadcast the message
    if(rank_no==0){

        strcpy(message,"Hello World!");
        printf("Processor %d: Broadcasting message '%s' to %d other processors...\n\n",rank_no,message,items-1);

        //print to text file
        fp=fopen("broadcast.txt","w");
        fprintf(fp,"Processor %d: Broadcasting message '%s' to %d other processors...\n\n",rank_no,message,items-1);
        fclose(fp);

        MPI_Bcast(&message, 30, MPI_CHAR, rank_no, MPI_COMM_WORLD);
    }


    //Have the other processors receive the broadcasted message
    else{
        MPI_Bcast(&message, 30, MPI_CHAR, 0, MPI_COMM_WORLD);

        printf("Processor %d: Received message '%s' from processor 0 \n",rank_no,message);

        //print results to text file
        fp=fopen("broadcast.txt","a");
        fprintf(fp,"Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
        fclose(fp);
    }

    MPI_Finalize();
    }
