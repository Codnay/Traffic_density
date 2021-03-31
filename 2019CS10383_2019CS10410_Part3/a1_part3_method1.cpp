#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "helper.cpp"

using namespace cv;
using namespace std;

int main(){


	//----------Variable Declarations-------------
	
	Mat I, O;
	int video_start= 0;

	vector<double> queue_density;
	vector<int> frame_number;

	string InputVideo;
	cout << "Enter the name of input video: ";
	cin >> InputVideo;

	int x;
	cout << "Enter the number of frames that must be skipped: ";
	cin >> x;


	string out= "out_method1_x" + to_string(x) + ".txt";

	time_t start, end;



	//------------Starting the clock----------------

	time(&start);




	//-----------Starting the program----------------

	//Storing the baseline image after performing cropping and homography
	I = imread("empty.jpg", IMREAD_GRAYSCALE);
	O = calc(I);

	//Opening the output file
	ofstream fout (out);
	fout << "framenum" << "," << "queue density" <<"\n";

	//Opening the input video
	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		return -1;
	}

	//Looping through all the frames of the input video
	while(1){

		Mat frame,edges;
		cap >> edges;

		if(video_start%x == 0){

			cvtColor(edges, frame, COLOR_BGR2GRAY);
			Mat out_frame;
			out_frame= calc(frame);
			queue_density.push_back(density(out_frame, O, 25));


		}else{
			queue_density.push_back(queue_density[video_start-1]);
			
		}

		frame_number.push_back(video_start+1);

		video_start= video_start+1;

		//Ending the loop if we reach the end of the video or user presses escape
		char c= (char)waitKey(25);
		if(c==27 || video_start == 50){
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
	return 0;
}
