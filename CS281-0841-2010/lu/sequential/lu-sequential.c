#include<stdio.h>
#include<stdlib.h>
#include <time.h>

/*
==========================================================================================================
This program performs LU decomposition of a matrix A.
The program starts by calling generateMatrix method which generates a matrix A of order n by n and populates
it using rand function. Malloc is used to reserve space for the matrices A, L and U.
The program then implements a sequential algorithm that performs LU decomposition of the matrix A.
Time taken by the program to execute is given at the end of the program.
Output of the program is in the file output.txt.
==========================================================================================================
*/
float **A, **L, **U;
int i,j,k,n;
clock_t begin, end;

void freeMatrix(float **matrix)
{
	int i =0;
    for(i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void generateMatrix(int size)
{
    srand(time(NULL));
    A = malloc(size * (sizeof *A));
    L = malloc(size * (sizeof *L));
    U = malloc(size * (sizeof *U));
   

    int i, j;
    for(i = 0; i<size;i++)
    {
    	U[i] = malloc((sizeof *U[i]) * size);
    	L[i] = malloc((sizeof *L[i]) * size);
    	A[i] = malloc((sizeof *A[i]) * size);
    }
    for( i=0 ; i < size ; i++) {
    	U[i] = malloc((sizeof *U[i]) * size);
    	L[i] = malloc((sizeof *L[i]) * size);
    	A[i] = malloc((sizeof *A[i]) * size);
        

        for( j=0; j< size; j++) {
            A[i][j] = 1+rand()%20;
            U[i][j] = 0;
            L[i][j] = 0;
        }
    }
    
}

int main()
{
    printf("Enter the order of square matrix: ");
    scanf("%d",&n);

    begin=clock();

    generateMatrix(n);
   
    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i<=j)
            {
                U[i][j]=A[i][j];
                for(k=0; k<i-1; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else
            {
                L[i][j]=A[i][j];
                for(k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
            }
        }
    }
    printf("[L]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",L[i][j]);
        printf("\n");
    }
    printf("\n\n[U]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",U[i][j]);
        printf("\n");
    }
    
	freeMatrix(A);
	freeMatrix(L);
	freeMatrix(U);

    end=clock();
    printf("The time taken is: %f seconds \n", (double)(end - begin) / CLOCKS_PER_SEC);
	return 0;
}


