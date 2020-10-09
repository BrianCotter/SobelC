/*
Author: Brian Cotter
File: sobel.c

Sobel edge detection implementation. 
Spatial domain processing (Spatial convolution with 3x3 kernel)
Test the effects of sobel edge detection with noisy image. 
Test the effects of sobel edge detection with noisy averaged image.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "readWrite.h"
#include "convolve.h"
#include "array2D.h"

#define BLACK       0
#define WHITE     255 // 8-bit image resolution
#define MAX_NOISE  40 // Change this macro to adjust added noise level


// addNoise() function, generate random noise within range to add to every pixel
int addNoise() {
  int noise; 
  noise = (rand()%MAX_NOISE) - (MAX_NOISE/2);
  return noise;
}


int main(int argc, char *argv[]) {
    /* Prepare input image */
    char *inputFile = "cake.pgm"; 
    int i, j, x, y; // Loop indexes (use int to account size > 8-bit)

    // Read input image into array
    unsigned char** inputImage;
    unsigned int sizeX, sizeY; // Use int not char to store sizes > 8-bit
    inputImage = loadImage(&sizeX, &sizeY, inputFile);
  
    // Pad array with 0's to perimeter of input image
    unsigned char** paddedImage;
    unsigned int paddedX, paddedY;
    paddedX = sizeX + 2;  
    paddedY = sizeY + 2;
    // Allocate a 258x258 padded image 
    paddedImage = createArray(paddedX, paddedY);

    // Image indexes now range [0-257]
    for(x = 0; x < paddedX; x++) {
        for(y = 0; y < paddedY; y++) {

            // If inside padded region
            if(x > 0 && x < (paddedX-1)) {
      	        if(y > 0 && y < (paddedY-1)) {	 
  
                // Copy input image data to padded
	        paddedImage[x][y] = inputImage[x -1][y - 1];
                }
            }
        }
    }

    /* Start Sobel algorithm implementation */
    // 3x3 vertical Sobel kernel used to compute the gradient in the Y direction
    int sobelV[MASK_X][MASK_Y] = {{-1, 0, 1},
                                  {-2, 0, 2},
                                  {-1, 0, 1}};
  
    // 3x3 horizontal Sobel kernel used to compute the gradient in the X direction
    int sobelH[MASK_X][MASK_Y] = {{-1,-2,-1},
		                  { 0, 0, 0},
		                  { 1, 2, 1}};

    // First, convolve with horizontal Sobel kernel
    unsigned char** gradientX; 
    gradientX = convolve(paddedImage, paddedX, paddedY, sobelH);  

    // Print the X-gradient to it's own image file
    float pixVal = 0.0;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            pixVal = gradientX[i][j];

            // Use threshold to produce binary image for visualization
            if(pixVal >= THRESHOLD_CAKE)
	        gradientX[i][j] = WHITE;
            else if(pixVal < THRESHOLD_CAKE)
	        gradientX[i][j] = BLACK;
        }
    }
    // Write result of gradient in the X direction to file
    writeImage(gradientX, paddedX, paddedY, "Gx_binary.pgm");  

    // Next, convolve with vertical Sobel kernel
    unsigned char** gradientY;
    gradientY = convolve(paddedImage,paddedX,paddedY,sobelV); 

    // Print the y-gradient to it's own image file
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            pixVal = gradientY[i][j];

            // Use threshold to produce binary image for visualization
            if(pixVal >= THRESHOLD_CAKE)
	        gradientY[i][j] = WHITE;
            else if(pixVal < THRESHOLD_CAKE)
	        gradientY[i][j] = BLACK;
        }
    }
    // Write result of gradient in the X direction to file
    writeImage(gradientY, paddedX, paddedY, "Gy_binary.pgm");

    // Create gradient image array containing the magnitude of gradients
    unsigned char** gradientImage;
    gradientImage = createArray(sizeX,sizeY);  
  
    // Assign to output (binary edge image)
    unsigned char normVal;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            pixVal = sqrt(pow(gradientX[i][j],2)+pow(gradientY[i][j],2));
            //pixVal = gradientX[i][j] + gradientY[i][j]; // (less accurate version)
      
            // Values already normalized by each gradient
            if(pixVal > 255)
                normVal = 255;
            else 
                normVal = (unsigned char)pixVal;

            // Use threshold value to produce a binary image
            if(normVal >= THRESHOLD_CAKE)
	        gradientImage[i][j] = WHITE;
            else if(normVal < THRESHOLD_CAKE)
	        gradientImage[i][j] = BLACK;
        }  
    }

    // Write completed (added noise) binary edge image to file
    writeImage(gradientImage,sizeX,sizeY,"cakeBinaryEdge.pgm"); 

    /* Test Sobel edge detection with added noise to input image */
    // Mask convolved with noisy image for averaging effect
    int average[MASK_X][MASK_Y] = {{1, 1, 1},
                                   {1, 1, 1},
                                   {1, 1, 1}};
 
    unsigned char** noisyImage;
    noisyImage = createArray(sizeX, sizeY);

    srand((unsigned)time(0)); // Seed for random number generation
    int curNoise = 0;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            curNoise = inputImage[i][j];	
            curNoise += addNoise(); // Add noise to every pixel value

            // Take into account adding noise could be greater than 8-bit
	    if(curNoise > 255)
	        noisyImage[i][j] = WHITE; 
            else if(curNoise < 0)
	        noisyImage[i][j] = BLACK;
	    else
                noisyImage[i][j] = (unsigned char)curNoise; 
        }
    }
  
    // Write orignal image with added noise
    writeImage(noisyImage,sizeX,sizeY,"noisyCake.pgm");

    // Allocate a 258x258 padded noisy image
    unsigned char ** paddedNoisyImage;
    paddedNoisyImage = createArray(paddedX, paddedY);
    // Pad noisy image for convolution
    // Image indexes now range [0-257]
    for(x = 0; x < paddedX; x++) {
        for(y = 0; y < paddedY; y++) {
            // If inside padded region
            if(x > 0 && x < (paddedX-1)) {
      	        if(y > 0 && y < (paddedY-1)) {	   
	            // Copy input image data to padded
	            paddedNoisyImage[x][y] = noisyImage[x -1][y - 1];
	        }
            }
        }
    }
    freeArray(noisyImage);

    // Apply the average (smoothing) filter to the noisy image
    // Write over padded array 
    paddedNoisyImage = convolve(paddedNoisyImage, paddedX, paddedY, average);

    /* Use Sobel algorithm to obtain binry edge image*/
    unsigned char ** noisyGradientX; 
    noisyGradientX = convolve(paddedNoisyImage, paddedX, paddedY, sobelH);  
    // Intermediate print the gradient X to an image
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            pixVal = noisyGradientX[i][j];

            // Before writing to file must threshold pixel data
            if(pixVal >= THRESHOLD_CAKE)
	        noisyGradientX[i][j] = WHITE;
            else if(pixVal < THRESHOLD_CAKE)
	        noisyGradientX[i][j] = BLACK;
        }
    }
    // Write result of gradient in the X direction to file
    writeImage(noisyGradientX, paddedX, paddedY, "noisyGx_binary.pgm");  

    unsigned char** noisyGradientY;
    noisyGradientY = convolve(paddedNoisyImage, paddedX, paddedY, sobelV);
    // Intermediate print the gradient X to an image
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            pixVal = noisyGradientY[i][j];

           // Before we can print must threshold pixel data
           if(pixVal >= THRESHOLD_CAKE)
	        noisyGradientY[i][j] = WHITE;
           else if(pixVal < THRESHOLD_CAKE)
	        noisyGradientY[i][j] = BLACK;
        }
    }
    // Write result of gradient in the X direction to file
    writeImage(noisyGradientY, paddedX, paddedY, "noisyGy_binary.pgm");

    unsigned char** noisyGradientImage;
    noisyGradientImage = createArray(sizeX,sizeY); 
  
    // Assign to output (binary edge image)
    normVal = 0.0;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            //pixVal = noisyGradientX[i][j] + noisyGradientY[i][j]; // Could also do this way
            pixVal = sqrt(pow(noisyGradientX[i][j],2)+pow(noisyGradientY[i][j],2));
      
            // Values already normalized by each gradient
            if(pixVal > 255)
                normVal = WHITE;
            else 
                normVal = (unsigned char)pixVal;

            // Use threshold value to produce a binary image (different then MRI)
           if(normVal >= THRESHOLD_CAKE)
	       noisyGradientImage[i][j] = WHITE;
           else if(normVal < THRESHOLD_CAKE)
	       noisyGradientImage[i][j] = BLACK;
        }  
    }

    // Write (added noise) binary edge image to file
    writeImage(noisyGradientImage, sizeX, sizeY, "noisyBinaryEdge_40_smooth.pgm");

    // Free all allocted memory
    freeArray(inputImage);
    freeArray(paddedImage);
    freeArray(gradientX);
    freeArray(gradientY);
    freeArray(paddedNoisyImage); 
    freeArray(noisyGradientY);
    freeArray(noisyGradientX);
    freeArray(noisyGradientImage);
 
    return 0;
}  

  
