/*
*******************************************************************************************
Title: Sequential Vs Parrallel Matrix Multiplication

Group Members:
Name: Gedion Kyalo Kitili
Reg Number: CS281-0375/2010

Name: Morris Iriga
Reg Number: CS281-08--/2010

This file contains both code for parrallel matrix multiplication and for sequeantial
matrix multiplicatio.

********************************************************************************************

MPI parallel matrix multiplication using asynchronous message passing.
Each process will be assigned a number of rows.

**** rank 0 process responsible for first interval of
**** the matrix as well as the remainder.

The message passing calls used include synchronous as well asynchronous
send and receive, plus broadcast.

For simplicity, square matrices will be assumed and static, global arrays
used.
*/

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


// macro prints array AA, size rzXcz, using formated string fs.
// use as in PRINT2M(A,4,5,"%f ")
#define PRINT2M(AA,rz,cz,fs) { \
 int i, j; \
 for (i=0;i<rz;i++) \
   { for (j=0;j<cz;j++) printf(fs,AA[i][j]); \
     printf("\n"); } \
}


// size of NxN matrix:
#define N 2500

// global static structures
double A[N][N];
double B[N][N];
double AB[N][N];   /* to hold result of A*B */

// conventional one-processor solution
void cmul()
{
  int i, j, k;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      for(k=0,AB[i][j]=0; k<N; k++)
	AB[i][j] += A[i][k] * B[k][j];
} // cmul

void compinterval(int,int);  // prototype

int main(int argc, char** argv)
{
  int rank, size, interval, remainder, i, j;
  double time1, time2, time3;  // for timing measurements
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  MPI_Request ireq[128]; // , asynch request, assume size<128
  MPI_Status stat;       // status of asynch communication

  // compute interval size each process is responsible for,
  // rank 0 process will be responsible for the remainder
  interval = N/(size);
  remainder = N % (size);

  if (rank==0)  // root/coordinator process
    {
      if (argc>1) srandom(atoi(*(argv+1)));  // random seed
      // generate random matrices
      for(i=0;i<N;i++) for(j=0;j<N;j++) 
	{ A[i][j] = random() % 4;
	  B[i][j] = random() % 4;
	} // for

      time1 = MPI_Wtime();     // record time
      // For array B, we broadcast the whole array, however, the Bcast
      // operation is strange because it needs to be executed by all
      // processes.  There is no corresponding Recv for a Bcast
      MPI_Bcast(B,N*N,MPI_DOUBLE,0,MPI_COMM_WORLD); // send broadcast
      //      printf("%d: Bcast complete\n",rank);

      // Send intervals of array A to worker processes
      for(i=1;i<size;i++)
	MPI_Isend(A+(i*interval),interval*N,MPI_DOUBLE,i,i,
		  MPI_COMM_WORLD,ireq+i);
      for(i=1;i<size;i++)
	//MPI_Waitany(size,ireq,&j,&stat); // join on sends

      compinterval(0,interval);                // local work
      compinterval(size*interval, remainder);  // remainder

      //get results from workers:
      for(i=1;i<size;i++)
	MPI_Irecv(AB+(i*interval),interval*N,MPI_DOUBLE,i,i,
		  MPI_COMM_WORLD,ireq+i);
      for(i=1;i<size;i++)
      {
	//MPI_Waitany(size,ireq,&j,&stat);
	//	printf("received results from process %d\n",j);
      }

      time2 = MPI_Wtime();  // record time

      /**
	* Run conventional algorithm:
	*
	* Here we are multiplying the Matrices sequentially and recording the start time and end time 
	* for analysis purposes.
	*
	*
	**/
      cmul();
      time3 = MPI_Wtime();

      printf("approx %d-process time Tp: %f sec.\n",size,time2-time1);
      printf("approx 1-process (conventional) time T1: %f sec.\n",time3-time2);
      printf("efficiency : %f\n",(time3-time2)/((time2-time1)*size));
      /* print : 
      PRINT2M(A,N,N,"%.0f ");  printf("------\n");
      PRINT2M(B,N,N,"%.0f ");  printf("------\n");
      PRINT2M(AB,N,N,"%.0f ");
      */
    }
  else          // worker process
    {
      MPI_Bcast(B,N*N,MPI_DOUBLE,0,MPI_COMM_WORLD); // receive broadcast
      // synchronous receive
      MPI_Recv(A+(rank*interval),interval*N,MPI_DOUBLE,0,rank,
	       MPI_COMM_WORLD,&stat);
      compinterval(rank*interval, interval);
      // send results back to root process, synchronous send
      MPI_Send(AB+(rank*interval),interval*N,MPI_DOUBLE,0,rank,
		MPI_COMM_WORLD);
    }
  MPI_Finalize();
} //main

