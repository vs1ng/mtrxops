#include <stdio.h>

int main(){
    int A[3][3] = {
                    {1,2,3},
                    {4,5,6},
                    {7,8,9}
    };

    int R = 3;
    int C = 3;
    int* S = &A[0][0];

    int* D[3] = {&A[0][0],&R,&C};

    int* a = D[0];

    for(int i = 0; i < R; i++){
        printf(" | ");
        for(int j = 0; j < C; j++){
            printf(" %i ",*(a+i+j));
        }
        printf(" | \n");
    }
    return 0;
}
