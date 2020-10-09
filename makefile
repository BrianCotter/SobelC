all: sobel

sobel: sobel.o convolve.o readWrite.o array2D.o
	gcc -g -Wall -o sobel sobel.o convolve.o readWrite.o array2D.o -lm

convolve.o: convolve.c convolve.h
	gcc -g -Wall -c convolve.c

readWrite.o: readWrite.c readWrite.h
	gcc -g -Wall -c readWrite.c

array2D.o: array2D.c array2D.h
	gcc -g -Wall -c array2D.c

sobel.o: sobel.c convolve.h readWrite.h array2D.h
	gcc -g -Wall -c sobel.c

clean:
	rm *.o

