#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <queue>
#include <algorithm>
#include "RBTree.h"
#define DBUG
using namespace std;

int numNegatives = 0;
int tq, age;


vector<vector<int>> readInput(const string filename){
    string line;
    ifstream file(filename);
    vector<vector<int>> lines;

    regex regexp("[^0-9 \t-]");
    bool negative;
    
    getline(file, line);
    while(getline(file,line)){
        string trimmedLine = regex_replace(line, regexp, "");
         
        //string cleanLine = cleanLine.replace("/[^0-9]/g",' ');
        stringstream iss(trimmedLine);

        int value;
        vector<int> row;
        while(iss >> value){
            //cout << value << '\n';
            if(value < 0){
                negative = true;
                numNegatives++;
            }
            row.push_back(value);
        }
        
        if(!negative && (row[2] < row[4])){
            lines.push_back(row);
        }
        negative = false;
    }
    return lines;
}

void print(vector<vector<int>> input){
    for(int i = 0; i < input.size(); i++){
        cout << '\n';
        for(int j = 0; j < input[i].size(); j++){
            cout << input[i][j] << ' ';
        }
    }
    cout << '\n';
}

void printBurst(vector<vector<int>> input){
    for(int i = 0; i < input.size(); i++){
        cout << input[i][1] << '\n';
    }
}

vector<vector<int>> menu(vector<vector<int>> processes){
    char yn;
    int numProcesses, bst, arr, pri, dline, io;
    cout << "Would you like to add any additional processes? (Y/N): ";
    cin >> yn;
    if(yn == 'y'){
        cout << "Enter the number of processes you would like to add: ";
        cin >> numProcesses;

        for(int i = 0; i < numProcesses; i++){
            cout << "Process: " << i+1 << " of " << numProcesses << "." << '\n';
            cout << "Enter the Burst: ";
            cin >> bst;
            cout << "Enter the Arrival: ";
            cin >> arr;
            cout << "Enter the Priority: ";
            cin >> pri;
            cout << "Enter the Deadline: ";
            cin >> dline;
            cout << "Enter the I/O: ";
            cin >> io;

            // if((bst || arr || pri || dline || io) < 0){
            //     i--;
            //     cout << "Invalid input, only positive integers allowed. Please try entering values again.";
            //     break;
            // }
            vector<int> newProcess = {(int) processes.size()+numNegatives, bst, arr, pri, dline, io};
            processes.push_back(newProcess);
        }

        cout << "Enter the time quantum: ";
        cin >> tq;
        cout << "Enter the aging timer: ";
        cin >> age;
        cout << "Processes Added.";

    } else if(yn == 'n'){
        cout << "Enter the time quantum: ";
        cin >> tq;
        cout << "Enter the aging timer: ";
        cin >> age;
    } else {
        cout << "Invalid input";
    }


    return processes;
}


void waitingTime(vector<vector<int>> processes, int n,
            vector<int> bt, vector<int> wt, int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++){
        rem_bt[i] = bt[i];
 
    int t = 0; // Current time
    
    //do stuff here
    }
}

void turnAroundTime(vector<vector<int>> processes, int numProcesses,
                        vector<int> bt, vector<int> wt, vector<int> tat)
{
    
    for (int i = 0; i < numProcesses ; i++)
        tat[i] = bt[i] + wt[i];
}


void findavgTime(vector<vector<int>> processes, int n, vector<int> bt,
                                    int quantum)
{
    vector<int> wt;
    vector<int> tat;
    int total_wt = 0, total_tat = 0;
 
    waitingTime(processes, n, bt, wt, quantum);
 
    turnAroundTime(processes, n, bt, wt, tat);
 
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }
 
    cout << "Average waiting time = "
        << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n;
}

bool compareArrival(vector<int> a, vector<int> b) {
		if (a[2] < b[2]) {
				return 1;
		}
		else {
				return 0;
		}
}

bool comparePriority(vector<int> a, vector<int> b) {
		if (a[3] < b[3]) {
				return 1;
		}
		else {
				return 0;
		}
}

bool compareDeadline(vector<int> a, vector<int> b) {
		if (a[4] < b[4]) {
				return 1;
		}
		else {
				return 0;
		}
}

bool compareBurst(vector<int> a, vector<int> b) {
		if (a[1] > b[1]) {
				return 1;
		}
		else {
				return 0;
		}
}

