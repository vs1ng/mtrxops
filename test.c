#include <pthread.h>
#include <stdio.h>

void* run(void* arg){
    puts("hi from thread!");
    pthread_exit(NULL);
    puts("bye from thread!");
    return NULL;
}

int main(void){
    pthread_t T;
    pthread_create(&T,NULL,run,NULL);
    pthread_join(T,NULL);
    puts("bye from program!");
    return 0;
}
