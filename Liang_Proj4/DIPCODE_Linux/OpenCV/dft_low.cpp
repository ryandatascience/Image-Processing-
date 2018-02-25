 #include "opencv2/core.hpp"
 #include "opencv2/imgproc.hpp"
 #include "opencv2/imgcodecs.hpp"
 #include "opencv2/highgui.hpp"
 #include "opencv2/opencv.hpp"
 #include <iostream>
 
 using namespace cv;
 using namespace std;
 #define MAX_LEN 256
 
 int main(int argc, char ** argv)
 {
	int count=0; 
	FILE *fp1;
	char *x, *x1;
	char *y, *y1;
	char *sx, *sx1;
	char *sy, *sy1;
	char *T, *T1;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		if(count==0)
		{
			x = strtok(str1, " ");
			//src.read(pch);

			y = strtok(NULL, " ");
			//strcpy(outfile, pch);

			sx = strtok(NULL, " ");
			sy = strtok(NULL, " ");
			T = strtok(NULL, "");
			printf("first is ok");
		}/*
		else
		{
			x1 = strtok(str1, " ");
			//src.read(pch);

			y1 = strtok(NULL, " ");
			//strcpy(outfile, pch);

			sx1 = strtok(NULL, " ");
			sy1 = strtok(NULL, " ");
			T1 = strtok(NULL, "");
			printf("second is ok");
		}*/
		//count++;
	}

		Mat I0 = imread("lena.pgm", IMREAD_GRAYSCALE);
		Mat I1=I0;
		Mat I(I0, Rect(atoi(y), atoi(x), atoi(sy), atoi(sx)));
		//Mat II(I1, Rect(atoi(y1), atoi(x1), atoi(sy1), atoi(sx1)));
	 	//int T=50;
	   //  Mat padded;                            //expand input image to optimal size
	  //   int m = getOptimalDFTSize( I0.rows );
	  //   int n = getOptimalDFTSize( I0.cols ); // on the border add zero values
	  //   copyMakeBorder(I0, padded, 0, m - I0.rows, 0, n - I0.cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = {Mat_<float>(I), Mat::zeros(I.size(), CV_32F)};
		//Mat planes1[] = {Mat_<float>(II), Mat::zeros(II.size(), CV_32F)};
		Mat complexI;
		//Mat complexII;
		merge(planes, 2, complexI);  
		//merge(planes1, 2, complexII);       // Add to the expanded another plane with zeros
		dft(complexI, complexI);  
		//dft(complexII, complexII);          // this way the result may fit in the source matrix
	     // compute the magnitude and switch to logarithmic scale
	     // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
		split(complexI, planes); 
		//split(complexII, planes1);                  // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes[0], planes[1], planes[0]);
		//magnitude(planes1[0], planes1[1], planes1[0]);// planes[0] = magnitude
		Mat magI = planes[0];
		//Mat magI1 = planes1[0];
		magI += Scalar::all(1);  
		//magI1 += Scalar::all(1);                   // switch to logarithmic scale
		log(magI, magI);
		//log(magI1, magI1);
	     // crop the spectrum, if it has an odd number of rows or columns
		magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
		//magI1 = magI1(Rect(0, 0, magI1.cols & -2, magI1.rows & -2));
	     // rearrange the quadrants of Fourier image  so that the origin is at the image center
		int cx = magI.cols/2;
		int cy = magI.rows/2;
	 //	int cx1 = magI1.cols/2;
		//int cy1 = magI1.rows/2;
		Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
		Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
		Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
		Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
/*
		Mat q01(magI1, Rect(0, 0, cx1, cy1));   // Top-Left - Create a ROI per quadrant
		Mat q11(magI1, Rect(cx1, 0, cx1, cy1));  // Top-Right
		Mat q21(magI1, Rect(0, cy1, cx1, cy1));  // Bottom-Left
		Mat q31(magI1, Rect(cx1, cy1, cx1, cy1)); // Bottom-Right
	*/ 
		Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);
	  
		q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
		q2.copyTo(q1);
		tmp.copyTo(q2);
	/*  
		Mat tmp1;                           // swap quadrants (Top-Left with Bottom-Right)
		q01.copyTo(tmp1);
		q31.copyTo(q01);
		tmp1.copyTo(q31);
	  
		q11.copyTo(tmp1);                    // swap quadrant (Top-Right with Bottom-Left)
		q21.copyTo(q11);
		tmp1.copyTo(q21);*/
		normalize(magI, magI, 0, 1, NORM_MINMAX);
		//normalize(magI1, magI1, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
		                                     // viewable image form (float between values 0 and 1).
	 
	   //  imshow("Input Image"       , I0   );    // Show the result
		imshow("before_filter_dft", magI);
		//imshow("before_filter_dft1", magI1);


	// Low pass filter
		split(complexI, planes);
		//split(complexII, planes1);                      // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		int rows = planes[0].rows, cols = planes[0].cols;
		//int rows1 = planes1[0].rows, cols1 = planes1[0].cols;
		cy = cols/2;
		cx = rows/2;
		//cy1 = cols1/2;
		//cx1 = rows1/2;
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				int gx = i, gy = j; 
				if(i >= cx) gx = rows - i;
				if(j >= cy) gy = cols - j;
				int gd = (int)sqrt((float)(gx * gx)+(float)(gy * gy));
				if(gd > atoi(T)) {
					planes[0].at<float>(i, j) = 0;
					planes[1].at<float>(i, j) = 0;
				}
			}
		}
