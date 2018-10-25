#include "global.hpp"

int** int2D(int dim1, int dim2){
	int **ret = new int*[dim1];
	ret[0] = new int[dim1*dim2];
	for(int i=1;i<dim1;i++)
		ret[i] = ret[i-1]+dim2;
	return ret;
}

Mat filterCore(Mat &I, Mat &F, float **wMap,int r)
{
	int nF=256,nI=256;
	Mat mask = Mat();
	int rows = I.rows, cols = I.cols;
	int alls = rows * cols;
	int winSize = (2*r+1)*(2*r+1);
	Mat outImg = I.clone();

	if(mask.empty()){
		mask = Mat(I.size(),CV_8U);
		mask = Scalar(1);
	}
}

Mat req_filter(Mat &I, int r)
{
	Mat feature = I.clone();
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
	for(int i=0;i<nF;i++){
		for(int j=i;j<nF;j++){
			float diff = fabs((float)(i-j));
			if(op==1)wMap[i][j] = wMap[j][i] = exp(-(diff*diff)*denom);
			else wMap[i][j] = wMap[j][i] = 1.0f;
		}
	}
	F = FNew;


	return F;

}

int main( int argc, char** argv ) {

	cv::Mat image,imagegray;
	image = imread("xy.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	imshow("Display window",req_filter(imagegray,1));
	waitKey(0);
	return 0;
}