#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#define r0 return 0

pthread_mutex_t lock;

void* F1(void* arg){
    puts("F1");
    return NULL;
}

void* F2(void* arg){
    puts("F2");
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