/*
		for(int i = 0; i < rows1; i++) {
			for(int j = 0; j < cols1; j++) {
				int gx1 = i, gy1 = j; 
				if(i >= cx1) gx1 = rows1 - i;
				if(j >= cy1) gy1 = cols1 - j;
				int gd1 = (int)sqrt((float)(gx1 * gx1)+(float)(gy1 * gy1));
				if(gd1 > atoi(T1)) {
					planes1[0].at<float>(i, j) = 0;
					planes1[1].at<float>(i, j) = 0;
				}
			}
		}
*/
	        magnitude(planes[0], planes[1], planes[0]);
	//	magnitude(planes1[0], planes1[1], planes1[0]);// planes[0] = magnitude
	        Mat magII = planes[0];
		//Mat magII1 = planes1[0];
	        magII += Scalar::all(1);
	//	magII1 += Scalar::all(1);                     // switch to logarithmic scale
	        log(magII, magII);
	//	log(magII1, magII1);
	     // crop the spectrum, if it has an odd number of rows or columns
	        magII = magII(Rect(0, 0, magII.cols & -2, magII.rows & -2));
	//	magII1 = magII1(Rect(0, 0, magII1.cols & -2, magII1.rows & -2));
	     // rearrange the quadrants of Fourier image  so that the origin is at the image center
	        cx = magII.cols/2;
	       cy = magII.rows/2;
		//cx1 = magII1.cols/2;
	   //     cy1 = magII1.rows/2;
	  
	       Mat q4(magII, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	       Mat q5(magII, Rect(cx, 0, cx, cy));  // Top-Right
	       Mat q6(magII, Rect(0, cy, cx, cy));  // Bottom-Left
	       Mat q7(magII, Rect(cx, cy, cx, cy)); // Bottom-Right
/*
	 	Mat q41(magII1, Rect(0, 0, cx1, cy1));   // Top-Left - Create a ROI per quadrant
	       Mat q51(magII1, Rect(cx1, 0, cx1, cy1));  // Top-Right
	       Mat q61(magII1, Rect(0, cy1, cx1, cy1));  // Bottom-Left
	       Mat q71(magII1, Rect(cx1, cy1, cx1, cy1)); // Bottom-Right
	*/	                       // swap quadrants (Top-Left with Bottom-Right)
	       q4.copyTo(tmp);
	       q7.copyTo(q4);
	       tmp.copyTo(q7);
	 /*
	       q41.copyTo(tmp1);
	       q71.copyTo(q41);
	       tmp1.copyTo(q71);
*/
	       q5.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	       q6.copyTo(q5);
	       tmp.copyTo(q6);
	 /*
	       q51.copyTo(tmp1);                    // swap quadrant (Top-Right with Bottom-Left)
	       q61.copyTo(q51);
	       tmp1.copyTo(q61);*/
	       normalize(magII, magII, 0, 1, NORM_MINMAX); 
	      // normalize(magII1, magII1, 0, 1, NORM_MINMAX);// Transform the matrix with float values into a
		                                     // viewable image form (float between values 0 and 1).
	       imshow("after_filter_dft", magII);
	      // imshow("after_filter_dft1", magII1);
	       merge(planes, 2, complexI);
	      // merge(planes1, 2, complexII);
	       dft(complexI, I,DFT_INVERSE+DFT_REAL_OUTPUT);
	     //  dft(complexII, II,DFT_INVERSE+DFT_REAL_OUTPUT);	// Inverse DFT
	       normalize(I, I, 0, 255, CV_MINMAX);
	     //  normalize(II, II, 0, 255, CV_MINMAX);
	
	       I.copyTo(I0(Rect(atoi(y), atoi(x), atoi(sy), atoi(sx))));
	 //      II.copyTo(I0(Rect(atoi(y1), atoi(x1), atoi(sx1), atoi(sy1))));
	       imshow("after_filter_pgm", I0);
	       waitKey(); 
 
	
       return 0;
 }
