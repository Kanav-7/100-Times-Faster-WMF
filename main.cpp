#include "global.hpp"
#include "core.hpp"
#include "allocint.hpp"
#include "bcb.hpp"
#include "slowWMF.hpp"

Mat req_filter(Mat &I, Mat &F, int r)
{
	int nI = 256,nF = 256;
	I.convertTo(I,CV_32S);
	F.convertTo(F, CV_32S);

	float **wMap;
	int alls = I.cols * I.rows;
	int op = 1;
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

	cv::Mat image,imagegray,dst;
	
	image = imread("xy.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	Mat final;
	// for(double p=1;p<65;p+=2)
	// {
		// resize(imagegray, final ,Size(imagegray.cols * p,imagegray.rows * p),0,0,CV_INTER_LINEAR);
		clock_t t = clock();
		Mat tm = req_filter(imagegray,imagegray,p);
		t = clock() - t;
		double time_taken1 = ((double)t)/CLOCKS_PER_SEC;


		t = clock();
		Mat rest = slowwmf(imagegray,imagegray,p);
		t = clock() - t;
		double time_taken2 = ((double)t)/CLOCKS_PER_SEC;
		cout << time_taken1 << "," <<  time_taken2 << "," << p << endl;
	// }

	// ximgproc::weightedMedianFilter(imagegray, imagegray, dst, 1, 25.5, 1<<5, noArray());
	// imshow("Display window", tm);
	cout << "Done" << endl;
	waitKey(0);
	return 0;
}
