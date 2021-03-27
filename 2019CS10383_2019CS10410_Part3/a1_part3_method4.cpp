#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"
#include <thread>

using namespace cv;
using namespace std;


//This code would not work because we are passing by value but some
//basic edits would fix this, would have to run and see



void imgcalc(int thread_count, int thread_num){
	

	Mat I = imread("empty.jpg", IMREAD_GRAYSCALE);
	Mat O = resize(calc(I));


	vector<double> queue_density;
	vector<int> frame_number;


	//Note that this is hard coded for now, to change this 
	//we will have to pass an extra string argument in imgcalc
	string InputVideo= "trafficvideo.mp4";

	int video_start= 0;

	ofstream fout ("out.txt");
	fout << "framenum" << "," << "queue density" <<"\n";

	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		return;
	}

	while(1){

		if(video_start%thread_count== thread_num){


		Mat frame,edges;
		cap >> edges;



		cvtColor(edges, frame, COLOR_BGR2GRAY);
		//imshow("Frame", frame);
		Mat out_frame;
		//imshow("Frame", frame);
		//waitKey(10);
		out_frame= resize(calc(frame));
		//imshow("Frame", out_frame);
		//waitKey(200);

		queue_density.push_back(density(out_frame, O, 25));

		

		frame_number.push_back(video_start+1);

		}


		iterator++;
		video_start= video_start+1;
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5722){
			break;
		}
		
	}
	cap.release();
	destroyAllWindows();

	cout << "time (in secs)" << ", " << "queue density" <<"\n";

	for(int k = 0; k < frame_number.size(); k++){
		//cout << frame_number[k]/15.0 << ", " << queue_density[k] << "\n";
		fout << frame_number[k] << "," << queue_density[k]  << "\n";
	}

	fout.close();

}

int main(){
	time_t start, end;
	time(&start);

	//Using 4 threads in our code
	int thread_tot= 4;
	vector<int> thread_count;

	for(int i=0 ; i< thread_tot; i++){
		thread_count.push_back(i);
	}

	thread t1(imgcalc, thread_tot, thread_count[0]);
	thread t2(imgcalc, thread_tot, thread_count[1]);
	thread t3(imgcalc, thread_tot, thread_count[2]);
	thread t4(imgcalc, thread_tot, thread_count[3]);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
}