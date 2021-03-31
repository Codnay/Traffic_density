#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
//#include <bits/stdc++.h>
#include <vector>
#include "helper.cpp"
#include <pthread.h>

using namespace cv;
using namespace std;

//--------Global Variable Declarations-----------

int thread_tot;
Mat I,O;




//-------Helper functions and structs------------

//Struct to be passed as argument to pthreads
struct thread_number_container
{
	int number;
	vector<vector<double>> file_data;
	string In;
};

//Function to be passed as argument to pthread
void* imgcalc(void* arg){

	//Local variable declarations
	struct thread_number_container *arg_struct = (struct thread_number_container*) arg;
	string InputVideo= arg_struct->In;

	int video_start= 0;

	//Opening an instance of the input video
	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		exit(1);
	}

	//Looping though all the frames of the input video
	while(1){

		Mat frame;
		Mat edges;
		cap >> edges;


		if(video_start%thread_tot == arg_struct->number){


			cvtColor(edges, frame, COLOR_BGR2GRAY);
			Mat out_frame;
			out_frame= calc(frame);

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

	//closing the instance of the input video
	cap.release();
	destroyAllWindows();

	cout << "Thread :" << arg_struct->number << " finished" <<"\n";


	pthread_exit(0);
}


int main(){

	//--------------Variable Declarations----------------

	string input;
	cout << "Input video: ";
	cin >> input;

	cout << "Number of threads: ";
	cin >> thread_tot;
	
	struct thread_number_container args[thread_tot];

	string out= "out_method4_thread" + to_string(thread_tot) + ".txt";

	time_t start, end;




	//----------------Starting the clock---------------
	time(&start);




	//---------------Starting the program--------------
	I = imread("empty.jpg", IMREAD_GRAYSCALE);
	O = calc(I);

	//Initialising the pthreads
	pthread_t tids[thread_tot];
	for (int i = 0; i < thread_tot; ++i)
	{
		args[i].number = i;
		args[i].In= input;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, imgcalc, &args[i]);
	}

	//Joining the pthreads with the main thread
	for (int i = 0; i < thread_tot; ++i)
	{
		pthread_join(tids[i], NULL);
	}


	//Opeing the output file
	ofstream fout (out);
	fout << "framenum" << "," << "queue density" <<"\n";
	
	//Outputting in the output file
	for (int i = 0; i < thread_tot; ++i)
	{
		vector<vector<double>> x = args[i].file_data;
		for (int j = 0; j < x.size(); ++j)
		{
			fout << x[j][0] << "," << x[j][1] << "\n";
		}
	}

	//Closing the output file
	fout.close();




	//----------Closing the clock--------------
	time(&end);
	double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
}
