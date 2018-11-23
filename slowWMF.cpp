#include "global.hpp"
// #include ""

Mat slowwmf(Mat &I, Mat &F, int r)
{
	int nI = 256,nF = 256;
	I.convertTo(I,CV_32S);
	Mat out = I.clone();
	F.convertTo(F, CV_32S);
	Mat padded;
	int padding = 3;
	padded.create(I.rows + 2*padding, I.cols + 2*padding, I.type());
	padded.setTo(cv::Scalar::all(0));
	I.copyTo(padded(Rect(padding, padding, I.cols, I.rows)));
	for(int i=r;i<I.rows-r;i++)
	{
		for(int j=r;j<I.cols-r;j++)
		{
			vector<pair<int,float> > vc;
			for(int p=i-r;p<=i+r;p++)
			{
				for(int q=j-r;q<=j+r;q++)
				{
					float diff = abs((float)(I.at<int>(p,q) - I.at<int>(i,j)));
					float denom = (1.0f/(2*26*26));
					vc.push_back(make_pair(I.at<int>(p,q),1.0f));
				}
			}
			sort(vc.begin(),vc.end());
			float tot = 0,cur=0;
			int k=0;
			for(int ig=0;ig<vc.size();ig++)
				tot+=vc[ig].second;
			while(cur < 0.5*tot)
			{
				cur+=vc[k].second;
				k++;
			}
			out.ptr<int>(i-r,j-r)[0] = vc[k].first;
			vc.clear();
		}
	}
	out.convertTo(out,CV_8U);
	return out;
}