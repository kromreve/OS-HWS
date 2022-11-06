#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


string stringLine;

typedef struct process{
	int pid; 			 
	int burst;
    int arrival;
	int priority; 	
	int deadline;
    int io;
} Process;



int main(){

	
	string stringLine;
  vector<process> allProcess;
  string fileName = "";
		cout << "Enter the file name: " << endl;
		cin >> fileName;
		

  
  ifstream IFILE(fileName);
  int retry = 0;
  
  getline(IFILE, stringLine);
  int pvalues [6];
  int n =0;
  
  while (getline (IFILE, stringLine)){

			
			 for (int i = 0; i < 6; i++)
				{
    				IFILE >> pvalues[i];
			
				}
				

				if (pvalues[0] >= 0 && pvalues[1] >= 0 && pvalues[2] >= 0 && pvalues[3] >= 0 && pvalues[4] >= 0 && pvalues[5] >= 0) { 

						process current;
						current.pid = pvalues[0];
						current.burst = pvalues[1];
						current.arrival = pvalues[2];
						current.priority = pvalues[3];
            			current.deadline = pvalues[4];
            			current.io = pvalues[5];

				
						
						allProcess.push_back(current);	

				}	


			 
		

IFILE.close();
}
