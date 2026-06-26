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

void Add(int* A, int* B, int RA, int RB, int CA, int CB){
    int* C = calloc(RA*CB, sizeof( *(A+0+0)));
    if(RA==RB){
        if(CA==CB){
        } else {
            raise(SIGSEGV);
        }
    } else {
        raise(SIGSEGV);
    }
    int ROW = RA;
    int COL = CA;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < ROW; j++){
            *(C+i+j) = (int)(*(A+i+j)) + (int)(*(B+i+j));
        }
    }
    puts("A + B  = ");
    display(C+0+0,RA,CB);
    bye(C);
}

int main(void){
    signal(SIGSEGV,catch);
    struct sizes DATA;

    int A[2][2] = {
                    {1,2},
                    {3,4}
    };

    int B[2][2] = {
                    {4,5},
                    {6,7}
    };

    DATA.R.r_a = (int)(sizeof(A)/sizeof(A[0]));
    DATA.C.c_a = (int)(sizeof(A[0])/sizeof(A[0][0]));
    
    DATA.R.r_b = (int)(sizeof(B)/sizeof(B[0]));
    DATA.C.c_b = (int)(sizeof(B[0])/sizeof(B[0][0]));

    puts("A:");
    display(&A[0][0],DATA.R.r_a,DATA.C.c_a);

    puts("B:");
    display(&B[0][0],DATA.R.r_b,DATA.C.c_b);
    Add(&A[0][0],&B[0][0],DATA.R.r_a,DATA.R.r_b,DATA.C.c_a,DATA.C.c_b);
    r0;
}
