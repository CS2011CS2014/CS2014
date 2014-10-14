/*
CS281-0865/2010
Wanga Melchsedech
Assignment 2

BROADCASTING AMONG PROCESSORS
Task: A program to broadcast a message from one processor to all other processors.
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{

    //Variable declaration
    FILE *fp;
    int rank_no,items;
    char message[30];

    //Variable and program initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

    //Has processor with rank 0 broadcasted the message?
    if(rank_no==0){

        strcpy(message,"Hello World!");
        printf("I am Processor %d Broadcasting message '%s' to %d other processors.\n",rank_no,message,items-1);

        //print to text file output2.txt
        fp=fopen("output2.txt","w");
		fprintf(fp,"PROGRAM OUTPUT:\n");
        fprintf(fp,"I am Processor %d Broadcasting message '%s' to %d other processors.\n",rank_no,message,items-1);
        fclose(fp);

        MPI_Bcast(&message, 30, MPI_CHAR, rank_no, MPI_COMM_WORLD);
    }


    //Have all other processors received the broadcasted message from processor 0?
    else{
        MPI_Bcast(&message, 30, MPI_CHAR, 0, MPI_COMM_WORLD);

        printf("Processor %d Received message '%s' from processor 0 \n",rank_no,message);

        //print results to text file output2.txt
        fp=fopen("output2.txt","a");
        fprintf(fp,"Processor %d Received message '%s' from processor 0 \n",rank_no,message);
        fclose(fp);
    }

    MPI_Finalize();
    }
