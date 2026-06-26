/*
 *  mtrxops : multithreaded matrix operations library made from C by vinayak singh
 *  Copyright (C) 2026  VINAYAK SINGH
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 b u*t WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.
 
 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define r0 return 0
#pragma optimize("O3")

struct row{
    int r_a;
    int r_b;
};

struct col{
    int c_a;
    int c_b;
};

struct sizes{
    struct row R;
    struct col C;
};

void catch(int sig){
    puts("Memory access illegally attempted!");
    exit(EXIT_FAILURE);
}

void bye(int* ptr){
    free(ptr);
    ptr = NULL;
}

void display(int* M, int rc, int cc){
    for(int i = 0; i < rc; i++){
        printf(" | ");
        for(int j = 0; j < cc; j++){
            printf(" %i ",*(M+i+j));
        }
        printf(" |\n");
    }
}

void ScalarMul(int K, int* A, int RA, int CA){
    for(int i = 0; i < RA; i++){
        for(int j = 0; j < CA; j++){
            printf("value at (%i,%i) before mul with %i : %i\n",i,j,K,*(A+i+j));
            *(A+i+j) = K*(int)(*(A+i+j));
            printf("value at (%i,%i) after  mul with %i : %i\n",i,j,K,*(A+i+j));
        }
    }
    printf(" %i(A) = \n",K);
    display(A+0+0,RA,CA);
}

int main(void){
    signal(SIGSEGV,catch);
    struct sizes DATA;

    int A[2][2] = {
                    {1,2},
                    {3,4}
    };


    DATA.R.r_a = (int)(sizeof(A)/sizeof(A[0]));
    DATA.C.c_a = (int)(sizeof(A[0])/sizeof(A[0][0]));

    puts("A:");
    display(&A[0][0],DATA.R.r_a,DATA.C.c_a);
    ScalarMul(3,&A[0][0],DATA.R.r_a,DATA.C.c_a);
    r0;
}
