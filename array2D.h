/*
Author: Brian Cotter
File: array2d.h
Desc: Dynamically Allocate an array of size X * Y using 
pointer to a pointer 

*/

#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY2D_H
#define ARRAY2D_H

unsigned char ** createArray(int X, int Y);

void freeArray(unsigned char ** arr);


#endif /*ARRAY2D_H*/
