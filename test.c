#include <stdio.h>
#include <pthread.h>

pthread_mutex_t LOCK;

void* F1(void* A){

    return NULL;
}

void* F2(void* A){

    return NULL;
}

int main(void){
    pthread_mutex_init(&LOCK,NULL);

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,F1,NULL);
    pthread_create(&T2,NULL,F2,NULL);

    pthread_mutex_destroy(&LOCK);
    
    return 0;
}
