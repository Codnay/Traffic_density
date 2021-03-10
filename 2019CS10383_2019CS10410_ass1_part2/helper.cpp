#include <stdio.h> 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

double density(Mat img1, Mat img2, int th){

	double nz = 0.0;
	for(int j=0; j<img1.rows; j++) {
        for(int i=0; i<img1.cols; i++){
            int pix = img1.at<uchar>(j,i);
            int pix1 = img2.at<uchar>(j,i);
            
            if(abs(pix1 - pix) > th){
                nz = nz + 1.0;
            }
        }
    }
	
	return(nz/(img1.rows * img1.cols));
}

Mat calc(Mat I){
	
	vector<Point2f> pts_src(4);

	pts_src[0] = Point2f(989,218);
	pts_src[1] = Point2f(522,980);
	pts_src[2] = Point2f(1542,990);
	pts_src[3] = Point2f(1270,214);

	vector<Point2f> pts_dst(4);
	pts_dst[0] = Point2f(472,52);
	pts_dst[1] = Point2f(472,830);
	pts_dst[2] = Point2f(800,830);
	pts_dst[3] = Point2f(800,52);

	Mat h = findHomography(pts_src, pts_dst);
	
	Mat Rin;
	Rin = Mat::zeros(I.rows, I.cols, I.type());
	warpPerspective(I,Rin,h,I.size());

	Mat ROI(Rin, Rect(472,52,328,778));
	Mat croppedImage;
	// Copy the data into new matrix
	ROI.copyTo(croppedImage);
	
	return croppedImage;
}

