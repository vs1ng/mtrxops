#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#define r0 return 0

pthread_mutex_t lock;

atomic_int C = ATOMIC_VAR_INIT(0); 

void* F1(void* arg){
    for(int i = 0; i < 4; i++){
        printf("F1: i = %i\t C = %i\n",i,C);
        atomic_fetch_add(&C,i);
    }
    return NULL;
}

void* F2(void* arg){
    for(int j = 0; j < 4; j++){
        printf("F2: j = %i\tC = %i\n",j,C);
        atomic_fetch_add(&C,j);
    }
    return NULL;
}

int main(void){
    pthread_mutex_init(&lock,NULL);
    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,F1,NULL);
    pthread_create(&T2,NULL,F2,NULL);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&lock);
    r0;
}


