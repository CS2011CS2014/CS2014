/*
*The Avengers
**********************************

Athman Gude					CS281-0837/2010
Erick Oude					CS281-0861/2010
Joseph Sharia				CS281-0834/2010
Brian Onyando				CS281-0862/2010
Ronnie Nyaga				CS281-0838/2010
*/


#include <stdio.h>
#include "lcs_functions.h"
#include "lcs_functions.c"

#define BUF_SIZE (1024*1024)

int main(int argc, char **argv) {
    /*if(argc != 4) {
        fprintf(stderr, "Usage: %s str1_file str2_file out_file\n", argv[0]);
        return 1;
    }*/
    char *str1 = (char*)malloc(sizeof(char) * BUF_SIZE);
    char *str2 = (char*)malloc(sizeof(char) * BUF_SIZE);
    int str1_len;
    int str2_len;
    char *c;
    //FILE *f1 = fopen(argv[1], "rb");
    FILE *f1 = fopen("file1.txt", "rb");
    if(!f1) {
        fprintf(stderr, "Unable to open file '%s'\n", argv[1]);
        return 1;
    }
    //FILE *f2 = fopen(argv[2], "rb");
    FILE *f2 = fopen("file2.txt", "rb");
    if(!f2) {
        fprintf(stderr, "Unable to open file '%s'\n", argv[2]);
        return 1;
    }
    //FILE *f3 = fopen(argv[3], "w");
    FILE *f3 = fopen("results.txt", "w");
    if(!f3) {
        fprintf(stderr, "Unable to open file '%s'\n", argv[3]);
        return 1;
    }
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
    int **res_matr = (int**)malloc(sizeof(void*) * (str1_len + 1));
    int i;
    for(i = 0; i <= str1_len; i++)
        res_matr[i] = (int*)malloc(sizeof(int) * (str2_len + 1));
    int lcs_len = lcs_length(res_matr, str1, str1_len, str2, str2_len);
    fprintf(f3, "lcs length = %d\n", lcs_len);
    char *seq = lcs_sequence(res_matr, lcs_len, str1, str1_len, str2, str2_len);
    fprintf(f3, "lcs sequence\n");
    fprintf(f3, seq);
    fprintf(f3, "\n");
    free(seq);
    for(i = 0; i <= str1_len; i++)
        free(res_matr[i]);
    fclose(f3);
    free(res_matr);
    free(str1);
    free(str2);
    return 0;
}
