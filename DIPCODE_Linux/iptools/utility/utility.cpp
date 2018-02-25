#include "utility.h"
#include <strings.h>
#include <string.h>
#include <math.h>  

#define MAXRGB 255
#define MINRGB 0
#define MAX_LEN 256
std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::Sobel33(image &src,image &tgt,image &tgt1,image &tgt2)
{
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char *theta;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgt1.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgt2.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	int rows = src.getNumberOfRows();
	int columns = src.getNumberOfColumns();
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			tgt1.setPixel(i,j,checkValue(src.getPixel(i,j)));
			tgt2.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}
	int maskx[3][3] = {-1,0,1,-2,0,2,-1,0,1}, masky[3][3] = {-1,-2,-1,0,0,0,1,2,1};
    while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
		theta = strtok(NULL, " ");
		//t = strtok(NULL, " ");
	
        for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        {
            for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            {
                if(i-1<0||i+1>=rows||j-1<0||j+1>=columns) 
			{
				tgt.setPixel(i, j, 0);
			}
		else
		{
		  int sumx=0, sumy=0;
		  for(int mx = 0; mx < 3; mx++) 
		   {
			 for(int my = 0; my < 3; my++) 
			  {
				int value = src.getPixel(i+mx-1,j+my-1);
				sumx+=value*maskx[mx][my];
				sumy+=value*masky[mx][my];
			  }
		   }
		  sumx=sumx/8; sumy=sumy/8;
		  int gradient= sqrt(sumx*sumx+sumy*sumy);
		  double theta_c = atan((float)sumy/(float)sumx)*180/M_PI;
		  if(theta_c>atoi(theta)+10 || theta_c<atoi(theta)-10) {
				tgt2.setPixel(i, j, 0);
			} else {
				if(atoi(t)<gradient)
		    		{ tgt2.setPixel(i,j,255);}
		  		else {tgt2.setPixel(i,j,0);}
			}
		  tgt.setPixel(i,j,gradient);
		  if(atoi(t)<gradient)
		    { tgt1.setPixel(i,j,255);}
		  else {tgt1.setPixel(i,j,0);}
		}
            }
        }


	}
	
	
	
}









