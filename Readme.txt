File: ReadMe.txt
Author: Brian Cotter
 
-------------------------- Purpose --------------------------
Part 1: Read "cake.pgm" input image and perform Sobel edge detection.
Using spatial domain convolution. 

Part 2: Read "cake.pgm" input image and perform Sobel edge detection.
Here the performance of Sobel method is tested by follwoing
the same process as part 1 using an image with randomly added noise
to each pixel. This process is again repeated using an noisy input 
image with an avergaing filter applied (spatial convolution) 

-------------------------- Source Files --------------------
Main source code file: 
sobel.c
readWrite.c
convolve.c
array2d.c

Header files:
readWrite.h
convolve.h
array2d.h

------------------------- Instructions ---------------------
Part 1:
Note: File named "cake.pgm" must be in the same 
directory as source code files to read. 

Instructions to compile (all files):
$ make

This generates the sobel executable file, run with:
$./sobel

Passing "cake.pgm" argument tells the program you want to
run Part 1.

Output image files are added to the current directory;
"mriBinaryEdge.pgm"

This is the end of executation. To run part 2, the program
must be run again.
 
Part 2:
Note: File named "cake.pgm" must be in the same 
directory as source code files to read. 

By default noise level of 20 is used. this can be changed by changing the macro
#define MAX_NOISE 

