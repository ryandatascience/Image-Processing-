//header of modules
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

// OpenCV uses cv namespace
using namespace cv;

int main(int argc, char* argv[ ])
{
	Mat image = imread("lena.pgm");
	namedWindow("Lena");
	imshow("Lena",image);
	waitKey(0);
	return 0;
}