void utility::conversion(image &src, image &tgt, image &tgt1, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgt1.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char *a,*bb,*c,*d;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	//tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			tgt.setPixel(i,j,BLUE,checkValue(src.getPixel(i,j,BLUE)));
			tgt.setPixel(i,j,GREEN,checkValue(src.getPixel(i,j,GREEN)));
			tgt1.setPixel(i,j,RED,checkValue(src.getPixel(i,j,RED)));
			tgt1.setPixel(i,j,BLUE,checkValue(src.getPixel(i,j,BLUE)));
			tgt1.setPixel(i,j,GREEN,checkValue(src.getPixel(i,j,GREEN)));
		}
    while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);
		y = strtok(NULL, " ");
		//strcpy(outfile, pch);
		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
		a = strtok(NULL, " ");
		bb = strtok(NULL, " ");
		c = strtok(NULL, " ");
		d = strtok(NULL, " ");
		float pi=3.14159265358979323846;	
		
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
	    	    {
	            	for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
	           	 {
	             
			int RR, GG, BB;


		//Histogram streching rgb on (a,b) to (c,d);
			
				if(tgt1.getPixel(i, j, RED)<=atoi(bb) && tgt1.getPixel(i, j, RED)>=atoi(a))
				{
					 RR =(atoi(d)-atoi(c))/(atoi(bb)-atoi(a))*(tgt1.getPixel(i, j, RED)-atoi(a))+atoi(c);
					//printf("RR:%d",RR);
				}
				
			
				if(tgt1.getPixel(i, j, GREEN)<=atoi(bb) && tgt1.getPixel(i, j, GREEN)>=atoi(a))
				{
					 GG =(atoi(d)-atoi(c))/(atoi(bb)-atoi(a))*(tgt1.getPixel(i, j, GREEN)-atoi(a))+atoi(c);
					//printf("GG:%d",GG);
				}				
				if(tgt1.getPixel(i, j, BLUE)<=atoi(bb) && tgt1.getPixel(i, j, BLUE)>=atoi(a))
				{
					 BB =(atoi(d)-atoi(c))/(atoi(bb)-atoi(a))*(tgt1.getPixel(i, j, BLUE)-atoi(a))+atoi(c);
				}			 
			
			tgt1.setPixel(i, j, RED, RR);
			tgt1.setPixel(i, j, GREEN, GG);
			tgt1.setPixel(i, j, BLUE, BB);
	                 }
	            }	
		

		// hsi i convertion



		for (int ii=atoi(x); ii<atoi(x)+atoi(sx); ii++)
	    	    {
	            	for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
	           	 {
	             	float R =  tgt.getPixel(ii, j, RED);
			float G =  tgt.getPixel(ii, j, GREEN);
			float B =  tgt.getPixel(ii, j, BLUE);
			float r,g,b;	
			float H, S, I,h,s, i,num, den, theta;
			
			I= (R+G+B)/3;
			r= R/(R+G+B);
			g= G/(R+G+B);
			b= B/(R+G+B);
			//printf("I is ok");
			if (R==B && R==G) 
				{H=0;
				S=0;
				}
			else {
			num = 0.5*(r-g+r-b);
			den = sqrt((r-g)*(r-g)+(r-b)*(g-b));
			h=acos(num/den);
			if (B>G) { h= 2*pi-h;}
			//printf("H is ok");
			H=h*180/pi;
			 S=(1-3*min(min(r,g),b))*100;
			
				}
	//convert HSI to hsi			
			i=I/255;
			s=S/100;
			h=H*pi/180;

//Histogram streching I on (a,b) to (c,d);
			
				if(i<=atoi(bb) && i>=atoi(a))
				{
					i=(atoi(d)-atoi(c))/(atoi(bb)-atoi(a))*(i-atoi(a))+atoi(c);
				}
			 
	//convert HSI back to RGB
			float xx=i*(1-s);
			
			if (h<2*pi/3)
			{
			float yy=i*(1+(s*cos(h))/cos(pi/3-h));
			float z=3*i-(xx+yy);
			r=yy;
			g=z;
			b=xx;
			}
			else if (h<4*pi/3)
			{
			float yy=i*(1+(s*cos(h-2*pi/3))/cos(pi/3-(h-2*pi/3)));
			float z=3*i-(xx+yy);
			r=yy;
			g=z;
			b=xx;
			}			
			else 
			{
			float yy=i*(1+(s*cos(h-4*pi/3))/cos(pi/3-(h-4*pi/3)));
			float z=3*i-(xx+yy);
			r=yy;
			g=z;
			b=xx;
			}
		//convert rgb to RGB
			//R=r*255;
			//G=g*255;
			//B=b*255;
			
			tgt.setPixel(ii, j, RED, r*255);
			tgt.setPixel(ii, j, GREEN, g*255);
			tgt.setPixel(ii, j, BLUE, b*255);
	                 }
	            }	
	}
	//fclose(fp1);
}


