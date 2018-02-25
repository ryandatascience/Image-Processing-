Yu Liang

Project 2 
Histogram Modification and Color Processing

*****
This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

*** FUNCTIONS ***

1. Histogram Modification: hist
show the before and after histogram of ROIs
linear histogram stretching with input range (a,b) to (c,d)

2. Color Processing: conversion
histgram stretching in RGB.
Covert RGB to HSI and histgram stretching I channel and covert back to RGB



ROI********************

Hist:
100 300 100 100 5 100 200 0 255      # Parameters for ROI1: x, y, sx, sy, T/WS, a, b, c,d
200 200 50 100 4 100 200 0 255    # Parameters for ROI1: x, y, sx, sy, T/WS, a, b, c,d
#need a space after 255#

Conversion:
50 50 50 50 5 20 100 0 200  	# Parameters for ROI1: x, y, sx, sy, T/WS, a, b, c,d
100 100 50 50 4 20 100 0 200 	# Parameters for ROI1: x, y, sx, sy, T/WS, a, b, c,d
#need a space after 200#	

*** PARAMETERS FILE ***

There are for parameters:
1. the input file name;
2. the output file name;
3. the name of the filter. Use "hist" or "conversion" for your filters;
4. the value for adding intensity, threshold value for binarize filter, or the scaling factor for scale filter Or input, output range.


*** Run the program: ./iptool parameters.txt


parameters.txt Example:

slope.pgm slope_histogram.pgm hist 50
pen.ppm pen_conversion.ppm conversion 50


