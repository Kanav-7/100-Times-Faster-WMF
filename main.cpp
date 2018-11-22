#include "global.hpp"
#include "core.hpp"
#include "allocint.hpp"
#include "bcb.hpp"

Mat req_filter(Mat &I, Mat &F, int r)
{
	int nI = 256,nF = 256;
	I.convertTo(I,CV_32S);
	F.convertTo(F, CV_32S);

	float **wMap;
	int alls = I.cols * I.rows;
	int op = 0;
	nF = 256;

	float **ret = new float*[nF];
	ret[0] = new float[nF*nF];
	for(int i=1;i<nF;i++)
		ret[i] = *ret + nF*i;

	wMap =  ret;

	float denom = (1.0f/(2*26*26));

	for(int i=0;i<nF;i++){
		for(int j=i;j<nF;j++){
			// cout << wMap[i][j] << endl;
			float diff = fabs((float)(i-j));
			if(op==1)
				wMap[i][j] = wMap[j][i] = exp(-(diff*diff)*denom);
			else if(op==2)
				wMap[i][j] = wMap[j][i] = (float)(min(i,j)*1.0/max(i,j));
			else 
				wMap[i][j] = wMap[j][i] = 1.0f;
		}
	}
	//Filtering - Joint-Histogram Framework
	I = filterCore(I,F,wMap, r);
	I.convertTo(I,CV_8U);
	return I;
}

int main( int argc, char** argv ) {

	cv::Mat image,imagegray;
	
	image = imread("xy.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	imshow("Display window", req_filter(imagegray,imagegray,1));
	waitKey(0);
	return 0;
}
