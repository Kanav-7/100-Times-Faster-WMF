#include "global.hpp"

int main( int argc, char** argv ) {

	cv::Mat image,imagegray;
	image = imread("xy.png" , CV_LOAD_IMAGE_COLOR);
	cvtColor(image,imagegray, CV_BGR2GRAY);
	imshow("Display window", req_filter(imagegray,imagegray,1));
	waitKey(0);
	return 0;
}