# MOprs : Matrix Operations 
## MOprs is a multi-threaded matrix operations library that ME I VINAYAK SINGH made from scratch
### Features:

1. Display Matrices
2. Matrix Multiplication
3. Addition
4. Subtraction
5. Scalar Multiplication

## Usage-Guidance 

#### 1. Display()

* Import the library and call the display function :)
```
#include "moprs.h"
...
    display(&PointerToFirstElement,RowCount,ColumnCount);
...
```
![](sampling/displaydemo.png)

#### 2. Multi-Threaded Multiply():

1. Define both Matrices

![](sampling/mmstep1.png)

2. Define row, column counts along with a resultant matrix. 

```
memset(RESULTANT, 0, sizeof(RESULTANT)):
```
![](sampling/mmstep2.png)

3. Define an array containing the addresses of the variables in the following manner:
```
void* DATA[7] = { 
                    &A1[0][0],
                    &A2[0][0],
                    &A2_RowCount,
                    &A1_RowCount,
                    &A1_ColCount,
                    &A2_ColCount,
                    &Resultant[0][0]
};
```
![](sampling/mmstep3.png)

4. Call Multiply() on the above array.
```
Multiply(DATA);
```

![](sampling/mmstep4.png)

### Usage:

#### Simply import the header (.h) file and pass in arguements as described 

```
Function(Pointer to Array, Row size, Col. size)
```

e.g : 

![sample](sampling/sample.png)

#### Demo of Addition and Multiplication:

![addmul](sampling/addmul.png)

#### Memory Address Mapping on x86 64-bit UNIX systems

![mem](sampling/memory.png)
