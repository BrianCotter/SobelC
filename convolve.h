/*
Author: Brian Cotter
File: convolve.h
Desc: Implementation of convolution for image
processing in the spatial domain. 
Takes any image array (and its size) along with any 3x3 filter array
*/

#ifndef CONVOLVE_H
#define CONVOLVE_H

#include <stdio.h>
#include <math.h>
#include "array2D.h"

#define INTENSITY       255
#define MASK_X            3
#define MASK_Y            3
#define THRESHOLD_CAKE  185

unsigned char ** convolve(unsigned char **image, unsigned int sizeX, unsigned int sizeY, int kernel[MASK_X][MASK_Y]);


#endif /*CONVOLVE_H*/
