/*
*The Avengers
**********************************

Athman Gude					CS281-0837/2010
Erick Oude					CS281-0861/2010
Joseph Sharia				CS281-0834/2010
Brian Onyando				CS281-0862/2010
Ronnie Nyaga				CS281-0838/2010
*/

#include "lcs_functions.h"

int lcs_length(int **S, char *str1, int len1, char *str2, int len2) {
    int i, k;
    for(i = 0; i <= len1; i++) {
        for(k = 0; k <= len2; k++) {
            if(i == 0 || k == 0)
                S[i][k] = 0;
            else if (str1[i-1] == str2[k-1])
                S[i][k] = 1 + S[i-1][k-1];
            else
                S[i][k] = max(S[i-1][k], S[i][k-1]);
        }
    }
    return S[len1][len2];
}

char* lcs_sequence(int **S, int len, char *str1, int str1_len, char *str2, int str2_len) {
    char *sequence = (char*)malloc(sizeof(char) * len + 1);
    int seq_index = len;
    sequence[seq_index] = '\0';
    int i, k;
    i = str1_len;
    k = str2_len ;
    while(S[i][k] > 0) {
        if(str1[i-1] == str2[k-1]) {
            sequence[--seq_index] = str1[i-1];
            i--; k--;
        } else if(S[i-1][k] >= S[i][k-1])
            i--;
        else
            k--;
    }
    return sequence;
}

inline void calc_Pij(int *P, int i, int j, char *str2, char *alphabet) {
    if(j == 0) {
        P[j] = 0;
    } else if(str2[j-1] == alphabet[i]) {
        P[j] = j;
    } else {
        P[j] = P[j-1];
    }
}

inline void calc_Sij(int **S, int i, int j, char *str1, int **P, char *alphabet) {
    if(i == 0 || j == 0) {
        S[i][j] = 0;
    } else {
        int c = strchr(alphabet, str1[i-1]) - alphabet;
        if(P[c][j] == 0) {
            S[i][j] = max(S[i-1][j], 0);
        } else {
            S[i][j] = max(S[i-1][j], S[i-1][P[c][j] - 1] + 1);
        }
    }
}
