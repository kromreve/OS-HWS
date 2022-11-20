#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include "RBTree.h"

using namespace std;

int tq;


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
            vector<int> newProcess = {(int) processes.size(), bst, arr, pri, dline, io};
            processes.push_back(newProcess);
        }

        cout << "Enter the time quantum: ";
        cin >> tq;
    } else {
        cout << "Invalid input";
    }

    return processes;
}

void scheduler(vector<vector<int>> input) {

    RBTree queue;
    int clockTicks,i = 0;

    while(1) {
        
        cout << "Clocktick " << clockTicks << ": ";

        //Detect when process's arrival is equal to the current clock tick.
        if (input[i][2] == clockTicks) {

            queue.insert(
                input[i][0],
                input[i][1],
                input[i][2],
                input[i][3],
                input[i][4],
                input[i][5]
            );

            cout << "Clocktick " << clockTicks << ": Process " << input[i][0] << " has arrived.";
        }
        
        clockTicks++;
    }
}

bool compareArrival(vector<int> a, vector<int> b) {
		if (a[2] < b[2]) {
				return 1;
		}
		else {
				return 0;
		}
}


int main(int argc,  char **argv) {
    string processes=argv[1];
    vector<vector<int>> input = readInput(processes);
    sort(input.begin(), input.end(), compareArrival);
    menu(input);
    print(input);

    scheduler(input);
}