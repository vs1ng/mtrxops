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
        return (RC/2)+1;
    } else {
        return (RC+1)/2;
    }
}

void display(int* A,int r, int c){
    signal(SIGSEGV,catch);

    printf("\n\t|");
    for(int I = 0; I < r; I++){
        printf("\n| ");
        for(int J = 0; J < c; J++){
            printf(" %p ",A+I+J);
        }
        printf(" | ");
    }
    printf("\n");
}

void* F1(void* A){
    int* ARRAY = *((int**)A+0);
    int RC = *(*((int**)A+1));
    int CC = *(*((int**)A+2));
    printf("Address of Array: %p\nRC = %i\nCC = %i\n",ARRAY,RC,CC);
    /*
    int* ARRAY = (A+0);
    int RC = *((int*)(A+1));
    int CC = *((int*)(A+2));

    pthread_mutex_lock(&LOCK);

    printf(" A before :");
    display(ARRAY,RC,CC);
    
    int WorkingRowCount = returnRowCount(RC);

    for(int i = 0; i != WorkingRowCount; i++){
        for(int j = 0; j < CC; j++){
            *((int*)A+i+j) = 1;
        }
    }
    
    printf(" A after :");
    display(A,RC,CC);
    
    pthread_mutex_unlock(&LOCK);
    */
    return NULL;
}
/*
void* F2(void* A){
    int* ARRAY = ((int*)A+0);
    int RC = *(int*)(A+1);
    int CC = *(int*)(A+2); 

    pthread_mutex_lock(&LOCK);
    
    printf(" A before :");
    display(ARRAY,RC,CC);
    int WorkingRowCount = RC-returnRowCount(RC);

    for(int i = 0; i != WorkingRowCount; i++){
        for(int j = 0; j < CC; j++){
            *((int*)A+i+j) = 2;
        }
    }
    printf(" A after :");
    display(A,RC,CC);
    
    pthread_mutex_unlock(&LOCK);
    return NULL;
}
*/
int main(void){

    pthread_mutex_init(&LOCK,NULL);

    int A[2][2] = { 
                    {1,2},
                    {3,4}
    };

    int arc = sizeof(A)/sizeof(A[0]);
    int acc = sizeof(A[0])/sizeof(A[0][0]);

    printf("[MAIN]:\tAddr(A) : %p\tAddr(arc) : %p\tAddr(acc) : %p\n",&A,&arc,&acc);
    void* DATA[3] = {
                    &A[0][0],
                    &arc,
                    &acc
    };

    printf("[MAIN]:\tAddr(DATA) : %p\n",&DATA);
    for(int I = 0; I < 3; I++){
        printf("[MAIN]:\tD[%i] = %p | %p\n",I,DATA+I,*(DATA+I));
    }
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("[MAIN]:\tA[%i][%i] = %i : %p\n",i,j,A[i][j],&A[i][j]);
        }
    }
/* 
    puts("[MAIN]: setting ARRAY  = *(DATA+0)");
    int* ARRAY = *(DATA+0); 
    printf("[MAIN]: ARRAY = %p\n",ARRAY);

    puts("[MAIN]: setting RC = *(DATA+1)");
    int* RC = *(DATA+1); 
    printf("[MAIN]: RC = %p\n",RC);

    puts("[MAIN]: setting CC = *(DATA+2)");
    int* CC = *(DATA+2); 
    printf("[MAIN]: CC = %p\n",CC);

    puts("[MAIN]: setting RCV = (int*)*(DATA+1)");
    int* RCV = (int*)*(DATA+1); 
    printf("[MAIN]: *RCV = %i\n",*RC);

    puts("[MAIN]: setting CCV = *(DATA+2)");
    int* CCV = *(DATA+2); 
    printf("[MAIN]: CCV = %p\n",CC);


    exit(EXIT_SUCCESS);
*/
    pthread_t T1;
//    pthread_t T2;

    pthread_create(&T1,NULL,F1,DATA);
 // pthread_create(&T2,NULL,F2,DATA);

    pthread_join(T1,NULL);
 //   pthread_join(T2,NULL);

    pthread_mutex_destroy(&LOCK);
    return 0;
}
