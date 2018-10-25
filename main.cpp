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
		int **H = int2D(nI,nF);
	int *BCB = new int[nF];

	int **Hf = int2D(nI,nF), **Hb = int2D(nI,nF);
	int *BCBf = new int[nF],*BCBb = new int[nF];

	for(int x=0;x<cols;x++){
		memset(BCB, 0, sizeof(int)*nF);
		memset(H[0], 0, sizeof(int)*nF*nI);
		for(int i=0;i<nI;i++)
			Hf[i][0]=Hb[i][0]=0;
		BCBf[0]=BCBb[0]=0;

		int medianVal = -1;
		int downX = max(0,x-r);
		int upX = min(cols-1,x+r);

		// Initialize joint-histogram
		int upY = min(rows-1,r);
		for(int i=0;i<=upY;i++){

			int *IPtr = I.ptr<int>(i);
			int *FPtr = F.ptr<int>(i);
			uchar *maskPtr = mask.ptr<uchar>(i);

			for(int j=downX;j<=upX;j++){

				if(!maskPtr[j])continue;

				int fval = IPtr[j];
				int *curHist = H[fval];
				int gval = FPtr[j];

				// necklace table
				if(!curHist[gval] && gval){
					int *curHf = Hf[fval];
					int *curHb = Hb[fval];

					int p1=0,p2=curHf[0];
					curHf[p1]=gval;
					curHf[gval]=p2;
					curHb[p2]=gval;
					curHb[gval]=p1;
				}

				curHist[gval]++;
				updateBCB(BCB[gval],BCBf,BCBb,gval,-1);
			}
		}
		for(int y=0;y<rows;y++)
		{
			{

				float balw = 0;
				int curIndex = F.ptr<int>(y,x)[0];
				float *fPtr = wMap[curIndex];
				int &cmedval = medianVal;
				int i=0;
				do{
					balw += BCB[i]*fPtr[i];
					i=BCBf[i];
				}while(i);

				if(balw >= 0){
					for(balw;balw >= 0 && cmedval;cmedval--){
						float curWeight = 0;
						int *nextHist = H[cmedval];
						int *nextHf = Hf[cmedval];

						int i=0;
						do{
							curWeight += (nextHist[i]<<1)*fPtr[i];
							
							updateBCB(BCB[i],BCBf,BCBb,i,-(nextHist[i]<<1));
							
							i=nextHf[i];
						}while(i);

						balw -= curWeight;
					}
				}
				else if(balw < 0){
					for(balw;balw < 0 && cmedval != nI-1; cmedval++){
						float curWeight = 0;
						int *nextHist = H[cmedval+1];
						int *nextHf = Hf[cmedval+1];

						int i=0;
						do{
							curWeight += (nextHist[i]<<1)*fPtr[i];

							updateBCB(BCB[i],BCBf,BCBb,i,nextHist[i]<<1);
							
							i=nextHf[i];
						}while(i);
						balw += curWeight;
					}
				}

				if(balw<0)outImg.ptr<int>(y,x)[0] = cmedval+1;
				else outImg.ptr<int>(y,x)[0] = cmedval;
			}
	return outImg;
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