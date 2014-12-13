/*
*The Avengers
**********************************

Athman Gude					CS281-0837/2010
Erick Oude					CS281-0861/2010
Joseph Sharia				CS281-0834/2010
Brian Onyando				CS281-0862/2010
Ronnie Nyaga				CS281-0838/2010
John Mwenda             CS281-0842/2010
*/


#include <stdio.h>
#include "lcs_functions_mpi.h"
#include "lcs_functions_mpi.c"
#include "lcs_functions.c"

#define BUF_SIZE (1024*1024)
#undef DEBUG_TIME

int main(int argc, char **argv) {
   /* if(argc != 4) {
        fprintf(stderr, "Usage: %s str1_file str2_file out_file\n", argv[0]);
        return 1;
    }*/
    double start_t, end_t;
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size == 1) {
        fprintf(stderr, "At least 2 processes expected\n");
        return 1;
    }
    char *str1 = (char*)malloc(sizeof(char) * BUF_SIZE);
    char *str2 = (char*)malloc(sizeof(char) * BUF_SIZE);
    int str1_len;
    int str2_len;
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alp_len = strlen(alphabet);
    FILE *f3;
    if(rank == 0) {
        start_t = MPI_Wtime();
        char *c;
        FILE *f1 = fopen("file1.txt", "rb");
        FILE *f2 = fopen("file2.txt", "rb");
        f3 = fopen("results.txt", "wb");
        fgets(str1, BUF_SIZE, f1);
        fgets(str2, BUF_SIZE, f2);
        c = strchr(str1, '\n');
        if(c) *c = '\0';
        c = strchr(str2, '\n');
        if(c) *c = '\0';
        str1_len = strlen(str1);
        str2_len = strlen(str2);
        fclose(f1);
        fclose(f2);
        end_t = MPI_Wtime();
        #ifdef DEBUG_TIME
        printf("rank=%d: %f seconds for [reading from files]\n", rank, end_t-start_t);
        #endif
    }
    if(rank==0) {
        start_t = MPI_Wtime();
    }
    MPI_Bcast(&str1_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&str2_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(str1, str1_len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(str2, str2_len, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank==0) {
        end_t = MPI_Wtime();
        #ifdef DEBUG_TIME
        printf("rank=%d: %f seconds for [MPI_Bcast of data]\n", rank, end_t-start_t);
        #endif
    }
    if(rank==0) {
        start_t = MPI_Wtime();
    }
    size -= 1;
    int **P = (int**)malloc(sizeof(void*) * alp_len);
    int i;
    for(i = 0; i < alp_len; i++)
        P[i] = (int*)malloc(sizeof(int) * (str2_len + 1));
    if(rank > 0) {
        parallel_calc_P(str2, str2_len, alphabet, alp_len);
    } else { //rank=0
        for(i = 0; i < alp_len; i++) {
            MPI_Recv(P[i], str2_len+1, MPI_INT, (i % size) + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    for(i = 0; i < alp_len; i++) {
        MPI_Bcast(P[i], str2_len+1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    if(rank==0) {
        end_t = MPI_Wtime();
        #ifdef DEBUG_TIME
        printf("rank=%d: %f seconds for [calculation of P]\n", rank, end_t-start_t);
        #endif
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) {
        int **S = (int**)malloc(sizeof(void*) * (str1_len + 1));
        int *rcvcounts = (int*)malloc(sizeof(int) * size + 1);
        int *displs = (int*)malloc(sizeof(int) * size + 1);
        int chunk_size = (str2_len + 1) / size;
        int start_column;
        int end_column;
        rcvcounts[0] = 0;
        displs[0] = 0;
        for(i = 1; i <= size; i++) {
            start_column = (i - 1) * chunk_size;
            end_column = i * chunk_size - 1;
            if(i == size)
                end_column = str2_len;
            rcvcounts[i] = end_column - start_column + 1;
            displs[i] = start_column;
        }
        for(i = 0; i <= str1_len; i++) {
            S[i] = (int*)malloc(sizeof(int) * (str2_len + 1));
        }
        start_t = MPI_Wtime();
        for(i = 0; i <= str1_len; i++) {
            MPI_Gatherv(NULL, 0, MPI_INT, S[i], rcvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
            if(i != str1_len) // this is not last row
                MPI_Bcast(S[i], str2_len + 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
        end_t = MPI_Wtime();
        #ifdef DEBUG_TIME
        printf("rank=%d: %f seconds for [calculation of S]\n", rank, end_t-start_t);
        #endif
        fprintf(f3, "lcs length = %d\n", S[str1_len][str2_len]);
        fprintf(f3, "lcs sequence\n");
        fprintf(f3, "%s\n", lcs_sequence(S, S[str1_len][str2_len], str1, str1_len, str2, str2_len));
        for(i = 0; i <= str1_len; i++) {
            free(S[i]);
        }
        free(S);
        free(rcvcounts);
        free(displs);
        fclose(f3);
    } else { //rank>0
        parallel_calc_S(P, alphabet, str1, str1_len, str2_len);
    }
    for(i = 0; i < alp_len; i++)
        free(P[i]);
    free(P);
    free(str1);
    free(str2);
    MPI_Finalize();
    return 0;
}