// multiply fragment of matrix
void compinterval(int start, int interval)
{
  int i, j, k;
  for (i=start;i<start+interval;i++)
    for(j=0;j<N;j++)
      {
	AB[i][j]=0;
	for(k=0;k<N;k++) AB[i][j] += A[i][k] * B[k][j];
      }
}


/**************** Performance Analysis ****************

As every computer science student should easily see, the number of
operations of the conventional matrix-multiplication algorithm is N^3
(N cubed).  With P parallel processors, the number of operations is
ideally N^3/P.  However, we should also take into account the cost of
communication.  A critical ratio is TCOMM/TCALC : the time to
communicate a datum versus the time to perform a calculation. On all
but the most powerful supercomputers, where all processors share RAM,
TCOMM will be considerably slower than TCALC.  On  IP-over-Ethernet
cluster, this ratio will be quite terrible :(.  It is difficult however,
to pin down this ratio to a definite value.  For example, on any network, 
sending 1000 bytes in one packet will be much faster than sending
1000 individual packets. The exact overhead of communication will depend
on many factors.  

It is still possible, however, to do some abstract analysis. The amount of
communication required by the program is 3*N^2. That is:
   
     N^2  for broadcasting array B
     N^2  for sending out each interval of rows (P*(N^2/P) = N^2)
     N^2  for receiving the results back from the worker processors.

The number of calculations required by the algorithm is N^3.  the
ratio is thus TCOMM*3*N^2 /  TCALC*N^3.  However, if we take the limit
of this formula as N approaches infinity, we get ZERO. What this means is
that the overhead of communication will become less and less significant as
the size of the matrices increase. 

Analyzing the same problem from another angle, let's assume for the
moment that the ration TCOMM/TCALC is 1. Then, taking into account the
cost of communication, the number of operations (both calculations and
communications) performed by each of the P processors is

  N^3/P + N^2 + 2N^2/P  

The cost of communication is the cost of receiving the broadcast plus the
costs of receiving and sending the rows it's responsible for.  If we compare
this value with the conventional cost of computation in the case of a 
single processor (N^3), we get:

    3N^3 + (P+2)*N^2
    ---------------
         P*N^3

The limit as N approaches infinity is 1/P (apply L'Hopital's rule 3 times).
This should accord perfectly with our intuition.  That is, if the overhead
of communication can be factored out, then as the size of the matrix increases
then using P processors will speed up the problem by P times.  For example, 
if we used 4 processors, then the maximum speedup will be 4x.  This is 
also the limit according to Amdahl's law regarding parallel speedup.

The matrix-multiplication algorithm is therefore a reasonable
candidate for parallel speed-up.  (the example in the book is only for
matrix-vector multiplication).  But now consider a different problem.  Let's
say we want to simply take matrices A and B and add them.  That is, 
AB[i][j] = A[i][j]+B[i][j].  This algorithm is only N^2. If we attempted
to use P processors, then the ratio of communication over computation is

        3*N^2        
       -------    =  3
         N^2         

  What does this mean?  It means you should be locked up if you tried to
parallelize this algorithm, unless you can dig up a system where
TCOMM/TCALC is less than 1/3.  
   


         =========================================

                       AMDAHL'S LAW:

T1 = time for a sequential solution (one processor) for the algorithm.
Tp = time using p processors
q  = value between 0 and 1 indicating portion of program that's parallelizable
(1-q) therefore prepresents the portion that must be execute sequentialy.

   ***  Speedup = T1/Tp = 1/((1-q)+q/p) <= 1/(1-q)  ***


In the worst case, no part of the program is parallelizable, which
means q=0 and Speedup = 1, or no speedup at all.

In the best case, q = 1, the entire program is parallelizable, which 
means Speedup = p, the number of processors.


Corollary (very important principle in computer science):

   ***  There cannot be super-linear speedup.  ***

Superlinear speed up means, for example, that with 4 processors somehow
we can achieve 10x speedup for the same algorithm.  This is impossible since
according to Amdahl's law, Speedup will be <= 4.  Super-linear speedup
is claimed to be possible with "quantum computing" however.  But quantum 
computing is right now a purely mathematical game.

******************************************************/

