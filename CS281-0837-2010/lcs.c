#include<stdio.h>

#include<string.h>

#define size 20

char A[size],B[size];

int i,j,A_len,B_len;

int score[size][size];

void main(){

    printf("\tEnter first string\n\t");
    scanf("%s",A);
    printf("\tEnter second string\n\t");
    scanf("%s",B);
    printf("\n");

    A_len = strlen(A);

    B_len = strlen(B);

    A[0] = ' ';

    printf("\t ");

    for(i=1;i<=B_len;i++)

    printf("%5c",toupper(B[i]));

    printf("\n\n");

    for(i=0;i<=A_len;i++){

        for(j=0;j<=B_len;j++){
            if(i==0 || j==0)
                score[i][j]=0;
            else if(A[i] == B[j] )
                score[i][j] = score[i-1][j-1] + 1;
            else{
                if(score[i][j-1]>score[i-1][j])
                    score[i][j] = score[i][j-1];
                else
                    score[i][j] = score[i-1][j];
            }
        }

    }

    for(i=0;i<=A_len;i++){
        printf("\t%c",toupper(A[i]));
        for(j=0;j<=B_len;j++)
            printf("%5d",score[i][j]);
        printf("\n\n");
    }

    if(score[A_len][B_len] != 0){
        printf("Longest common subsequence is of %d length :\t",score[A_len][B_len]);
    }else{
        printf("longest common subsequence not found");
    }
}
