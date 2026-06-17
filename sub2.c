#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <signal.h>
#include <memory.h>

pthread_mutex_t LOCK;

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

void* KM1(void* A){
    int* A_RAY = *((int**)A+0);
    int* R_RAY = *((int**)A+1);
    
    int KNT = *(*((int**)A+2));
    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    pthread_mutex_lock(&LOCK);
    
    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = ((int)A_RAY[i*ACC+j])*(KNT);
        }
    }
    
    pthread_mutex_unlock(&LOCK);
    
    return NULL;
}

void* KM2(void* A){
    int* A_RAY = *((int**)A+0);
    int* R_RAY = *((int**)A+1);
    
    int KNT = *(*((int**)A+2));
    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    pthread_mutex_lock(&LOCK);
    
    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = ((int)A_RAY[i*ACC+j])*(KNT);
        }
    }
    
    pthread_mutex_unlock(&LOCK);
    
    return NULL;
}

void* SF1(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);
    
    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    if(ARC == BRC){
        if(ACC == BCC){
        } else {
            puts("Col Count of A != Col Count of B");
            exit(EXIT_FAILURE);
        }
    } else {
        puts("Row Count of A != Row Count of B");
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_lock(&LOCK);
    
    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }
    
    pthread_mutex_unlock(&LOCK);
    
    return NULL;
}

void* AF1(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    if(ARC == BRC){
        if(ACC == BCC){
        } else {
            puts("Col Count of A != Col Count of B");
            exit(EXIT_FAILURE);
        }
    } else {
        puts("Row Count of A != Row Count of B");
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_lock(&LOCK);

    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }

    pthread_mutex_unlock(&LOCK);

    return NULL;
}

void* SF2(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);
    
    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    if(ARC == BRC){
        if(ACC == BCC){
        } else {
            puts("Col Count of A != Col Count of B");
            exit(EXIT_FAILURE);
        }
    } else {
        puts("Row Count of A != Row Count of B");
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_lock(&LOCK);
    
    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }
    
    pthread_mutex_unlock(&LOCK);
    
    return NULL;
}

void* AF2(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    if(ARC == BRC){
        if(ACC == BCC){
        } else {
            puts("Col Count of A != Col Count of B");
            exit(EXIT_FAILURE);
        }
    } else {
        puts("Row Count of A != Row Count of B");
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_lock(&LOCK);

    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }

    pthread_mutex_unlock(&LOCK);

    return NULL;
}


void* MF1(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    pthread_mutex_lock(&LOCK);
   
    int WorkingRowCount = returnRowCount(ARC);

    for(int i = 0; i != WorkingRowCount; i++){
        for(int j = 0; j < ACC; j++){
            for(int k = 0; k < BRC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }

    pthread_mutex_unlock(&LOCK);

    return NULL;
}

void* MF2(void* A){
    int* A_RAY = *((int**)A+0);
    int* B_RAY = *((int**)A+1);
    int* R_RAY = *((int**)A+6);

    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    int BRC = *(*((int**)A+2));
    int BCC = *(*((int**)A+5));
    
    pthread_mutex_lock(&LOCK);
   
    int WorkingRowCount = ARC-returnRowCount(ARC);

    for(int i = WorkingRowCount+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            for(int k = 0; k < BRC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }

    pthread_mutex_unlock(&LOCK);

    return NULL;
}

void Multiply(void* DATA){

    pthread_mutex_init(&LOCK,NULL);

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,MF1,DATA);
    pthread_create(&T2,NULL,MF2,DATA);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&LOCK);
}

void ScalarMul(void* DATA){

    pthread_mutex_init(&LOCK,NULL);

    pthread_t K1;
    pthread_t K2;

    pthread_create(&K1,NULL,KM1,DATA);
    pthread_create(&K2,NULL,KM2,DATA);

    pthread_join(K1,NULL);
    pthread_join(K2,NULL);

    pthread_mutex_destroy(&LOCK);
}

void Add(void* DATA){

    pthread_mutex_init(&LOCK,NULL);

    pthread_t A1;
    pthread_t A2;

    pthread_create(&A1,NULL,AF1,DATA);
    pthread_create(&A2,NULL,AF2,DATA);

    pthread_join(A1,NULL);
    pthread_join(A2,NULL);

    pthread_mutex_destroy(&LOCK);
}

void Sub(void* DATA){

    pthread_mutex_init(&LOCK,NULL);

    pthread_t A1;
    pthread_t A2;

    pthread_create(&A1,NULL,SF1,DATA);
    pthread_create(&A2,NULL,SF2,DATA);

    pthread_join(A1,NULL);
    pthread_join(A2,NULL);

    pthread_mutex_destroy(&LOCK);
}

int main(void){

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
    memset(RES, 0, sizeof(RES));
    
    void* DATA[7] = {
                    &A[0][0],
                    &B[0][0],
                    &brc,
                    &arc,
                    &acc,
                    &bcc,
                    &RES[0][0]
    };

    Add(DATA);
    display(&RES[0][0],arc,bcc);
    return 0;
}
