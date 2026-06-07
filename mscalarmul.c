#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define r0 return 0
#pragma optimize("O3")

struct row{
    int r_a;
    int r_b;
};

struct col{
    int c_a;
    int c_b;
};

struct sizes{
    struct row R;
    struct col C;
};

void catch(int sig){
    puts("Memory access illegally attempted!");
    exit(EXIT_FAILURE);
}

void bye(int* ptr){
    free(ptr);
    ptr = NULL;
}

void display(int* M, int rc, int cc){
    for(int i = 0; i < rc; i++){
        printf(" | ");
        for(int j = 0; j < cc; j++){
            printf(" %i ",*(M+i+j));
        }
        printf(" |\n");
    }
}

void ScalarMul(int K, int* A, int RA, int CA){
    for(int i = 0; i < RA; i++){
        for(int j = 0; j < CA; j++){
            printf("value at (%i,%i) before mul with %i\n",i,j,K);
            *(A+i+j) = K*(int)(*(A+i+j));
            printf("value at (%i,%i) after  mul with %i\n",i,j,K);
        }
    }
    printf(" %i(A) = \n",K);
    display(A+0+0,RA,CA);
}

int main(void){
    signal(SIGSEGV,catch);
    struct sizes DATA;

    int A[2][2] = {
                    {1,2},
                    {3,4}
    };

    int B[2][2] = {
                    {4,5},
                    {6,7}
    };

    DATA.R.r_a = (int)(sizeof(A)/sizeof(A[0]));
    DATA.C.c_a = (int)(sizeof(A[0])/sizeof(A[0][0]));
    
    DATA.R.r_b = (int)(sizeof(B)/sizeof(B[0]));
    DATA.C.c_b = (int)(sizeof(B[0])/sizeof(B[0][0]));

    puts("A:");
    display(&A[0][0],DATA.R.r_a,DATA.C.c_a);
    
    ScalarMul(3,&A[0][0],DATA.R.r_a,DATA.C.c_a);
    r0;
}
