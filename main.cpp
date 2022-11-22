#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include "RedBlackTree.h"
#include "Queue.h"
using namespace std;

int tq;

vector<Process> readInput(const string filename){
    string line;
    ifstream file(filename);
    vector<Process> lines;

    regex regexp("[^0-9 \t-]");
    bool negative;
    
    getline(file, line);
    while(getline(file,line)){
        string trimmedLine = regex_replace(line, regexp, "");
        stringstream iss(trimmedLine);
        //cout << "trimmedLine: " << trimmedLine << endl;
        int a,b,c,d,e; //a pid, b burst, c priority, d arrival
        
        int i = 0;
        while(iss.good()) {
            int null;
            iss >> a;
            iss >> b;
            iss >> c;
            iss >> d;
            iss >> null;
            iss >> e;
            if (a < 0 || b < 0 || c < 0 || null < 0 || e < 0) {
                continue;
            }
            Process p = Process(a,b,c,d,e);
            //cout << "Process " << p.pid << " added to vector" << endl;
            lines.push_back(p);
        }
    }
    return lines;
}

//Compares the arrival time of two process, used for sorting processes by arrival time.
bool compareArrival(Process a, Process b) {
	if (a.arrival < b.arrival) {
		return 1;
	}
	else {
		return 0;
	}
}

void print(vector<Process> input){
    cout << "PID Burst Arrival Priority Io"<<endl;
    for(int i = 0; i < input.size(); i++){
        cout << input[i].pid << ": " 
        << input[i].burst << " " 
        << input[i].priority << " "
        << input[i].arrival << " "
        << input[i].io << endl;
    }
    cout << '\n';
}


int main(int argc,  char **argv){
    
    string processes=argv[1];

    vector<Process> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);
    //cout << input.size() << endl;

    int startTime = input[0].arrival;

    cout << "Enter the time quantum: ";
    cin >> tq;
    
    print(input);
    RBTree treeList;
    QueueList queue[100];
    cout << "queue created" << endl;
    for (int i=1;i<100;i++) {
        cout << "i=" << i << endl;
        queue[i] = QueueList(i);
    }
    input[1].arrival
    queue[1].insertProcess(&input[1]);
    queue[1].isEmpty();
    queue[1].printList();
    queue[2].printList();
    
    

    
    

    //scheduler(input);
    //double endTime = scheduler(input);
    //double totalTime = endTime - startTime;
    
    //cout << "Average Turn Around Time = " << totalTime/input.size();
    //cout << "Average Turn Around Time = " << tat/input.size();
    //cout << "\t";
    //cout << "Average Wait Time = " << (totalTime - totBurst)/input.size();
}