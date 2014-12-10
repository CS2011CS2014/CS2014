#ifndef _LCS_FUNCTIONS_MPI_H_
#define _LCS_FUNCTIONS_MPI_H_

#include "lcs_functions.h"
#include <mpi.h>

void parallel_calc_P(char *str2, int str2_len, char *alphabet, int alphabet_len);
void parallel_calc_S(int **P, char *alphabet, char *str1, int str1_len, int str2_len);

void LCS_IO_calc_P(MPI_File f_str2, char *alphabet, MPI_File f_P, int first_row, int last_row);
void LCS_IO_calc_S(MPI_File f_str1, MPI_File f_str2, MPI_File f_P, MPI_File f_S, char *alphabet, int first_column, int last_column);
void LCS_IO_lcs_sequence(MPI_File f_S, MPI_File f_str1, MPI_File f_str2, char **s);

#endif
