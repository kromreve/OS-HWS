#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <queue>
#include <algorithm>
#include "RBTree.h"
#include "LinkedList.h"
#define DBUG
using namespace std;

int numNegatives = 0;
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
         
        stringstream iss(trimmedLine);

        int value;
        vector<int> row;
        while(iss >> value){
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

//Compares the arrival time of two process, used for sorting processes by arrival time.
bool compareArrival(vector<int> a, vector<int> b) {
		if (a[2] < b[2]) {
				return 1;
		}
		else {
				return 0;
		}
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



//The scheduler method is used to keep track of what is happening at every clock tick and responds accordingly
void scheduler(vector<vector<int>> processes){
    int clockticks = 0;
    int iterator = 0;
    RBTree queue;
    Linkedlist list;

    while(1){

        //if next process's arrival time matches current clock tick, add it to the tree and remove it from the input vector
        if(processes[iterator][2] == clockticks){
            //Loop to check if the next process also arrives at the same clock tick    
            while(processes[iterator][2]==clockticks && processes.size() > 0){
                queue.insert(
                    processes[iterator][0],
                    processes[iterator][1],
                    processes[iterator][2],
                    processes[iterator][3],
                    processes[iterator][4],
                    processes[iterator][5]
                );
                cout << "Process " << processes[iterator][0] << " arrived at clock tick " << clockticks << '\n';

                //Insert process into linked list and calculate the clock tick that process will have to promote, if it is still in the tree
                int pID = processes[iterator][0];
                int promotionClockTick = clockticks + 100;
                //cout << "Promotion Clock Tick: " << promotionClockTick << '\n';
                list.insertNode(pID, promotionClockTick);
                //list.printList();

                processes.erase(processes.begin());
            }
        }

        //Check linked list to see if last value needs to be promoted
        if(!list.isEmpty()){
            if(list.getLastClockTick()==clockticks){
                int process = list.getLastPID();
                cout << "Process " << process << " needs to be promoted." << '\n';
                list.deleteNode(1); 
            }
        }

        //if(q is empty && cpu is empty && processes is empty){
        //    break;
        //}
        //print(processes);
        clockticks++;
    }
}




int main(int argc,  char **argv){
    
    string processes=argv[1];

    vector<vector<int>> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);

    cout << "Enter the time quantum: ";
    cin >> tq;

    scheduler(input);
    
}