#include<stdio.h>
#include<string.h>
#include"mpi.h"

int main(int argc, char *argv[])
{
int process_rank,items,name_len,tag=0;
char message[50];
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD,&process_rank);
MPI_Comm_size(MPI_COMM_WORLD,&items);
// Get the name of the processor
  MPI_Get_processor_name(processor_name, &name_len);
if(process_rank==0)
	{
	strcpy(message,"I was sent from another process");
	MPI_Send(message,strlen(message)+1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
	printf("Message sent from processor %s, rank %d"
         " out of %d processors\n",
         processor_name, process_rank,items);
	}
if(process_rank==1)
	{
	MPI_Recv(message,50,MPI_CHAR,0,tag, MPI_COMM_WORLD,&status); 
	printf("Mesage received by process %d is: %s \n",process_rank,message);; 
	} 
MPI_Finalize();
}
