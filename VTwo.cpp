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
//#define DBUG
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
int scheduler(vector<vector<int>> processes){
    int clockticks = 0;
    int iterator = 0;
    RBTree queue;
    Linkedlist list;
    int cpu[7];
    bool printer = true;

    while(1){

        // if(CPU.empty() && !queue.empty()){  //start running process with highest priority
		// #ifdef debug
        //                 if(printer == true){
        //                     cout << "Clock Tick " << clockticks << ": |";
		// 	    printer = false;
        //                 }
		//     	else{
		// 	    cout << "\t\t";

        //         cout << " Process " << processes[iterator][0] << " enters the CPU" << '\n';
        //         #endif	

        //     //add process with highest to cpu

        //     CPU[6] = clockticks +tq;
        // }

        // if(!CPU.empty()){

        //     if(CPU[1] == 0){  //process finishes
		//     #ifdef debug
        //                 if(printer == true){
        //                     cout << "Clock Tick " << clockticks << ": |";
		// 	    printer = false;
        //                 }
		//     	else{
		// 	    cout << "\t\t";

        //         cout << " Process " << processes[iterator][0] << " finishes running" << '\n';
        //         #endif	

        //             //queue.remove(CPU);

        //             CPU.remove(CPU);

        //         }

        //     else{  //decrement burst

        //         int temp = CPU[1];

        //         CPU[1] = temp--;

        //     }

        //     if(CPU[6] == clockTick){ //time quantum expires
		// #ifdef debug
        //                 if(printer == true){
        //                     cout << "Clock Tick " << clockticks << ": |";
		// 	    printer = false;
        //                 }
		//     	else{
		// 	    cout << "\t\t";

        //         cout << " Process " << processes[iterator][0] << " is demoted" << '\n';
        //         #endif	

        //         CPU.remove(CPU);
        //         //demote

        //     }
        // }

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
		#ifdef debug
                        if(printer == true){
                            cout << "Clock Tick " << clockticks << ": |";
		            printer = false;
                        }
		    	else{
			    cout << "\t\t";

                cout << " Process " << processes[iterator][0] << " arrives" << '\n';
                #endif	
                //cout << "Process " << processes[iterator][0] << " arrived at clock tick " << clockticks << '\n';

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
		#ifdef debug
                if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
                printer = false;
                    }
		    	else{
			    cout << "\t\t";

                cout << " Process " << processes[iterator][0] << " is promoted" << '\n';
                #endif
                cout << "Process " << process << " promoted at clock tick "<< clockticks << '\n';
                //Extracts the node/process that needs to be promoted
                vector<int> pvalues = {*(queue.exportProcess(queue.searchTree(process))),
                                    *(queue.exportProcess(queue.searchTree(process))+1),
                                    *(queue.exportProcess(queue.searchTree(process))+2),
                                    *(queue.exportProcess(queue.searchTree(process))+3),
                                    *(queue.exportProcess(queue.searchTree(process))+4),
                                    *(queue.exportProcess(queue.searchTree(process))+5)
                                    };
                int pri = pvalues[3];
                pvalues[3] = pri + 10;
                queue.deleteNode(queue.searchTree(process));
                list.deleteNode(1);
                queue.insert(
                    pvalues[0],
                    pvalues[1],
                    pvalues[2],
                    pvalues[3],
                    pvalues[4],
                    pvalues[5]
                );
                pvalues.clear();
                int promotionClockTick = clockticks + 100;
                list.insertNode(pvalues[3], promotionClockTick);
            }
        }

        //if(q is empty && cpu is empty && processes is empty){
        //    break;
        //}
        //print(processes);
        clockticks++;
	printer = true;
    }
    return clockticks;
}




int main(int argc,  char **argv){
    
    string processes=argv[1];

    vector<vector<int>> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);

    int startTime = input[0][2];

    cout << "Enter the time quantum: ";
    cin >> tq;

    int endTime = scheduler(input);

    int totalTime = endTime - startTime;
    
    //cout << "Average Turn Around Time = " << totalTime/input.size();
}
