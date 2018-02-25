//header of modules
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <stdlib.h>
#include <stdio.h>


// OpenCV uses cv namespace
using namespace cv;


//based on https://docs.opencv.org/3.2.0/da/d5c/tutorial_canny_detector.html
int main(int argc, char* argv[ ])
{
	Mat image = imread("lena.pgm"); //load image
	Mat output, edges;

    output.create( image.size(), image.type() );

    cvtColor( image, edges, COLOR_BGR2GRAY );
    namedWindow("Window");

	Canny(edges, edges, 48, 48*3, 3);
    output = Scalar::all(0);
    image.copyTo(output, edges);
	imshow("Window",output);

	//write images
	 imwrite( "lena_Canny.pgm", output );

	waitKey(0);
	return 0;
}
