#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"

using namespace cv;
using namespace std;

int main(){
	Mat I = imread("empty.jpg", IMREAD_GRAYSCALE);
	Mat O = calc(I);

	vector<double> queue_density;
	vector<double> dynamic_density;
	vector<int> frame_number;

	string InputVideo;
	cin >> InputVideo;
	int video_start= 0;

	ofstream fout ("out.txt");
	fout << "framenum" << "," << "queue density" << "," << "dynamic density" <<"\n";

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
		queue_density.push_back(density(out_frame, O, 25));

		Mat dst;
		bitwise_xor(temp, O, dst);        
		if(countNonZero(dst) > 0){
			dynamic_density.push_back(density(out_frame, temp, 25));
		}	
		else{
			dynamic_density.push_back(density(out_frame, out_frame, 25));
		}

		temp = temp1;
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp4;
		temp4 = temp5;
		temp5 = temp6;
		temp6 = out_frame;

		video_start= video_start+1;
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5722){
			break;
		}
		
	}
	cap.release();
	destroyAllWindows();

	cout << "time (in secs)" << ", " << "queue density" << ", " << "dynamic density" <<"\n";

	for(int k = 0; k < frame_number.size(); k++){
		cout << frame_number[k]/15.0 << ", " << queue_density[k] << ", " << dynamic_density[k] << "\n";
		fout << frame_number[k] << "," << queue_density[k] << "," << dynamic_density[k] << "\n";
	}

	fout.close();
	return 0;
}
