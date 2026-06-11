#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>

pthread_mutex_t LOCK;
atomic_int C = ATOMIC_VAR_INIT(0);


void display(int* A,int r, int c){
    printf("\n\t|");
    for(int I = 0; I < r; I++){
        printf("\n| ");
        for(int J = 0; J < c; J++){
            printf(" %i ",*(A+I+J));
        }
        printf(" | ");
    }
    printf("\n");
}

void* F1(void* A){
    int* ARRAY = ((int*)A+0);
    int RC = *((int*)A+1);
    int CC = *((int*)A+2);

    pthread_mutex_lock(&LOCK);
    printf(" A before :");
    display(ARRAY,RC,CC);
    for(int i = 0; i != 7; i++){
        *((int*)A+i) = 1;
    }
    printf(" A after :");
    display(A,RC,CC);
    pthread_mutex_unlock(&LOCK);
    return NULL;
}

void* F2(void* A){
    pthread_mutex_lock(&LOCK);
    printf(" A before :"); display(A,12);
    for(int j = 7; j != 13; j++){
        *((int*)A+j) = 2;
    }
    printf(" A after :"); display(A,12);
    pthread_mutex_unlock(&LOCK);
    return NULL;
}

int main(void){
    pthread_mutex_init(&LOCK,NULL);

    int A[2][2] = { 
                    {1,2},
                    {3,4}
    };

    int arc = sizeof(A)/sizeof(A[0]);
    int acc = sizeof(A[0])/sizeof(A[0][0]);

    int DATA[3] = {
                    &A[0][0],
                    &arc,
                    &acc
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
