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
#include "moprs.h"

int main(){
    int A[2][2] = {{1,2},{3,4}};
    int B[2][2] = {{1,1},{1,1}};
    display(&A[0][0],2,2);
    Multiply(&A[0][0],&B[0][0],2,2,2,2);
    r0;
}
