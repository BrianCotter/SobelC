/*
Author: Brian Cotter
File:   readWrite.h
Desc:   Purpose of this is file is to define functions to
read binary data from pgm files as well as write to 
new pgm files.
File has minimal comments as derived from lab provided example
code to read/write
*/



#include <stdio.h>
#include <stdlib.h> 

#ifndef READWRITE_H
#define READWRITE_H

unsigned char ** loadImage(unsigned int* sizeX, unsigned int* sizeY, char fname[]);

void writeImage(unsigned char ** image, unsigned int sizeX, unsigned int sizeY, char fname[]);

#endif /*READWRITE_H*/




















