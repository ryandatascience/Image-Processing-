#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void histogram(image &src, image &tgt,image &hist1, image &hist12,image &hist2, image &hist22, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void binarize2(image &src, image &tgt, int threshold, int r, int g, int b);
		static void conversion(image &src, image &tgt,image &tgt1, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void Smooth2D(image &src, image &tgt);
		static void Smooth1D(image &src, image &tgt);
		static void EdgeSmooth(image &src, image &tgt, int tws);
};

#endif

