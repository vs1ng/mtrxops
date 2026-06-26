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
			printf(" %i ",M[i*cc+j]);
		}
		printf(" |\n");
	}
}

void Multiply(int* A, int* B, int RA, int RB, int CA, int CB){
	if(RB!=CA){
		puts("A x B not defined.");
		raise(SIGTERM);
	}
	int* C = calloc(RA*CB, sizeof( *(A+0+0)));
	if(!C){
		raise(SIGSEGV);
	}
	for(int i = 0; i < RA; i++){
		for(int j = 0; j < CB; j++){
			for(int k = 0; k < CA; k++){
				C[i*CB+j] += (int)A[i*CA+k]*(int)B[k*CB+j];
			}
		}
	}
	puts("A x B  = ");
	display(C+0+0,RA,CB);
	bye(C);
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
		for(int j = 0; j < COL; j++){
			C[i*COL+j] = (int)A[i*CA+j] + (int)B[i*CA+j];
		}
	}
	puts("A + B  = ");
	display(C+0+0,RA,CB);
	bye(C);
}

void ScalarMul(int K, int* A, int RA, int CA){
	for(int i = 0; i < RA; i++){
		for(int j = 0; j < CA; j++){
			printf("value at (%i,%i) before mul with %i : %i\n",i,j,K,*(A+i+j));
			A[i*CA+j] = K*(int)A[i*CA+j];
			printf("value at (%i,%i) after  mul with %i : %i\n",i,j,K,*(A+i+j));
		}
	}
	printf(" %i(A) = \n",K);
	display(A+0+0,RA,CA);
}

void Sub(int* A, int* B, int RA, int RB, int CA, int CB){
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
		for(int j = 0; j < COL; j++){
			C[i*COL+j] = (int)A[i*CA+j] - (int)B[i*CA+j];
		}
	}
	puts("A - B  = ");
	display(C+0+0,RA,CB);
	bye(C);
}
