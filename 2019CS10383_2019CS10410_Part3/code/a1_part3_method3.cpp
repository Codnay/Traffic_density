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

//----------Global Variable Declaration-------------
int thread_tot;
vector<Mat> outstream;
Mat I,O;




//---------Helper Functions and Struct---------------

//Function to calculate altered pixels
double density_total(Mat img1, Mat img2, int th, int total, int k){

	double nz = 0.0;
	for(int j= (img1.rows*k)/total; j<(img1.rows*(k+1))/total; j++) {
        for(int i=0; i<img1.cols; i++){
            int pix = img1.at<uchar>(j,i);
            int pix1 = img2.at<uchar>(j,i);
            
            if(abs(pix1 - pix) > th){
                nz = nz + 1.0;
            }
        }
    }
	
	return(nz);
}

//Struct to pass as argument to a pthread
struct thread_number_container
{
	int number;
	vector<vector<double>> file_data;
};

//Function to pass as argument to a pthread
void* imgcalc(void* arg){

	//Local variable declarations
	struct thread_number_container *arg_struct = (struct thread_number_container*) arg;
	int video_frame= 0;

	//Looping through an input of frames
	while(video_frame < 5722){


		vector<double> v;
		v.push_back((double)video_frame+1);
		v.push_back(density_total(outstream[video_frame], O, 25, thread_tot, arg_struct->number));
		arg_struct->file_data.push_back(v);

		video_frame= video_frame+1;
		
		
	}

	cout << "Thread :" << arg_struct->number << " finished" <<"\n";

	pthread_exit(0);
}

int main(){

	//--------------Variable Declarations----------------
	time_t start, end;

	string InputVideo;
	cout << "Input Video: ";
	cin >> InputVideo;
	
	cout << "Number of threads: ";
	cin >> thread_tot;

	struct thread_number_container args[thread_tot];

	string out= "out_method3_thread" + to_string(thread_tot) + ".txt";
	int video_start= 0;




	//---------------Starting the clock-------------------
	time(&start);




	//--------------Starting the program------------------
	I = imread("empty.jpg", IMREAD_GRAYSCALE);
	O = calc(I);

	//Opening the input video
	VideoCapture cap(InputVideo);
	if(!cap.isOpened()){
		cout << "Error loading the file"<< endl;
		exit(1);
	}

	//Looping through the input video and storing transformed images
	while(1){

		//Local variable declarations
		Mat frame;
		Mat edges;
		cap >> edges;

		cvtColor(edges, frame, COLOR_BGR2GRAY);
		Mat out_frame;
		out_frame= calc(frame);

		outstream.push_back(out_frame);

		video_start= video_start+1;

		//Ending the video if reached the end or user presses escape
		char c= (char)waitKey(25);
		if(c==27 || video_start == 5722){
			break;
		}
		
	}

	//Closing the input video
	cap.release();
	destroyAllWindows();

	//Initialising the pthreads
	pthread_t tids[thread_tot];
	for (int i = 0; i < thread_tot; ++i)
	{
		args[i].number = i;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, imgcalc, &args[i]);
	}

	//Joining the pthreads to the main thread
	for (int i = 0; i < thread_tot; ++i)
	{
		pthread_join(tids[i], NULL);
	}

	//Opening the output file
	ofstream fout (out);
	fout << "framenum" << "," << "queue density" <<"\n";

	vector<vector<double>> x= args[0].file_data;
	
	//Outputting in the output file
	for (int j = 0; j < x.size(); ++j)
	{	
		double sum= 0;
		for(int i=0; i<thread_tot; i++){
			sum= sum+ args[i].file_data[j][1];
		
		}
		sum= sum/ (O.rows*O.cols);
		fout << x[j][0] << "," << sum << "\n";
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
