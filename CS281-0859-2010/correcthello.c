#include<stdio.h>
#include<string.h>
#include "mpi.h"
int main(int argc,char *argv[]){
MPI_Init(&argc,&argv);
int my_rank,p, tag=0;
char message[20];
MPI_Status status;

MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

if (my_rank==0)
{
strcpy(message,"HELLO");
MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
printf("Hello world from processor %s, rank %d"
         " out of %d processors\n",
         processor_name, my_rank,p);
}
if(my_rank==1)
MPI_Recv(message,20,MPI_CHAR,0,tag,MPI_COMM_WORLD,&status);
MPI_Finalize();
}
