#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>

pthread_mutex_t LOCK;
atomic_int C = ATOMIC_VAR_INIT(0);


void display(int* A,int l){
    printf("\n");
    for(int I = 0; I < l; I++){
        printf("| %i |",*(A+I));
    }
    printf("\n");
}

void* F1(void* A){
    printf("| LOCKG | F1 | C : %i |\n",C);
    pthread_mutex_lock(&LOCK);
    printf(" A before :"); display(A,6);
    for(int i = 0; i != 4; i++){
        *((int*)A+i) = 1;
    }
    printf(" A after :"); display(A,6);
    printf("| UNLOK | F1 | C : %i |\n",C);
    pthread_mutex_unlock(&LOCK);
    sleep(2);

    return NULL;
}

void* F2(void* A){
    printf("| LOCKG | F2 | C : %i |\n",C);
    pthread_mutex_lock(&LOCK);
    printf(" A before :"); display(A,6);
    for(int j = 4; j != 7; j++){
        *((int*)A+j) = 2;
    }
    printf(" A after :"); display(A,6);
    printf("| UNLOK | F2 | C : %i |\n",C);
    pthread_mutex_unlock(&LOCK);
    sleep(2);
    return NULL;
}

int main(void){
    pthread_mutex_init(&LOCK,NULL);

    void* A = calloc(6,sizeof(int));

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,F1,A);
    pthread_create(&T2,NULL,F2,A);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&LOCK);
    free(A);
    A = NULL;
    return 0;
}
