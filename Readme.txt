File: ReadMe.txt
Author: Brian Cotter
Course: EECE4840
Desc: 
-------------------------- Purpose --------------------------
Part 1: Read "mri.pgm" input image and perform Sobel edge detection.
Using spatial domain convolution. 

Part 2: Read "cake.pgm" input image and perform Sobel edge detection.
Here the performance of Sobel method is tested by follwoing
the same process as part 1 using an image with randomly added noise
to each pixel. This process is again repeated using an noisy input 
image with an avergaing filter applied (spatial convolution) 

-------------------------- Source Files --------------------
Main source code file: 
lab3.c
readWrite.c
convolve.c
array2d.c

Header files:
readWrite.h
convolve.h
array2d.h

------------------------- Instructions ---------------------
Part 1:
Note: File named "mri.pgm" must be in the same 
directory as source code files to read. 

Instructions to compile (all files):
$ make

This generates the lab1 executable file, run with:
$./lab3 mri.pgm

Passing "mri.pgm" argument tells the program you want to
run Part 1.

Output image files are added to the current directory;
"mriBinaryEdge.pgm"

This is the end of executation. To run part 2, the program
must be run again.
 
Part 2:
Note: File named "cake.pgm" must be in the same 
directory as source code files to read. 

Run with:
$./lab2 cake.pgm 

Passing "mri.pgm" argument tells the program you want to
run Part 2. 

Output image files are added to the current directory;
"noisyBinaryEdge_20.pgm"

By default noise level of 20 is used. this can be changed by chnging the macro
#define MAX_NOISE 
on line _ of file lab3.c

Terminal output:
$./lab3 mri.pgm 
---- Part 1: Input image = mri.pgm ----

Note: File named "mri.pgm" must be in the same 
directory as source code files to read. 


Terminal Output:
$./lab3 cake.pgm 
---- Part 2: Input image = cake.pgm ----

Note: File named "mri.pgm" must be in the same 
directory as source code files to read. 
