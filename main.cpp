#include <cstdio>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {

	cv::Mat image,imagegray;
	Mat src = imread( "xy.png", 1 );
    Mat dst;

     //Apply median filter
    medianBlur ( src, dst, 15 );
    imshow("source", src);
    imshow("result", dst);  
	waitKey(0);
	return 0;
}
