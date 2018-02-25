//header of modules
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>


// OpenCV uses cv namespace
using namespace cv;


//based on https://docs.opencv.org/3.2.0/d2/d2c/tutorial_sobel_derivatives.html
int main(int argc, char* argv[ ])
{
	Mat image = imread("lena.pgm"); //load image
	Mat grad_x, grad_y, grad, src_gray, abs_grad_x, abs_grad_y;

    int ddepth = CV_16S;

    cvtColor( image, src_gray, COLOR_BGR2GRAY );

	Sobel( src_gray, grad_x, ddepth, 1, 0, 3 ,1,0, BORDER_DEFAULT);

	Sobel( src_gray, grad_y, ddepth,0, 1, 3,1,0,BORDER_DEFAULT);



    convertScaleAbs( grad_x, abs_grad_x );
      convertScaleAbs( grad_y, abs_grad_y );
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

	namedWindow("Window");
	imshow("Window",grad);

	//write images
	 imwrite( "lena_x.pgm", abs_grad_x );
	 imwrite( "lena_y.pgm", abs_grad_y );
	 imwrite( "lena_sobel.pgm", grad );
	waitKey(0);
	return 0;
}
