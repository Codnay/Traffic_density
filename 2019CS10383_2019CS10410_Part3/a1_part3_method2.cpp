#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"

using namespace cv;
using namespace std;

Mat resize(Mat img){

	Mat res = cv2.resize(img, (img.shape[1]/2, img.shape[0]/2), interpolation=INTER_AREA);
	return res;

}

int main(){
	time_t start, end;
	time(&start);
	

	Mat I = imread("empty.jpg", IMREAD_GRAYSCALE);
	Mat O = resize(calc(I));



	vector<double> queue_density;
	vector<int> frame_number;

	string InputVideo;
	cin >> InputVideo;
	int video_start= 0;

	ofstream fout ("out.txt");
	fout << "framenum" << "," << "queue density" <<"\n";

	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		return -1;
	}

	while(1){


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

	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
	return 0;
}
