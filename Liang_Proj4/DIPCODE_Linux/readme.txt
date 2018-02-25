Yu Liang

Project 4
Fourier Transform and frequency filtering

*****
This software is architectured as follows. This software can work on grad server.


DIPCODE/OpenCV - OpenCV code, input image, output image



*** INSTALATION ***

On Linux


Enter the OpenCV directory in terminal and run:
g++ dft_low.cpp -o dft_low `pkg-config opencv --cflags --libs`
to compile dft_low 
 
g++ dft_high.cpp -o dft_high `pkg-config opencv --cflags --libs`
to compile dft_high 

g++ dft_band.cpp -o dft_band `pkg-config opencv --cflags --libs`
to compile dft_band 





*** FUNCTIONS ***

implement the following filters. (Not use the function from OpenCV) functions should operate within ROI (one is enough).

For each filter, you should have three output images:
1. the amplitude of the Fourier domain before filtering (no need to combine with the original image),
2. the amplitude of the Fourier domain after filtering (no need to combine with the original image),
3. the output result of the ROI combines with the original image.

Filters:

    Low-pass filter,
    High-pass filter,
    Band-stop filter,


ROI********************

**low or high:

60 60 100 100 40 50       # Parameters for ROI1: x, y, sx, sy, T, NULL

#need a space after 50#

**band:

60 60 100 100 10 40 50       # Parameters for ROI1: x, y, sx, sy, T_low, T_high, NULL

#need a space after 50#



*** Run the program: 

./dft_low

./dft_high

./dft_band






