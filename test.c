#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

pthread_mutex_t LOCK;
atomic_int C = ATOMIC_VAR_INIT(0);

int A[6];

void* F1(void* A){
    printf("| LOCKG | F1 | C : %i |\n",C);
    pthread_mutex_lock(&LOCK);
    atomic_fetch_add(&C,1);
    printf("| UNLOK | F1 | C : %i |\n",C);
    pthread_mutex_unlock(&LOCK);
    sleep(2);

    return NULL;
}

void* F2(void* A){
    printf("| LOCKG | F2 | C : %i |\n",C);
    pthread_mutex_lock(&LOCK);
    atomic_fetch_add(&C,1);
    printf("| UNLOK | F2 | C : %i |\n",C);
    pthread_mutex_unlock(&LOCK);
    sleep(2);
    return NULL;
}

int main(void){
    pthread_mutex_init(&LOCK,NULL);

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1,NULL,F1,NULL);
    pthread_create(&T2,NULL,F2,NULL);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&LOCK);
    
    return 0;
}
