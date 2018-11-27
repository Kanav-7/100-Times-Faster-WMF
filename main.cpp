#include "global.hpp"
#include "core.hpp"
#include "allocint.hpp"
#include "bcb.hpp"
#include "slowWMF.hpp"

// I = Input Image, F = Feature Map, r= Radius of Kernel
Mat req_filter(Mat &I, Mat &F, int r)
{
	int nI = 256,nF = 256;
	I.convertTo(I,CV_32S);
	F.convertTo(F, CV_32S);

	float **wMap;
	int alls = I.cols * I.rows;
	int op = 1;  //for type of weight (0: unweighted, 1: guassian, 2: Jacard)
	nF = 256;

	float **ret = new float*[nF];
	ret[0] = new float[nF*nF];
	for(int i=1;i<nF;i++)
		ret[i] = *ret + nF*i;

	wMap =  ret;

	float denom = (1.0f/(2*26*26));

	for(int i=0;i<nF;i++){
		for(int j=i;j<nF;j++){
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
	
	image = imread("input_images/x3.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	Mat final;
	// for(double p=2;p<5;p+=.2)
	// {
	int p =1;
		// resize(imagegray, final ,Size(imagegray.cols * p,imagegray.rows * p),0,0,CV_INTER_LINEAR);
		clock_t t = clock();
		Mat tm = req_filter(imagegray,imagegray,25);
		t = clock() - t;
		double time_taken1 = ((double)t)/CLOCKS_PER_SEC;
		imwrite( "output.jpeg", tm );
		cout << "Time Taken: " << time_taken1 << "s" << endl;


	// 	t = clock();
	// 	Mat rest = slowwmf(final,final,3);
	// 	t = clock() - t;
	// 	double time_taken2 = ((double)t)/CLOCKS_PER_SEC;
	// 	cout << time_taken1 << "," << time_taken2 << "," << p << endl;
	// }
	// output = medianBlur(final, 3);
	// ximgproc::weightedMedianFilter(imagegray, imagegray, dst, 1, 25.5, 1<<5, noArray());
	imshow("Display window", tm);
	cout << "Done" << endl;
	waitKey(0);
	return 0;
}
