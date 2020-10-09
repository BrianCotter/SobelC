/*
File:   readWrite.c
Author: Brian Cotter
Desc:   Purpose of this is file is to define functions to
read binary data from pgm files as well as write to 
new pgm files.
*/

#include "readWrite.h"
#include "array2D.h"


/* Function to read an image from a file */
unsigned char ** loadImage(unsigned int * sizeX, unsigned int * sizeY, char fname[]) {
    FILE * fp_in;         // File pointer
    unsigned char* image; // Array to store image
    unsigned char** image2D; 
    unsigned int levels;

    // Open input image
    fp_in = fopen(fname, "r");
    if(fp_in == NULL)
        fprintf(stderr, "Error opening: %s\n", fname); // Error handling
	
    // Read header info
    if(3 != fscanf(fp_in, "P5 %d %d %d ", sizeX, sizeY, &levels)) 
        fprintf(stderr, "Error reading image header values");
     
    // Dynamicaly allocate memory to store the image
    image = (unsigned char *)malloc((*sizeX)*(*sizeY));
    if(image == NULL)
        printf("Image memory allocation failed\n");

    // For now going to try to allocate in this same function
    image2D = (unsigned char **)malloc(*sizeX * sizeof(unsigned char *));
    for(int i = 0; i < *sizeX; i++)
      image2D[i] = (unsigned char *)malloc(*sizeY * sizeof(unsigned char));

    //Init as all 0's
    for(int i = 0; i < *sizeY; i++)
    {
	for(int j = 0; j < *sizeX; j++)
	  image2D[i][j] = 0;
    }
    
    // Read binary image data
    fread(image, sizeof(unsigned char), (*sizeX)*(*sizeY), fp_in);

    // Convert 1D array to 2D
    int i = 0;
    for(int x = 0; x < *sizeX; x++) {
        for(int y = 0; y < *sizeY; y++) {
	    //image2D[x][y] = image[i];
	    image2D[x][y] = image[i];
	    i++; 
	}
    }

    fclose(fp_in); // Close the file pointer
    free(image); // Dont need the 1D array anymore
    return image2D;  // return pointer to the image array
}


/* Function to write an image to a file */
void writeImage(unsigned char ** image, unsigned int sizeX, unsigned int sizeY, char fname[])
{
    FILE * fp_out;         // File pointer 
    unsigned levels = 255; // For now assuming levels = 255

    fp_out = fopen(fname, "w");
    if(fp_out == NULL) 
        fprintf(stderr, "Error opening: %s\n", fname);
	
    unsigned char * outputImage;
    outputImage = (unsigned char*)malloc(sizeX*sizeY*sizeof(unsigned char));
    int i = 0;
    for(int x = 0; x < sizeX; x++) {
        for(int y = 0; y < sizeY; y++) {
            outputImage[i] = image[x][y];
            i++;
        }
    }	


    fprintf(fp_out, "P5 %d %d %d ", sizeX, sizeY, levels);
    fwrite(outputImage, sizeof(unsigned char), sizeX*sizeY, fp_out);

    free(outputImage);
    fclose(fp_out); // Close the file pointer
}

