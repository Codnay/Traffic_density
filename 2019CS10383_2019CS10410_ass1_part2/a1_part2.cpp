#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"
//#include <cuchar>

using namespace cv;
using namespace std;

/*vector<Point2f> pts_src(4);
int i = 0;
void click_event(int event, int x, int y, int flag, void *param)
{
	if(event == EVENT_LBUTTONDOWN || event == EVENT_RBUTTONDOWN || event == EVENT_MBUTTONDOWN)
	{	
		pts_src[i] = Point2f(x,y);
		i++;
	}
	return;
}*/	
int main(){
	Mat I = imread("empty.jpg", IMREAD_GRAYSCALE);
	Mat O = calc(I);
	//imshow("background", I);
	//waitKey(0);
	vector<double> queue_density;
	vector<double> dynamic_density;
	vector<int> frame_number;

	string InputImage;
	//cin >> InputImage;
	int video_start= 0;

	//fstream fout;
	//fout.open("output.txt");
	//fout << "Frame Number" << " " << "Queue density" << "\n";

	ofstream fout ("output.csv");
	fout << "framenum" << "," << "queue density" << "," << "dynamic density" <<"\n";

	VideoCapture cap("trafficvideo.mp4");
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		return -1;
	}

	Mat temp, temp1, temp2, temp3, temp4, temp5, temp6;
	temp = O;
	temp1 = O;
	temp2 = O;
	temp3 = O;
	temp4 = O;
	temp5 = O;
	temp6 = O;
	while(1){
		Mat frame, edges;
		cap >> edges;
		cvtColor(edges, frame, COLOR_BGR2GRAY);
		//imshow("Frame", frame);
		Mat out_frame;
		//imshow("Frame", frame);
		//waitKey(10);
		out_frame= calc(frame);
		//imshow("Frame", out_frame);
		//waitKey(200);

		frame_number.push_back(video_start+1);
		queue_density.push_back(density(out_frame, O, 25));
		dynamic_density.push_back(density(out_frame, temp, 25));

		temp = temp1;
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp4;
		temp4 = temp5;
		temp5 = temp6;
		temp6 = out_frame;
		
		
		/*if(video_start%3==0){
			Mat frame, edges;
			cap >> edges;
			cvtColor(edges, frame, COLOR_BGR2GRAY);
			//imshow("Frame", frame);
			Mat out_frame;
			//imshow("Frame", frame);
			//waitKey(10);
			out_frame= calc(frame);
			//imshow("Frame", out_frame);
			//waitKey(200);

			frame_number.push_back(video_start+1);
			queue_density.push_back(density(out_frame, O));

		}*/

		video_start= video_start+1;
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5715){
			break;
		}
		
	}
	cap.release();
	destroyAllWindows();

	cout << "framenum" << " " << "queue density" << "," << "dynamic density" <<"\n";

	for(int k = 0; k < frame_number.size(); k++){
		cout << frame_number[k] << "," << queue_density[k] << "," << dynamic_density[k] << "\n";
		fout << frame_number[k] << "," << queue_density[k] << "," << dynamic_density[k] << "\n";
	}

	fout.close();
	return 0;

	
	//for(int j = 0; j< 4; j++){
	//	setMouseCallback("InputImage", click_event);
	//}
	//waitKey(0);


	/*vector<Point2f> pts_dst(4);
	pts_dst[0] = Point2f(472,52);
	pts_dst[1] = Point2f(472,830);
	pts_dst[2] = Point2f(800,830);
	pts_dst[3] = Point2f(800,52);
	Mat h = findHomography(pts_src, pts_dst);
	
	Mat Rin;
	Rin = Mat::zeros(I.rows, I.cols, I.type());
	warpPerspective(I,Rin,h,I.size());
	imwrite("Transformed.jpg", Rin);
	imshow("Transformed",Rin);
	waitKey(0);
	Mat ROI(Rin, Rect(472,52,328,778));
	Mat croppedImage;
	// Copy the data into new matrix
	ROI.copyTo(croppedImage);
	imwrite("Final_cropped.jpg", croppedImage);
	imshow("Final_cropped",croppedImage);
	waitKey(0);*/
}
