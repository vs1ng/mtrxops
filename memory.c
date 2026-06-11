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

    printf("D : %p\nD[0] : %p\nD[1] : %p\nD[2] : %p\n",D,D[0],D[1],D[2]);
    printf("&A = %p\n*S = &A[0][0] = %p\n",&A,S);
    for(int i = 0; i != 5; i++){
        printf(" D+%i : %p\t *(D+%i) : %p\n",i,D[i],i,*(D+i));
    }
    for(int i = 0; i != 5; i++){
        for(int j = 0; j!= 5; j++){
            printf(" D+%i+%i : %p\t *(D+%i+%i) : %p\n",i,j,D+i+j,i,j,*(D+i+j));
        }
    }
    for(int i = 0; i < 3; i++){
        printf(" | ");
        for(int j = 0; j < 3; j++){
            printf(" %i : %p ",A[i][j],&A[i][j]);
        }
        printf(" | \n");
    }
    return 0;
}
