#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"

using namespace cv;
using namespace std;

int main(){
	time_t start, end;
	time(&start);
	

	Mat I = imread("empty.jpg", IMREAD_GRAYSCALE);
	Mat O = calc(I);

	vector<double> queue_density;
	vector<double> dynamic_density;
	vector<int> frame_number;

	string InputVideo = "trafficvideo.mp4";
	//cin >> InputVideo;
	int video_start= 0;

	//ofstream fout ("out.txt");
	//fout << "framenum" << "," << "queue density" << "," << "dynamic density" <<"\n";

	VideoCapture cap(InputVideo);
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

	int x = 9;
	int iterator = 0;

	while(1){
		Mat frame,edges;
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
		
		if(iterator%x == 0){

			queue_density.push_back(density(out_frame, O, 25));

			Mat dst;
			bitwise_xor(temp, O, dst);        
			if(countNonZero(dst) > 0){
				dynamic_density.push_back(density(out_frame, temp, 25));
			}	
			else{
				dynamic_density.push_back(density(out_frame, out_frame, 25));
			}

		}else{
			queue_density.push_back(queue_density[iterator-1]);
			dynamic_density.push_back(dynamic_density[iterator-1]);
		}

		temp = temp1;
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp4;
		temp4 = temp5;
		temp5 = temp6;
		temp6 = out_frame;

		iterator++;
		video_start= video_start+1;
		char c= (char)waitKey(25);
		if(c==27 || video_start == 450){
			break;
		}
		
	}
	cap.release();
	destroyAllWindows();

	//cout << "time (in secs)" << ", " << "queue density" << ", " << "dynamic density" <<"\n";

	//for(int k = 0; k < frame_number.size(); k++){
	//	cout << frame_number[k]/15.0 << ", " << queue_density[k] << ", " << dynamic_density[k] << "\n";
	//	fout << frame_number[k] << "," << queue_density[k] << "," << dynamic_density[k] << "\n";
	//}

	//fout.close();

	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
	return 0;
}