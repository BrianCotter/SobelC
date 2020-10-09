/*
Author: Brian Cotter
File: convolve.c
Desc: Imlementation of convolution for image
processing in the spatial domain. 
Takes any image array (and its size) along with any 3x3 filter array
*/

#include "convolve.h"

unsigned char** convolve(unsigned char **image, unsigned int sizeX, unsigned int sizeY, int kernel[MASK_X][MASK_Y]) {
    float pixVal;  // Keep track of the current pixel value in loop
    float min, max;
    int x, y, i, j; // Loop indexes

    unsigned char** output;
    output = createArray(sizeX, sizeY);
    
    //Image we are working with is already padded
    min = 0;
    max = 0;
    for(y = 1; y < sizeY-1; y++) {
        for(x = 1; x < sizeX-1; x++) {
            pixVal = 0.0;
            for(j = -1; j < 2; j++) {
                for(i = -1; i < 2; i++) {
                    pixVal += kernel[j + 1][i + 1] * (float)image[y + j][x + i];
                }
            }
            // Get max and min values for normalization
            if(pixVal < min)
                min = pixVal;
            if(pixVal > max)
                max = pixVal;
        } 
    }

    // Assign values to output array (apply normalization)
    int normVal = 0;;
    for(y = 1; y < sizeY-1; y++) {
        for(x = 1; x < sizeX-1; x++) {
            pixVal = 0.0;
            for(j = -1; j < 2; j++) {
                for(i = -1; i < 2; i++) {
                    pixVal += kernel[j + 1][i + 1] * (int)image[y + j][x + i];
                }
            }
            // Normalization
            pixVal = abs(pixVal);
            pixVal = INTENSITY * (pixVal-min) / (max - min); 
      
            output[y][x] = (unsigned char)pixVal;        
        } 
    } 
    return output;
}
