#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <signal.h>
#include <memory.h>

pthread_mutex_t MUL_LOCK;
pthread_mutex_t SCM_LOCK;
pthread_mutex_t ADD_LOCK;
pthread_mutex_t SUB_LOCK;

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
    
    pthread_mutex_lock(&SCM_LOCK);
    
    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = ((int)A_RAY[i*ACC+j])*(KNT);
        }
    }
    
    pthread_mutex_unlock(&SCM_LOCK);
    
    return NULL;
}

void* KM2(void* A){
    int* A_RAY = *((int**)A+0);
    int* R_RAY = *((int**)A+1);
    
    int KNT = *(*((int**)A+2));
    int ARC = *(*((int**)A+3));
    int ACC = *(*((int**)A+4));
    
    pthread_mutex_lock(&SCM_LOCK);
    
    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = ((int)A_RAY[i*ACC+j])*(KNT);
        }
    }
    
    pthread_mutex_unlock(&SCM_LOCK);
    
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
    
    pthread_mutex_lock(&SUB_LOCK);
    
    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] - (int)B_RAY[i*ACC+j];
        }
    }
    
    pthread_mutex_unlock(&SUB_LOCK);
    
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
    
    pthread_mutex_lock(&ADD_LOCK);

    int WRC = returnRowCount(ARC);
    for(int i = 0; i != WRC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }

    pthread_mutex_unlock(&ADD_LOCK);

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
    
    pthread_mutex_lock(&SUB_LOCK);
    
    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] - (int)B_RAY[i*ACC+j];
        }
    }
    
    pthread_mutex_unlock(&SUB_LOCK);
    
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
    
    pthread_mutex_lock(&ADD_LOCK);

    int WRC = ARC-returnRowCount(ARC);
    for(int i = WRC+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            R_RAY[i*ACC+j] = (int)A_RAY[i*ACC+j] + (int)B_RAY[i*ACC+j];
        }
    }

    pthread_mutex_unlock(&ADD_LOCK);

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
    
    pthread_mutex_lock(&MUL_LOCK);
   
    int WorkingRowCount = returnRowCount(ARC);

    for(int i = 0; i != WorkingRowCount; i++){
        for(int j = 0; j < ACC; j++){
            for(int k = 0; k < BRC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }

    pthread_mutex_unlock(&MUL_LOCK);

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
    
    pthread_mutex_lock(&MUL_LOCK);
   
    int WorkingRowCount = ARC-returnRowCount(ARC);

    for(int i = WorkingRowCount+1; i != ARC; i++){
        for(int j = 0; j < ACC; j++){
            for(int k = 0; k < BRC; k++){
                R_RAY[i*BCC+j] += A_RAY[i*ARC+k]*B_RAY[k*BCC+j];
            }
        }
    }

    pthread_mutex_unlock(&MUL_LOCK);

    return NULL;
}

void Multiply(void* DATA){

    pthread_mutex_init(&MUL_LOCK,NULL);

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,MF1,DATA);
    pthread_create(&T2,NULL,MF2,DATA);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&MUL_LOCK);
}

void ScalarMul(void* DATA){

    pthread_mutex_init(&SCM_LOCK,NULL);

    pthread_t K1;
    pthread_t K2;

    pthread_create(&K1,NULL,KM1,DATA);
    pthread_create(&K2,NULL,KM2,DATA);

    pthread_join(K1,NULL);
    pthread_join(K2,NULL);

    pthread_mutex_destroy(&SCM_LOCK);
}

void Add(void* DATA){

    pthread_mutex_init(&ADD_LOCK,NULL);

    pthread_t A1;
    pthread_t A2;

    pthread_create(&A1,NULL,AF1,DATA);
    pthread_create(&A2,NULL,AF2,DATA);

    pthread_join(A1,NULL);
    pthread_join(A2,NULL);

    pthread_mutex_destroy(&ADD_LOCK);
}

void Sub(void* DATA){

    pthread_mutex_init(&SUB_LOCK,NULL);

    pthread_t A1;
    pthread_t A2;

    pthread_create(&A1,NULL,SF1,DATA);
    pthread_create(&A2,NULL,SF2,DATA);

    pthread_join(A1,NULL);
    pthread_join(A2,NULL);

    pthread_mutex_destroy(&SUB_LOCK);
}
