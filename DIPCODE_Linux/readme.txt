Yu Liang

Project 3 
Sobel Edge Detection and OpenCV

*****
This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.

OpenCV - OpenCV code, input image, output image



*** INSTALATION ***

On Linux

Sobel:

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

OpenCV:

Enter the OpenCV directory in terminal and run:
g++ Sobel.cpp -o Sobel `pkg-config opencv --cflags --libs`
to compile Sobel 
 
replace Sobel.cpp with Canny.cpp to compile Canny.
replace Sobel.cpp with EqualizeHis.cpp to compile Histogram Equalization.



*** FUNCTIONS ***

1. Sobel : Sobel33
Use the Sobel operator (3x3) to compute dx, dy, gradient amplitude and edge direction.
generate image of gradient amplitude as intensity image
generate binary edge image of thresholded gradient amplitude
generate binary edge image of thresholded gradient amplitude and direction


2. OpenCV : Sobel, Canny, EqualizeHis
Use the Sobel operator (3x3) in OpenCV
Use Canny module to do edge detection in OpenCV, lower threshold is 48
Implement histogram equalization using OpenCV (call the function)


ROI********************

Sobel:
50 150 100 200 50 45 
200 200 100 100 50 45      # Parameters for ROI1: x, y, sx, sy, T, TD

#need a space after 45#



*** PARAMETERS FILE ***

There are for parameters:
1. the input file name;
2. the output file name;
3. the name of the filter. Use "Sobel33"  for your filters;



*** Run the program: ./iptool parameters.txt


parameters.txt Example:

tree.pgm tree_amplitude.pgm Sobel33 50 
wheel.pgm wheel_amplitude.pgm Sobel33 50 



