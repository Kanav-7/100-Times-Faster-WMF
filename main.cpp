#include "global.hpp"

int** int2D(int dim1, int dim2){
	int **ret = new int*[dim1];
	ret[0] = new int[dim1*dim2];
	for(int i=1;i<dim1;i++)
		ret[i] = ret[i-1]+dim2;
	return ret;
}

Mat req_filter(Mat &I, Mat &feature, int r)
{
	Mat F = feature.clone();
	int nI = 256,nF = 256, weightType = 1;
	I.convertTo(I,CV_32S);

	float **wMap;
	Mat FNew;

	int alls = F.cols * F.rows;
	int op;
	nF = 256;
	F.convertTo(FNew, CV_32S);

		float **ret = new float*[nF];
	ret[0] = new float[nF*nF];
	for(int i=1;i<nF;i++)
		ret[i] = ret[i-1]+nF;

	wMap =  ret;


	return F;

}

int main( int argc, char** argv ) {

	cv::Mat image,imagegray;
	image = imread("xy.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	imshow("Display window",req_filter(imagegray,imagegray,1));
	waitKey(0);
	return 0;
}