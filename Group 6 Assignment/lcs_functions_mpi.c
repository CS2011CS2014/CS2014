/*
*The Avengers
**********************************

Athman Gude					CS281-0837/2010
Erick Oude					CS281-0861/2010
Joseph Sharia				CS281-0834/2010
Brian Onyando				CS281-0862/2010
Ronnie Nyaga				CS281-0838/2010
*/


#include "lcs_functions_mpi.h"

void parallel_calc_P(char *str2, int str2_len, char *alphabet, int alphabet_len) {
    int i,j;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    size -= 1; // rank=0 does not work here
    int *P = (int*)malloc(sizeof(void*) * (str2_len + 1));
    for(i = 0; i < alphabet_len; i++) {
        if(((i % size) + 1) == rank) {
            P[0] = 0;
            for(j = 1; j <= str2_len; j++) {
                if(str2[j-1] == alphabet[i]) {
                    P[j] = j;
                } else {
                    P[j] = P[j-1];
                }
            }
            MPI_Send(P, str2_len+1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    free(P);
}

void parallel_calc_S(int **P, char *alphabet, char *str1, int str1_len, int str2_len) {
    int i, j, rank, size, chunk_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    size -= 1; // rank=0 does not work here
    chunk_size = (str2_len + 1) / size;
    int *S_prev = (int*)malloc(sizeof(int) * (str2_len + 1)); // previous row
    int start_column = (rank - 1) * chunk_size;
    int end_column = rank * chunk_size - 1;
    if(rank == size)
        end_column = str2_len;
    int *S_current = (int*)malloc(sizeof(int) * (end_column - start_column + 1));
    for(i = 0; i <= str1_len; i++) {
        if(i > 0) {
            // get previous row
            MPI_Bcast(S_prev, str2_len+1, MPI_INT, 0, MPI_COMM_WORLD);
        }
        // if we have 101 columns (100 cells for str2 + 1 cell for '0'),
        // and 3 processes work here (not including rank=0)
        // then rank=1 processes columns from 0 to 32 (including 32)
        // rank=2 processes columns from 33 to 66(including)
        // rank=3 processes columns from 67 to 101(including)
        for(j = start_column; j <= end_column; j++) {
            if(i == 0 || j == 0) { // first row (actually '0' row) and first column (actually '0' column)
                                   // are filled with zeros
                S_current[j - start_column] = 0;
            } else {
                int c = strchr(alphabet, str1[i-1]) - alphabet;
                if(P[c][j] == 0) {
                    S_current[j - start_column] = max(S_prev[j], 0);
                } else {
                    S_current[j - start_column] = max(S_prev[j], S_prev[P[c][j] - 1] + 1);
                }
            }
        }
        MPI_Gatherv(S_current, end_column - start_column + 1, MPI_INT, NULL, NULL, NULL, MPI_INT, 0, MPI_COMM_WORLD);
    }
    free(S_current);
    free(S_prev);
}

void LCS_IO_calc_P(MPI_File f_str2, char *alphabet, MPI_File f_P, int first_row, int last_row) {
    MPI_Offset str2_len;
    MPI_File_get_size(f_str2, &str2_len);
    int *P = (int*)malloc(sizeof(int) * (str2_len + 1));
    char *str2 = (char*)malloc(sizeof(char) * (str2_len + 1));
    MPI_File_read_all(f_str2, str2, str2_len, MPI_CHAR, MPI_STATUS_IGNORE);
    str2[str2_len] = '\0';
    MPI_Datatype one_row;
    MPI_Type_contiguous(str2_len + 1, MPI_INT, &one_row);
    MPI_Type_commit(&one_row);
    int i, k;
    MPI_File_set_view(f_P, sizeof(int) * first_row * (str2_len + 1), MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    for(i = first_row; i <= last_row; i++) {
        for(k = 0; k <= str2_len; k++) {
            calc_Pij(P, i, k, str2, alphabet);
        }
        MPI_File_write(f_P, P, 1, one_row, MPI_STATUS_IGNORE);
    }
    free(P);
    free(str2);
    MPI_Type_free(&one_row);
}

void LCS_IO_calc_S(MPI_File f_str1, MPI_File f_str2, MPI_File f_P, MPI_File f_S, char *alphabet, int first_column, int last_column) {
    MPI_Offset str1_len, str2_len;
    MPI_File_get_size(f_str1, &str1_len);
    MPI_File_get_size(f_str2, &str2_len);
    char *str1 = (char*)malloc(sizeof(char) * (str1_len + 1));
    MPI_File_read_all(f_str1, str1, str1_len, MPI_CHAR, MPI_STATUS_IGNORE);
    str1[str1_len] = '\0';
    int *S_prev = (int*)malloc(sizeof(int) * (str2_len + 1));
    int *S_current = (int*)malloc(sizeof(int) * (last_column - first_column + 1));
    int Pck;
    int i, k;
    for(i = 0; i <= str1_len; i++) {
        if(i > 0) { // read previous row
            MPI_File_read_at_all(f_S, sizeof(int) * (i - 1) * (str2_len + 1), S_prev, str2_len + 1, MPI_INT, MPI_STATUS_IGNORE);
        }
        for(k = first_column; k <= last_column; k++) {
            if(i == 0 || k == 0) {
                S_current[k - first_column] = 0;
            } else {
                int c = strchr(alphabet, str1[i-1]) - alphabet;
                MPI_File_read_at(f_P, sizeof(int) * (c * (str2_len + 1) + k), &Pck, 1, MPI_INT, MPI_STATUS_IGNORE);
                if(Pck == 0) {
                    S_current[k - first_column] = max(S_prev[k], 0);
                } else {
                    S_current[k - first_column] = max(S_prev[k], S_prev[Pck - 1] + 1);
                }
            }
        }
        MPI_File_write_at_all(f_S, sizeof(int) * ((str2_len + 1) * i + first_column), S_current, last_column - first_column + 1, MPI_INT, MPI_STATUS_IGNORE);
    }
    free(S_prev);
    free(S_current);
    free(str1);
}

void LCS_IO_lcs_sequence(MPI_File f_S, MPI_File f_str1, MPI_File f_str2, char **s) {
    MPI_Offset str1_len, str2_len;
    MPI_File_get_size(f_str1, &str1_len);
    MPI_File_get_size(f_str2, &str2_len);
    char *str1 = (char*)malloc(sizeof(char) * (str1_len + 1));
    str1[str1_len] = '\0';
    char *str2 = (char*)malloc(sizeof(char) * (str2_len + 1));
    str2[str2_len] = '\0';
    MPI_File_read_at(f_str1, 0, str1, str1_len, MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_File_read_at(f_str2, 0, str2, str2_len, MPI_CHAR, MPI_STATUS_IGNORE);
    int length;
    MPI_File_read_at(f_S, sizeof(int) * ((str1_len + 1) * (str2_len + 1) - 1), &length, 1, MPI_INT, MPI_STATUS_IGNORE);
    char *sequence = (char*)malloc(sizeof(char) * length + 1);
    int seq_index = length;
    sequence[seq_index] = '\0';
    int i, k;
    i = str1_len;
    k = str2_len;
    int Lik, Li1k, Lik1;
    while(1) {
        MPI_File_read_at(f_S, sizeof(int) * (i * (str2_len + 1) + k), &Lik, 1, MPI_INT, MPI_STATUS_IGNORE);
        if(Lik > 0) {
            if(str1[i-1] == str2[k-1]) {
                sequence[--seq_index] = str1[i-1];
                i--; k--;
            } else {
                MPI_File_read_at(f_S, sizeof(int) * ((i - 1) * (str2_len + 1) + k), &Li1k, 1, MPI_INT, MPI_STATUS_IGNORE);
                MPI_File_read_at(f_S, sizeof(int) * (i * (str2_len + 1) + k - 1), &Lik1, 1, MPI_INT, MPI_STATUS_IGNORE);
                if(Li1k >= Lik1) {
                    i--;
                } else {
                    k--;
                }
            }
        } else {
            break;
        }
    }
    free(str1);
    free(str2);
    *s = sequence;
}
