#include <stdio.h> 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>


using namespace cv;
using namespace std;

vector<Point2f> pts_src(4);
int i = 0;

//idhar hard code krna padega
void click_event(int event, int x, int y, int flag, void *param)
{
	if(event == EVENT_LBUTTONDOWN || event == EVENT_RBUTTONDOWN || event == EVENT_MBUTTONDOWN)
	{	
		pts_src[i] = Point2f(x,y);
		i++;
	}
	return;
}	
Mat calc(Mat I){
	//string InputImage;
	//cin >> InputImage;
	//Mat I = imread(InputImage, IMREAD_GRAYSCALE);
	//imshow("InputImage", I);

	
	for(int j = 0; j< 4; j++){
		setMouseCallback("InputImage", click_event);
	}
	waitKey(0);


	vector<Point2f> pts_dst(4);
	pts_dst[0] = Point2f(472,52);
	pts_dst[1] = Point2f(472,830);
	pts_dst[2] = Point2f(800,830);
	pts_dst[3] = Point2f(800,52);

	Mat h = findHomography(pts_src, pts_dst);
	
	Mat Rin;
	Rin = Mat::zeros(I.rows, I.cols, I.type());
	warpPerspective(I,Rin,h,I.size());
	//imwrite("Transformed.jpg", Rin);
	//imshow("Transformed",Rin);
	//waitKey(0);

	Mat ROI(Rin, Rect(472,52,328,778));
	Mat croppedImage;
	// Copy the data into new matrix
	ROI.copyTo(croppedImage);
	//imwrite("Final_cropped.jpg", croppedImage);
	//imshow("Final_cropped",croppedImage);
	//waitKey(0);
	return croppedImage;
}

int main(){
	//not sure iska kya krunga huehue
}
