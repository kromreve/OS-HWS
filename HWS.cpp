#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <queue>
using namespace std;

int numNegatives = 0;
int tq;

vector<vector<int>> readInput(const string filename){
    string line;
    ifstream file(filename);
    vector<vector<int>> lines;

    regex regexp("[^0-9 \t-]");
    bool negative;
    
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
        if(!negative){
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
        cout << "Processes Added.";

    } else if(yn == 'n'){
        cout << "Enter the time quantum: ";
        cin >> tq;
    } else {
        cout << "Invlaid input";
    }


    return processes;
}

void waitingTime(vector<vector<int>> processes, int n,
            int bt[], int wt[], int quantum)
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
                        int bt[], int wt[], int tat[])
{
    
    for (int i = 0; i < numProcesses ; i++)
        tat[i] = bt[i] + wt[i];
}


void findavgTime(vector<vector<int>> processes, int n, int bt[],
                                    int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
 
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

int main(int argc,  char **argv){
    string processes=argv[1];
    vector<vector<int>> input = readInput(processes);
    print(menu(input));
    //cout << input[2][0];
    //printBurst(input);

    int numProcesses = input.size();
    vector<queue<vector<int>>> allQueues;

    for (int i = 0; i <= 99; i++) {
			queue<vector<int>> temp;
			allQueues.push_back(temp);

        for(int j=0; j<numProcesses; j++){
            if(input[j][3] == i){
                temp.push(input[j]);
             }
        }
	}

    sort(input.begin(), input.end(), compareArrival);

    



    int burstTimes[] = {};
    for(int i=0; i< numProcesses; i++){
        burstTimes[i] = input[i][1];
    }
 
    // Time quantum
    findavgTime(input, numProcesses, burstTimes, tq);
    return 0;
}


