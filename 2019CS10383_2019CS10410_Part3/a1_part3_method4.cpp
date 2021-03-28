#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"
#include <pthread.h>

using namespace cv;
using namespace std;


int thread_tot= 4;

Mat I,O;


struct thread_number_container
{
	int number;
	vector<vector<double>> file_data;
};

void* imgcalc(void* arg){

	struct thread_number_container *arg_struct = (struct thread_number_container*) arg;
	//Note that this is hard coded for now, to change this 
	//we will have to pass an extra string argument in imgcalc
	string InputVideo= "trafficvideo.mp4";

	int video_start= 0;

	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		exit(1);
	}

	while(1){

		if(video_start%thread_tot == arg_struct->number){


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

			vector<double> v;
			v.push_back((double)video_start+1);
			v.push_back(density(out_frame, O, 25));

			arg_struct->file_data.push_back(v);

		}

		video_start= video_start+1;
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5722){
			break;
		}
		
	}
	cap.release();
	destroyAllWindows();

	cout << "Thread :" << arg_struct->number << " finished" <<"\n";

	/*for(int k = 0; k < frame_number.size(); k++){
		//cout << frame_number[k]/15.0 << ", " << queue_density[k] << "\n";
		fout << frame_number[k] << "," << queue_density[k]  << "\n";
	}*/

	pthread_exit(0);
}

int main(){
	time_t start, end;
	time(&start);
	
	/*vector<int> thread_count;

	for(int i=0 ; i< thread_tot; i++){
		thread_count.push_back(i);
	}*/
	struct thread_number_container args[thread_tot];

	I = imread("empty.jpg", IMREAD_GRAYSCALE);
	O = calc(I);

	pthread_t tids[thread_tot];
	for (int i = 0; i < thread_tot; ++i)
	{
		args[i].number = i;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, imgcalc, &args[i]);
	}

	/*thread t1(imgcalc, thread_tot, thread_count[0]);
	thread t2(imgcalc, thread_tot, thread_count[1]);
	thread t3(imgcalc, thread_tot, thread_count[2]);
	thread t4(imgcalc, thread_tot, thread_count[3]);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	*/

	for (int i = 0; i < thread_tot; ++i)
	{
		pthread_join(tids[i], NULL);
	}


	ofstream fout ("out_method4_t4_2.txt");
	fout << "framenum" << "," << "queue density" <<"\n";
	
	for (int i = 0; i < thread_tot; ++i)
	{
		vector<vector<double>> x = args[i].file_data;
		for (int j = 0; j < x.size(); ++j)
		{
			fout << x[j][0] << "," << x[j][1] << "\n";
		}
	}


	fout.close();

	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
}
