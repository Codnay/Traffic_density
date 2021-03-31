#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "helper.cpp"

using namespace cv;
using namespace std;



int main(){


	//-----------Variable Declarations-------------

	Mat I, K, O;

	string InputVideo;
	cout << "Input video: ";
	cin >> InputVideo;

	vector<double> queue_density;
	vector<int> frame_number;

	int video_start= 0;

	int x;
	cout << "X: ";
	cin >> x;

	int y;
	cout << "Y: ";
	cin >> y;

	string out= "out_method2_" + to_string(x) + "_" + to_string(y) + ".txt";

	time_t start, end;




	//------------Starting the clock----------------

	time(&start);


	

	//-----------Starting the program----------------


	//Storing the baseline image after performing cropping ,homography and resizing
	I = imread("empty.jpg", IMREAD_GRAYSCALE);
	K= calc(I);
	resize(K, O, Size(x,y), 0, 0, INTER_NEAREST);

	//Opening the output file
	ofstream fout (out);
	fout << "framenum" << "," << "queue density" <<"\n";

	//Opening the input video
	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		return -1;
	}

	//Looping through all the frames in the input video
	while(1){


		Mat frame,edges;
		cap >> edges;

		cvtColor(edges, frame, COLOR_BGR2GRAY);
		Mat out_frame;

		Mat out;
		out= calc(frame);
		resize(out, out_frame, Size(x,y), 0, 0, INTER_NEAREST);

		queue_density.push_back(density(out_frame, O, 25));

		frame_number.push_back(video_start+1);

		video_start= video_start+1;

		//Ending the loop if we reach the end of the video or if user enters escape
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5722){
			break;
		}
		
	}

	//Closing the input video
	cap.release();
	destroyAllWindows();

	//Outputting the obtained values in the given output file
	for(int k = 0; k < frame_number.size(); k++){
		fout << frame_number[k] << "," << queue_density[k]  << "\n";
	}

	//Closing the output file
	fout.close();



	
	//---------------Ending the clock-------------------

	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;

	
}
