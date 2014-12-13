/*
CS281-0857/2010
Njogu Ngugi Benson
Ass 2
M.P.I.

Broadcasting = one message from one processor to other processors

*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    int rank_no,items;
    char message[30];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_no);
    MPI_Comm_size(MPI_COMM_WORLD,&items);

    if(rank_no==0){
        strcpy(message,"Hello World!");
        printf("Processor %d: Broadcasting message '%s' to %d other processors...\n\n",rank_no,message,items-1);
        fp=fopen("broadcast.txt","w");
        fprintf(fp,"Processor %d: Broadcasting message '%s' to %d other processors...\n\n",rank_no,message,items-1);
        fclose(fp);
        MPI_Bcast(&message, 30, MPI_CHAR, rank_no, MPI_COMM_WORLD);
    }
    else{
        MPI_Bcast(&message, 30, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
        fp=fopen("broadcast.txt","a");
        fprintf(fp,"Processor %d: Received message '%s' from processor 0 \n",rank_no,message);
        fclose(fp);
    }
    MPI_Finalize();
    }