int main(int argc,  char **argv){
    
    //cout << "I am line 188" << '\n';
    string processes=argv[1];
    vector<vector<int>> input = readInput(processes);
    //cout << "I am line 191" << '\n';
    sort(input.begin(), input.end(), compareArrival);
    menu(input);

    RBTree q;
    for (int i = 0; i < input.size(); i++) {
        q.insert(
            input[i][0],
            input[i][1],
            input[i][2],
            input[i][3],
            input[i][4],
            input[i][5]
            );
    }
    //q.formatPrint();
    cout << '\n' << '\n' << '\n';
    q.priorityOrder();
    //cout << input[2][0];
    //printBurst(input);

    int numProcesses = input.size();
    vector<queue<vector<int>>> allQueues;

    for (int i = 0; i <= 99; i++) {
			queue<vector<int>> temp;

        for(int j=0; j<numProcesses; j++){
            if(input[j][3] == i){
                temp.push(input[j]);
             }
        }
        allQueues.push_back(temp);
	}


    int clockTicks = 0, iterator = 0, cpuIterator = 0, size;
    vector<int> temp;
    vector<vector<int>> currentProcesses;
    vector<vector<int>> CPU;
    
    bool printer = true;

   // while(input[size-1][4] <= clockTicks){
    while(1){
        size = input.size();
        sort(currentProcesses.begin(), currentProcesses.end(), comparePriority);
        sort(CPU.begin(), CPU.end(), comparePriority);

        if(!currentProcesses.empty()){  //start running process with highest priority
            if(printer == true){
                            cout << "Clock Tick " << clockTicks << ": |";
                        }
            else{
                cout << "\t\t" << "|";
            }
        for(int i =99; i>=0; i--){
            
            if(currentProcesses[(currentProcesses.size()-1)][3] == i){
                
              //  cout << '\n' << "Clock tick " << clockTicks << ": " << '\n';
                queue<vector<int>> priorityI = allQueues[i];
                temp = priorityI.front();
                currentProcesses.pop_back();
               
                CPU.push_back(temp);
                CPU[CPU.size()-1][2] = clockTicks; //set new arrival time
                
                cout << " Process " << temp[0] << " enters CPU" << '\n';
                }
            else{
                continue;
            }
           
            break;
        }
        }

        for(int i=0; i<currentProcesses.size(); i++){ //increment age
            currentProcesses[i][6]++;
        }

        
        
        for(int i =0; i< input.size(); i++) {
															
				if (input[iterator][2] == clockTicks) {	//arrival
                        if(printer == true){
                            cout << "Clock Tick " << clockTicks << ": |";
                            printer == false;
                        }
                    										
						currentProcesses.push_back(input[iterator]);											
                        cout << " Process " << input[iterator][0] << " arrives" << '\n';
                        input[iterator][6] == 0;
                        iterator++;
                        																														
				}
                  else if (input[iterator][4] == clockTicks ){ //reaches deadline
               
                        if(printer == true){
                            cout << "Clock Tick " << clockTicks << ": |";
                            printer == false;
                        }
                   
                    
                    
                    cout << " Process " << input[iterator][0] << " reaches deadline" << '\n';
                    sort(currentProcesses.begin(), currentProcesses.end(), compareDeadline);
                    sort(CPU.begin(), CPU.end(), compareDeadline);
                    
                   if(!CPU.empty() && CPU[CPU.size()-1][4] == clockTicks){
                    cout << "before";
                        print(CPU);
                        CPU.pop_back();
                    cout << "after";
                    print(CPU);
                        
                    }
                   if(!currentProcesses.empty() && currentProcesses[currentProcesses.size()-1][4] == clockTicks){
                        print(currentProcesses);
                        currentProcesses.pop_back();
                        print(currentProcesses);
                    }
                    
                    //remove(CPU.begin(), CPU.end(), input[iterator]);
                    
                    iterator++;
                    //sort(input.begin(), input.end(), comparePriority);
                    
                } 
                
                else if(input[iterator][6] == age){
                    //promote
                     cout << " Process " << input[iterator][0] << " aging timer expires (promoted)" << '\n';
                     iterator++;
                }
                
                else{
                    iterator++;
                } 
		}

        for(int i=0; i<CPU.size(); i++){
         if(CPU[i][1] == 0){ //if burst ends, process finished
                    if(printer == true){
                            cout << "Clock Tick " << clockTicks << ": |";
                            printer == false;
                        }
                
                    cout << " Process " << CPU[i][0] << " finishes running" << '\n';
                    //remove(input.begin(), input.end(), CPU[i]);
                    
                    for(int i=0; i< CPU.size(); i++){ 
                    if(CPU[i][1] == 0){
                    
                        CPU.pop_back();
                    }
                    if(currentProcesses[i][1] == 0){
                        currentProcesses.pop_back();
                    }
                    
                    }
                    
                   
                }

                else if(clockTicks == (CPU[i][2] + tq)){ //time quantum expires
                    if(printer == true){
                            cout << "Clock Tick " << clockTicks << ": |";
                            printer == false;
                        }
                 
                    //demotion (remove from current priority queue and put into a lower one)
                    
                    cout << " Process " << CPU[i][0] << " time quantum expires (demoted)" << '\n';
                   
                   
                        currentProcesses.push_back(CPU[i]);
                        for(int i=0; i< CPU.size(); i++){ 
                            if(CPU[i][2] +tq == clockTicks ){ //pause burst
                               //remove CPU[i]
                        
                   }
                   }
                     
                    
                    
                    //start wait
                    
                }
                
    }
        sort(currentProcesses.begin(), currentProcesses.end(), comparePriority);
        
        

        for(int i=0; i< CPU.size(); i++){ //decrease burst for active processes
            CPU[i][1]--;
            
        }
        

       sort(input.begin(), input.end(), compareDeadline);
        if(clockTicks > input[size-1][4]){
                        break;
                    }	
    iterator = 0;
    printer = true;
    clockTicks++;
    } 

    cout << "exited loop";

    vector <int> burstTimes;
    for(int i=0; i< numProcesses; i++){
        burstTimes[i] = input[i][1];
    }
 
    findavgTime(input, numProcesses, burstTimes, tq);
    return 0;
}


