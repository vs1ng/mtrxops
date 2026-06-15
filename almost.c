#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <signal.h>

pthread_mutex_t LOCK;
atomic_int C = ATOMIC_VAR_INIT(0);

void catch(int sig){
    puts("seg fault");
    exit(EXIT_FAILURE);
}

int returnRowCount(int RC){
    if(RC%2 == 0){
        return RC/2;
    } else {
        return (RC+1)/2;
    }
}

void display(int* A,int r, int c){
    signal(SIGSEGV,catch);

    printf("\n");
    for(int I = 0; I < r; I++){
        printf("\n| ");
        for(int J = 0; J < c; J++){
            printf(" %i ",A[I*c+J]);
        }
        printf(" | ");
    }
    printf("\n");
}

void* F1(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    pthread_mutex_lock(&LOCK);
   
    int WorkingRowCount = returnRowCount(ARC);
    puts("[F1]: A : ");
    display(A_RAY,ARC,ACC);
    puts("[F1]: B: ");
    display(B_RAY,BRC,BCC);
    puts("[F1]: A x B: ");
    display(R_RAY,ARC,BCC);

    for(int i = 0; i != WorkingRowCount; i++){
        for(int j = 0; j < ARC; j++){
            for(int k = 0; k < ARC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }
    
    puts("[F1]: A : ");
    display(A_RAY,ARC,ACC);
    puts("[F1]: B: ");
    display(B_RAY,BRC,BCC);
    puts("[F1]: A x B: ");
    display(R_RAY,ARC,BCC);

    pthread_mutex_unlock(&LOCK);

    return NULL;
}

void* F2(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    pthread_mutex_lock(&LOCK);
   
    int WorkingRowCount = ARC-returnRowCount(ARC);
    puts("[F2]: A : ");
    display(A_RAY,ARC,ACC);
    puts("[F2]: B: ");
    display(B_RAY,BRC,BCC);
    puts("[F2]: A x B: ");
    display(R_RAY,ARC,BCC);

    for(int i = WorkingRowCount; i != ARC; i++){
        for(int j = 0; j < ARC; j++){
            for(int k = 0; k < ARC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }
    
    puts("[F2]: A : ");
    display(A_RAY,ARC,ACC);
    puts("[F2]: B: ");
    display(B_RAY,BRC,BCC);
    puts("[F2]: A x B: ");
    display(R_RAY,ARC,BCC);

    pthread_mutex_unlock(&LOCK);

    return NULL;
}


int main(void){

    pthread_mutex_init(&LOCK,NULL);

    int A[5][5] = { 
                    {1,2,3,4,5},
                    {6,7,8,9,10},
                    {11,12,13,14,15},
                    {16,17,18,19,20},
                    {21,22,23,24,25},

    };

    int B[5][5] = {
                    {1,2,3,4,5},
                    {6,7,8,9,10},
                    {11,12,13,14,15},
                    {16,17,18,19,20},
                    {21,22,23,24,25}
    };

    int arc = sizeof(A)/sizeof(A[0]);
    int acc = sizeof(A[0])/sizeof(A[0][0]);

    int brc = sizeof(B)/sizeof(B[0]);
    int bcc = sizeof(B[0])/sizeof(B[0][0]);

    int RES[arc][bcc];

    void* DATA[7] = {
                    &A[0][0],
                    &B[0][0],
                    &brc,
                    &arc,
                    &acc,
                    &bcc,
                    &RES[0][0]
    };

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,F1,DATA);
    pthread_create(&T2,NULL,F2,DATA);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&LOCK);
    return 0;
}
