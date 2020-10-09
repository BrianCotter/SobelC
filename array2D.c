/*
Author: Brian Cotter
File: array2d.c
Desc: Dynamic allocation of 2-d arrays by single function call. 
      Keeps main program neater. 
*/

#include "array2D.h"

// Allocate an array of size X * Y
unsigned char ** createArray(int X, int  Y) {
    int i, j; // Loop Iterators

    // Alllocate 2D array using pointer to a pointer
    unsigned char **arr = (unsigned char **)malloc(X * sizeof(unsigned char *));
    
    // For X rows holds pointer to array size Y
    for (i = 0; i<X; i++)
        arr[i] = (unsigned char *)malloc(Y * sizeof(unsigned char));

    // Init as all 0's
    for (i = 0; i < Y; i++) {
        for (j = 0; j < X; j++) { 
            arr[i][j] = 0;
        }
    }

    return arr;
}


// Free dynamicaly allocated memory
void freeArray(unsigned char ** arr) {
    free(*arr);
    free(arr);
}
