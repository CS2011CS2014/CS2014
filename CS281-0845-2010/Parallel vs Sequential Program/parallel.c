#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

/*
=====================================================================================================================
-   This program performs LU decomposition of a matrix A.

-   Cyclic distribution was used to accomplish LU factorization of the input square matrix, meaning that load was distributed 
    among the processors in a cyclic fashion

-   Each node is responsible for computing its own block and then broadcasts the result to rest of the nodes.

-   The Algorithm was evaluated for input matrix of sizes 100, 500, 10000
    with a combination of 8, 16, 32 compute nodes working in parallel.

-   Output is stored in output.txt
========================================================================================
*/

int size;
double **l;
double **u;
double **mat;
int rank, nprocs;
clock_t begin, end;
FILE *fp;

void printMatrix(double **m) {
    //printf("\n");

	int i =0, j=0;
    for (i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            printf("  %f  ",m[i][j]);
        }
        printf("\n");
    }

}

void freeMatrix(double **matrix)
{
	int i =0;
    for(i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}


void decompose(double **m) {
	begin =clock();
	int i=0, j=0, k=0;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	/* get current process id */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);	/* get number of processes */


	int *map =malloc(size * (sizeof *map));

	for(i=0; i<size; i++)
	{
		map[i]= i % nprocs;
	}

	for(j =0; j < size-1; j++) {
        if(map[j] == rank)
        {
        	for(i = j+1; i < size; i++) {
        		m[i][j] = m[i][j]/m[j][j];
        	}
        }
        MPI_Bcast (&m[j][j],size-j,MPI_DOUBLE,map[j],MPI_COMM_WORLD);

        		for(k = j+1; k < size; k++)
        		{
        			if(map[j] == rank)
        			{
        				for(i = j+1; i < size; i++) {
        					m[k][i]= m[k][i] - (m[k][j] * m[j][i]);
        				}
        			}
        		}
        }
        
        //printMatrix(m);
    end = clock();
    
    MPI_Finalize();
}

int generateMatrix(int size)
{

srand(time(NULL));
    mat = malloc(size * (sizeof *mat));
    u = malloc(size * (sizeof *u));
    l = malloc(size * (sizeof *l));
    //matcpy = malloc(size * (sizeof *matcpy));

    int i =0;
    for(i = 0; i<size;i++)
    {
    	u[i] = malloc((sizeof *u[i]) * size);
    	l[i] = malloc((sizeof *l[i]) * size);
    	mat[i] = malloc((sizeof *mat[i]) * size);
    }
    for( i=0 ; i < size ; i++) {
    	u[i] = malloc((sizeof *u[i]) * size);
    	l[i] = malloc((sizeof *l[i]) * size);
        mat[i] = malloc((sizeof *mat[i]) * size);
        //matcpy[i] = malloc((sizeof *matcpy[i]) * size);

        int j = i;
        for( j=i; j< size; j++) {
            mat[i][j] = i+1;
            mat[j][i] = i+1;
            u[i][j] = mat[i][j];
            u[j][i] = mat[j][i];
        }
    }
    decompose(mat);
    return 1;
}


int main(int argc, char * argv[])
{
    if(argc < 2) {
    	printf("Matrix Size missing in the arguments \n");
    	return -1;
    }
    size = strtol(argv[1],(char **)NULL,10);
    fp = fopen("output.txt","wb");

  	int successFlag = 0;
  	if(generateMatrix(size) == 1)
        {
  		successFlag = 1;
  	}


  	if(successFlag == 1)
  	{
  		fprintf(fp, "Successfully generated %d by %d matrix \n",size,size);
  		//printf("%d by %d matrix generated \n",size,size);
  	}
  	else
  	{
  		fprintf(fp,"Failed to generate matrix \n");
  	}

  	fprintf(fp,"Time taken to decompose : %f seconds ", (double)(end - begin) / CLOCKS_PER_SEC);
  	fclose(fp);
  	return 0; 
}
