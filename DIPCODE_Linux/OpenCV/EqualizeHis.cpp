//header of modules

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>


// OpenCV uses cv namespace
using namespace cv;
using namespace std;


//based on https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_equalization/histogram_equalization.html
int main(int argc, char* argv[ ])
{
	Mat image = imread("slope.pgm"); //load image
	Mat output;



    cvtColor( image, image, COLOR_BGR2GRAY );
    equalizeHist( image, output );

    namedWindow("Window");


	imshow("Window",output);

	//write images
	 imwrite( "Slope_EquHis.pgm", output );

	waitKey(0);
	return 0;
}
