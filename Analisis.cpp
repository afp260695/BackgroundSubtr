#include <string>
#include <cv.h>
#include <highgui.h>
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
	if(argc==2){
	string imageName = argv[1];
	Mat img = imread(imageName,1);
	cvtColor(img,img,CV_BGR2HSV);
	imshow("Background",img);
	waitKey(0);
	} else
	if(argc==3){
	Mat back = imread (argv[1],1);
	Mat img = imread (argv[2],1);
	cvtColor(back,back,CV_BGR2HSV);
	cvtColor(img,img,CV_BGR2HSV);
	int cols = back.cols;
	int rows = back.rows;
	
	for(int y=0;y<rows;y++)
		for(int x=0;x<cols;x++){
		img.at<Vec3b>(y,x)[0]=abs(img.at<Vec3b>(y,x)[0]-back.at<Vec3b>(y,x)[0]);
		img.at<Vec3b>(y,x)[1]=abs(img.at<Vec3b>(y,x)[1]-back.at<Vec3b>(y,x)[1]);
		img.at<Vec3b>(y,x)[2]=abs(img.at<Vec3b>(y,x)[2]-back.at<Vec3b>(y,x)[2]);
		}
		
	imshow("Tikus",img);
	waitKey(0);
	}
	return 0;
}