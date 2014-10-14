/* C Example */
#include <mpi.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
int i,root,my_rank,my_size,number=1000;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&my_size);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
if(my_rank==0)
{
my_rank=root;
MPI_Bcast(&number,1,MPI_INT,0,MPI_COMM_WORLD);
for(i=1;i<my_size;i++)
{
printf("broadcasting %d to processor%d\n",number,i);
}
}
else
{
printf("broadcasting %d receceiving...%d\n",my_rank,my_size);
}
MPI_Finalize();
return 0;
}