void utility::histogram(image &src, image &tgt,image &hist1, image &hist12,image &hist2, image &hist22, int value)
{

	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char *a,*b,*c,*d;
	char str1[MAX_LEN];
	int count[255];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	hist1.resize(src.getNumberOfRows()-src.getNumberOfRows()+256, src.getNumberOfColumns()-src.getNumberOfColumns()+256);
	hist12.resize(src.getNumberOfRows()-src.getNumberOfRows()+256, src.getNumberOfColumns()-src.getNumberOfColumns()+256);
	hist2.resize(src.getNumberOfRows()-src.getNumberOfRows()+256, src.getNumberOfColumns()-src.getNumberOfColumns()+256);
	hist22.resize(src.getNumberOfRows()-src.getNumberOfRows()+256, src.getNumberOfColumns()-src.getNumberOfColumns()+256);
	for (int i=0; i<src.getNumberOfRows(); i++)
		{for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}}
	
	int time=0;
    while(fgets(str1,MAX_LEN,fp1) != NULL) {
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
		a = strtok(NULL, " ");
		b = strtok(NULL, " ");
		c = strtok(NULL, " ");
		d = strtok(NULL, " ");
		

	for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        {
            for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            {
		if(src.getPixel(i,j)<=atoi(b)&&src.getPixel(i,j)>=atoi(a))
		{
                	tgt.setPixel(i,j,checkValue((src.getPixel(i,j)-atoi(a))*(atoi(d)-atoi(c))/(atoi(b)-atoi(a))));
		}
            }
        }
	if(time==0)
	{
		//printf("histogram is ok\n");
		for(int i=0;i<255;i++)
		{
		   count[i]=0;
		}
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        	{
            		for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            		{
			 count[src.getPixel(i,j)]++;            
            		}
        	}
		int temp=0;
		for(int i=0;i<255;i++)
		{
		   if(temp<count[i])
		   {temp=count[i];}
		   
		}
		//printf("temp is %d %d",temp,temp);
		//int width=1;
		//float height=256/temp;
		for(int i=0;i<256;i++)
		{
			//printf("first loop is ok");
			for(int j=256-256*count[i]/temp; j<256;j++)
			{
				//printf("i:%d,j:%d\n",i,j);
			   hist1.setPixel(j,i,255);
			}
		}
		
		// modified histogram
		for(int i=0;i<255;i++)
		{
		   count[i]=0;
		}
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        	{
            		for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            		{
			 count[tgt.getPixel(i,j)]++;            
            		}
        	}
		int temp1=0;
		for(int i=0;i<255;i++)
		{
		   if(temp1<count[i])
		   {temp1=count[i];}
		   
		}
		//printf("temp is %d %d",temp,temp);
		int width=1;
		//float height=256/temp;
		for(int i=0;i<256;i++)
		{
			//printf("first loop is ok");
			for(int j=256-256*count[i]/temp1; j<256;j++)
			{
				//printf("i:%d,j:%d\n",i,j);
			   hist12.setPixel(j,i,255);
			}
		}
		

		


	}
	if(time==1)
	{
		//printf("histogram is ok\n");
		for(int i=0;i<255;i++)
		{
		   count[i]=0;
		}
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        	{
            		for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            		{
			 count[src.getPixel(i,j)]++;            
            		}
        	}
		int temp=0;
		for(int i=0;i<255;i++)
		{
		   if(temp<count[i])
		   {temp=count[i];}
		   
		}
		//printf("temp is %d %d",temp,temp);
		//int width=1;
		//float height=256/temp;
		for(int i=0;i<256;i++)
		{
			//printf("first loop is ok");
			for(int j=256-256*count[i]/temp; j<256;j++)
			{
				//printf("i:%d,j:%d\n",i,j);
			   hist2.setPixel(j,i,255);
			}
		}
		
		// modified histogram
		for(int i=0;i<255;i++)
		{
		   count[i]=0;
		}
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        	{
            		for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            		{
			 count[tgt.getPixel(i,j)]++;            
            		}
        	}
		int temp1=0;
		for(int i=0;i<255;i++)
		{
		   if(temp1<count[i])
		   {temp1=count[i];}
		   
		}
		//printf("temp is %d %d",temp,temp);
		int width=1;
		//float height=256/temp;
		for(int i=0;i<256;i++)
		{
			//printf("first loop is ok");
			for(int j=256-256*count[i]/temp1; j<256;j++)
			{
				//printf("i:%d,j:%d\n",i,j);
			   hist22.setPixel(j,i,255);
			}
		}
		

		


	}
	time++;


}
}





void utility::addGrey(image &src, image &tgt, int value)
{

	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}
    while(fgets(str1,MAX_LEN,fp1) != NULL) {
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
	
        for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
        {
            for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
            {
                tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value));
            }
        }
}}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			tgt.setPixel(i,j,BLUE,checkValue(src.getPixel(i,j,BLUE)));
			tgt.setPixel(i,j,GREEN,checkValue(src.getPixel(i,j,GREEN)));
		}
	printf("row number:%d\n",src.getNumberOfRows());
	printf("columns number:%d\n", src.getNumberOfColumns());
    while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
			
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
	    	    {
	            	for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
	           	 {
	             	   	if (src.getPixel(i,j) < threshold)
					tgt.setPixel(i,j,MINRGB);
				else
					tgt.setPixel(i,j,MAXRGB);
	                 }
	            }	
	}
}

