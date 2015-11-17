#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
using namespace cv;

typedef pair<int,int> ii;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};


void CallBackFunc(int event, int x,int y, int flags, void* userdata);

Mat img;

int HSV[6];
int xmin=99999; 
int xmax=0;
int ymin=99999; 
int ymax=0;

int main(int argc, char* argv[]){
	VideoCapture cap;
	cap.open(argv[1]);
	Mat frame;
	string Nama;
	char* temp;
	bool bSuccess;
	int i=65;
	bool terus=true;
	while(terus){
	bSuccess = cap.read(frame);
	if(!bSuccess){
		cout<<"Habis";
		break;
	}
	
	imshow("Window",frame);
	if(waitKey(33)==' '){
		Nama = Nama + argv[1];
		Nama = Nama + ".jpg";
		img=frame.clone();
		imwrite(Nama,frame);
		i++;
		terus=false;
		}	
	
	}
	
	imshow("image",img);
	setMouseCallback("image",CallBackFunc,NULL);
	waitKey(0);
	return 0;
}

void CallBackFunc(int event, int x,int y, int flags, void* userdata){
	if(event==EVENT_LBUTTONDOWN){
		Mat image = img.clone();
		cvtColor(image,image,CV_BGR2HSV);
			HSV[0]=image.at<Vec3b>(y,x)[0]-30;
			HSV[3]=image.at<Vec3b>(y,x)[0]+30;
			HSV[1]=image.at<Vec3b>(y,x)[1]-30;
			HSV[4]=image.at<Vec3b>(y,x)[1]+30;
			HSV[2]=image.at<Vec3b>(y,x)[2]-8;
			HSV[5]=image.at<Vec3b>(y,x)[2]+8;
		for(int i=0;i<3;i++){
		
			if(HSV[i]<0) HSV[i]=0;
			if(HSV[3+i]>255) HSV[3+i]=255;
		}
		inRange(image,Scalar(HSV[0],HSV[1],HSV[2]),Scalar(HSV[3],HSV[4],HSV[5]),image);
		
			
		bool visit[image.rows+1][image.cols+1];
		memset(visit,false,sizeof(visit));
		

		
		uchar pl;
		
	
				pl = image.at<uchar>(y,x);
				if((pl>0)&&(!visit[y][x])){
					queue<ii> q;
					q.push(ii(y,x));
					visit[y][x]=true;
					
					
					while(!q.empty()){
						ii u = q.front(); q.pop();
						xmin = min(xmin,u.second);
						xmax = max(xmax,u.second);
						ymin = min(ymin,u.first);
						ymax = max(ymax,u.first);
						for(int k =0; k<4;++k){
							int ny = u.first+dy[k];
							int nx = u.second+dx[k];
							if((ny>=0) && (ny<=image.rows) && (nx>=0) && (nx<=image.cols) && (!visit[ny][nx])){
								uchar p = image.at<uchar>(ny,nx);								
								if(p > 0){
									
									q.push(ii(ny,nx));
									visit[ny][nx] = true;
								}
							}
							
						}
					
					}
		
				
				}
			
			
		
		if ((xmin < xmax) && (ymin < ymax))
			rectangle(img,Point(xmin,ymin),Point(xmax,ymax),Scalar(0,255,0),4,8,0);
		cout<<xmin<<" "<<ymin<<endl;
		cout<<xmax<<" "<<ymax<<endl;
		imshow("image",img);
		imshow("Hasil",image);     
		
		
		waitKey(0);
	}
}