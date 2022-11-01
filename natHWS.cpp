#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

vector<process> allProcess;
string stringLine;


int main(){
  
  string fileName = "";
		cout << "Enter the file name: " << endl;
		cin >> fileName;
  
  ifstream IFILE(fileName);
  
  getline(IFILE, line);
  int pvalues [6];
  
  while (getline (IFILE, stringLine)){

				splitLine(stringLine, pvalues); 
				
				if (pvalues[0] > 0 && pvalues[1] > 0 && pvalues[2] > 0 && pvalues[3] > 0 && pvalues[4] > 0 && pvalues[5] > 0) { 

						process current;
						current.pid = pvalues[0];
						current.burst = pvalues[1];
						current.arrival = pvalues[2];
						current.priority = pvalues[3];
            current.deadline = pvalues[4];
            current.io = pvalues[5];

						allProcess.push_back(pvalues);	
				}

		}




IFILE.close();
}
