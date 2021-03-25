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

int sqdiff(int a, int b){
	return (int)(pow(a-b,2)+0.5);
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

	vector<vector<int> > a;
	vector<vector<int> > b;

	for(int i= 0; i<first.size(); i++){
		int temp=0;

		while(first[i][temp] != ' '){
			temp+=1;
		}

		int helper= temp+1;
		int help= temp+1;

		while(first[i][temp] != ' '){
			help+=1;
		}

		vector<int> rand;
		rand.push_back(str_to_int(first[i].substr(0,temp)));
		rand.push_back(str_to_int(first[i].substr(helper, help)));
		a.push_back(rand);


	}

	for(int i= 0; i<second.size(); i++){
		int temp=0;

		while(second[i][temp] != ' '){
			temp+=1;
		}

		int helper= temp+1;
		int help= temp+1;

		while(second[i][temp] != ' '){
			help+=1;
		}

		vector<int> rand;
		rand.push_back(str_to_int(second[i].substr(0,temp)));
		rand.push_back(str_to_int(second[i].substr(helper, help)));
		b.push_back(rand);


	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	vector<vector<int> > c;

	for(int i= 0; i<second.size(); i++){
		
		int k= sqdiff(a[i][1], b[i][1]);

		vector<int> rand;
		rand.push_back(a[i][0]);
		rand.push_back(k);
		c.push_back(rand);

	}

	print(c);

	return 0;

}