void utility::binarize2(image &src, image &tgt, int threshold, int r, int g, int b)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	//tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			tgt.setPixel(i,j,BLUE,checkValue(src.getPixel(i,j,BLUE)));
			tgt.setPixel(i,j,GREEN,checkValue(src.getPixel(i,j,GREEN)));
		}
    while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);
		y = strtok(NULL, " ");
		//strcpy(outfile, pch);
		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
			
		for (int i=atoi(x); i<atoi(x)+atoi(sx); i++)
	    	    {
	            	for (int j=atoi(y); j<atoi(y)+atoi(sy); j++)
	           	 {
	             	int cr = r - tgt.getPixel(i, j, RED);
			int cg = g - tgt.getPixel(i, j, GREEN);
			int cb = b - tgt.getPixel(i, j, BLUE);
			int distance = cr * cr + cg * cg + cb * cb;
			int value = 0; 
			if(distance < threshold*threshold) { 
				 value = 255; 
			}
			tgt.setPixel(i, j, RED, value);
			tgt.setPixel(i, j, GREEN, value);
			tgt.setPixel(i, j, BLUE, value);
	                 }
	            }	
	}
	//fclose(fp1);
}


void utility::Smooth2D(image &src, image &tgt)
{
	
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL)
	 {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}
	}//printf("ok");
    	while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
//	printf("ok");
		int rows = src.getNumberOfRows();
		int columns = src.getNumberOfColumns();
		int h = (atoi(t) - 1)/2;
	for(int x0 = atoi(x); x0 < atoi(x) + atoi(sx); x0++) 
		{
			for(int y0 = atoi(y); y0 < atoi(y) + atoi(sy); y0++) 
			{
				int x1 = x0-h, x2 = x0+h, y1 = y0 - h, y2 = y0 + h;
				if(x1 < 0 || y1 <0 || x2 >= rows || y2 >= columns) continue;
				int value = 0;
				for(int i = x1; i <= x2; i++) 
				{
					for(int j = y1; j <= y2; j++) 
					{
						value += src.getPixel(i, j);
					}
				}
			
				value = value/(atoi(t)*atoi(t));
				tgt.setPixel(x0,y0,value);
			}
		}
	}
}


void utility::Smooth1D(image &src, image &tgt)
{
	
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL)
	 {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}
	}//printf("ok");
    	while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
		int h = (atoi(t) - 1)/2;
		for(int x0 = atoi(x); x0 < atoi(x) + atoi(sx); x0++) 
		{
			for(int y0 = atoi(y); y0 < atoi(y) + atoi(sy); y0++) 
			{			
				int x1 = x0-h, x2 = x0+h;
				if(x1 < 0 || x2 >= src.getNumberOfRows()) continue;
				int value = 0;
				for(int i = x1; i <= x2; i++) 
				{
					value += src.getPixel(i, y0);
				}
			
			value = value/atoi(t);
			tgt.setPixel(x0,y0,value);
			}		
		}
	}
}


void utility::EdgeSmooth(image &src, image &tgt, int tws)
{
	
	FILE *fp1;
	char *x;
	char *y;
	char *sx;
	char *sy;
	char *t;
	char str1[MAX_LEN];
	if ((fp1 = fopen("ROI.txt","r")) == NULL)
	 {
		fprintf(stderr, "Can't open file: %s\n", "ROI.txt");
		exit(1);
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
		}
	}//printf("ok");
    	while(fgets(str1,MAX_LEN,fp1) != NULL) 
	{
		x = strtok(str1, " ");
		//src.read(pch);

		y = strtok(NULL, " ");
		//strcpy(outfile, pch);

		sx = strtok(NULL, " ");
		sy = strtok(NULL, " ");
		t = strtok(NULL, " ");
//	printf("ok");
		int rows = src.getNumberOfRows();
		int columns = src.getNumberOfColumns();
		int h = (atoi(t) - 1)/2;
	for(int x0 = atoi(x); x0 < atoi(x) + atoi(sx); x0++) 
		{
			for(int y0 = atoi(y); y0 < atoi(y) + atoi(sy); y0++) 
			{
				int x1 = x0-h, x2 = x0+h, y1 = y0 - h, y2 = y0 + h;
				if(x1 < 0 || y1 <0 || x2 >= rows || y2 >= columns) continue;
				int value = 0;
				for(int i = x1; i <= x2; i++) 
				{
					for(int j = y1; j <= y2; j++) 
					{
						value += src.getPixel(i, j);
					}
				}
			
				value = value/(atoi(t)*atoi(t));
				if(abs(src.getPixel(x0,y0)-value)<tws)
					{
						tgt.setPixel(x0,y0,value);
					}
				else
					continue;
			}
		}
	}
}



/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}



