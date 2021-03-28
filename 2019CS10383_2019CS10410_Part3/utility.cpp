#include <iostream>
#include <fstream>
#include <sstream>  
#include <string> 
#include <string.h>  
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <math.h>
using namespace std;

//The given code reads the values of frame numbers from 2 files and 
//outputs the corresponding utility

int sqdiff(double a, double b){
	return (pow(a-b,2));
}

int str_to_int(string s){
	stringstream num(s);
	int helper= 0;
	num >> helper;
	return helper;
}

void print(vector<vector<int> > a){
	for(int i= 0; i< a.size(); i++){
		cout << a[i][0] << " " << a[i][1] << endl;
	}
	return;
}


int main(){
	string s;
	cin >> s;

	string k;
	cin >> k;

	string line;

	ifstream myfile(s);
	vector<string> first;

	while(getline(myfile,line)){
		first.push_back(line);
	}

	myfile.close();

	ifstream myfil(k);
	vector<string> second;

	while(getline(myfil, line)){
		second.push_back(line);
	}

	myfile.close();

	vector<vector<double> > a;
	vector<vector<double> > b;

	for(int i= 1; i<first.size(); i++){
		int temp=0;

		while(temp < second[i].size() && first[i][temp] != ','){
			temp+=1;
		}

		int helper= temp+1;
		int help= temp+1;

		while(help < second[i].size() && first[i][help] != '\t'){
			help+=1;
		}

		vector<double> rand;
		rand.push_back(stod(first[i].substr(0,temp)));
		rand.push_back(stod(first[i].substr(helper, help)));
		a.push_back(rand);


	}

	for(int i= 1; i<second.size(); i++){
		int temp=0;

		while(temp < second[i].size() && second[i][temp] != ','){
			temp+=1;
		}

		int helper= temp+1;
		int help= temp+1;

		while(help < second[i].size() && second[i][help] != '\t'){
			help+=1;
		}

		vector<double> rand;
		rand.push_back(stod(second[i].substr(0,temp)));
		rand.push_back(stod(second[i].substr(helper, help)));
		b.push_back(rand);


	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	//vector<vector<int> > c;

	double total=0.0;
	for(int i= 0; i<second.size()-1; i++){
		
		//cout<< a[i][1] << " " << b[i][1] << endl;
		total+=  (a[i][1] - b[i][1])*(a[i][1] - b[i][1]);

		//vector<int> rand;
		//rand.push_back(a[i][0]);
		//rand.push_back(k);
		//c.push_back(rand);

	}

	//print(c);
	cout << pow((double)total/(second.size()-1), 0.5) << endl;

	return 0;

}
