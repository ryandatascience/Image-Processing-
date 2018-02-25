//header of modules
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodes/imgcodecs.hpp"

// OpenCV uses cv namespace
using namespace cv;

int main(int argc, char* argv[ ])
{
	Mat image = imread("lena.pgm");
	dft(image, image);
	namedWindow("Lena");
	imshow("Lena",image);
	waitKey(0);
	return 0;
}
