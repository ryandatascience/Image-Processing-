/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "../iptools/core.h"
#include <strings.h>
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt,tgt1, hist_ori, hist_modi,hist1_ori, hist1_modi;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		pch = strtok(str, " ");
		src.read(pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " ");
        if (strncasecmp(pch,"hist",MAXLEN)==0) {
			/* histogram */
			pch = strtok(NULL, " ");
        		utility::histogram(src,tgt,hist_ori, hist_modi,hist1_ori, hist1_modi,atoi(pch));
			hist_ori.save("hist1_original.pgm");
			hist_modi.save("hist1_modified.pgm");
			hist1_ori.save("hist2_original.pgm");
			hist1_modi.save("hist2_modified.pgm");
		//printf("hist is ok");        
	}

        else if (strncasecmp(pch,"binarize1",MAXLEN)==0) {
			/* Thresholding */
			pch = strtok(NULL, " ");
			//utility::binarize(src,tgt,atoi(pch));
		}
	
    	else if (strncasecmp(pch,"conversion",MAXLEN)==0) {
			/* Thresholding */
			int r,b,g;
			pch = strtok(NULL, " ");
			//char *p;
			//p=strtok(NULL, " ");
			
			//printf("function is not run");
			utility::conversion(src,tgt,tgt1,atoi(pch));
			tgt1.save("penconvert_rgb.ppm");
			
			//printf("function is ok");
		}
	else if (strncasecmp(pch,"smooth2",MAXLEN)==0) {
			
			printf("ok\n");
			//pch = strtok(NULL, " ");
			//utility::Smooth2D(src,tgt);
		}
		else if (strncasecmp(pch,"smooth1",MAXLEN)==0) {
			
			printf("ok\n");
			//pch = strtok(NULL, " ");
			//utility::Smooth1D(src,tgt);
		}


		else if (strncasecmp(pch,"scale",MAXLEN)==0) {
			/* Image scaling */
			pch = strtok(NULL, " ");
			//utility::scale(src,tgt,atof(pch));
		}
		else if (strncasecmp(pch,"edgesmooth",MAXLEN)==0) {
			
			printf("ok\n");
			pch = strtok(NULL, " ");
			//utility::EdgeSmooth(src,tgt,atoi(pch));
		}

		else {
			printf("No function: %s\n", pch);
			continue;
		}
       
		tgt.save(outfile);
	}
	fclose(fp);
	return 0;
}

