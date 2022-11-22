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
int tat=0;
int wt=0;
int totBurst =0;


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
    vector<int> CPU;
    bool printer = true;
    NodePtr temp;
    //NodePtr inCPU;
    

    while(1){
        if(clockticks%100 == 0){
            cout << "Clocktick: " << clockticks << endl;
        }

        if(CPU.empty() && queue.getRoot() != queue.TNULL){ //start running process with highest priority
            temp = queue.maximum(queue.getRoot()); //add process with highest priority to CPU 
            //queue.formatPrint();

            //queue.printProcess(temp);
            //cout << "Process ID from tree: " << *(queue.exportProcess(temp)) << endl;
            CPU.push_back(queue.returnPid(temp));
            CPU.push_back(queue.returnBurst(temp));
            CPU.push_back(queue.returnArrival(temp));
            CPU.push_back(queue.returnPriority(temp));
            CPU.push_back(queue.returnDeadline(temp));
            CPU.push_back(queue.returnIo(temp));
            CPU.push_back(clockticks + tq);
            
            //cout << "Process ID to go into CPU: " << CPU[0] << endl;
  	        list.deleteNode(list.getOffsetByID(CPU[0]));
            //inCPU = queue.searchTree(CPU[0]);
            //queue.deleteNode(inCPU);
            queue.deleteNode(queue.searchTree(CPU[0]));
            //queue.formatPrint();
            
            
		
	    #ifdef DBUG
            if(printer == true){
                cout << "Clock Tick " << clockticks << ": |";
                printer = false;
            }
            else{
                cout << "\t\t";
            }
                cout << " Process " << CPU[0] << " enters the CPU" << '\n';
        #endif
        }

        if(!CPU.empty()){ //Process is currently running
            //queue.formatPrint();
            if(CPU[1] == 0){  //process finishes
                #ifdef DBUG
                   if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
	        	        printer = false;
                    }
		         	else{
		                cout << "\t\t";
                    }
                        cout << " Process " << CPU[0] << " finishes running" << '\n';
                #endif
		        //tat = tat + (clockticks - CPU[2]); 
                //queue.deleteNode(queue.searchTree(CPU[0]));
                CPU.clear();
                temp = nullptr;
                //inCPU = nullptr;
                //cout << "CPU Cleared." << " Size: " << CPU.size() << endl;               
            }
            else{  //decrement burst
                int temp = CPU[1]-1;
                CPU[1] = temp;
                //cout << "Burst: " << CPU[1] << endl;
            }
		
            if(!CPU.empty() && CPU[6] == clockticks && CPU[1] > 0){ //time quantum expires
                #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
                        printer = false;
                    }
                    else{
                        cout << "\t\t";
                    }
                        cout << " Process " << CPU[0] << " is demoted" << '\n';
                #endif
		    //demote
		        int promotionClockTick = clockticks + 100;
		        int currentPID = CPU[0];
		        int pri = CPU[3];
                //int basePriTemp = queue.returnBasePriority(inCPU);
                int basePriTemp = queue.returnBasePriority(queue.searchTree(CPU[0]));

                if(pri - 10 < basePriTemp){
                    CPU[3] = basePriTemp;
                } else {
                    CPU[3] = pri - 10;
                }
                //queue.deleteNode(queue.searchTree(currentPID));
                //list.deleteNode(1);
                queue.insert(
                    CPU[0],
                    CPU[1],
                    CPU[2],
                    CPU[3],
                    CPU[4],
                    CPU[5]
                );
                list.insertNode(currentPID, promotionClockTick);
                CPU.clear();
                temp = nullptr;
                //inCPU = nullptr;
            }
        }
        
	 

        //if next process's arrival time matches current clock tick, add it to the tree and remove it from the input vector
        if(processes[iterator][2] == clockticks){
            //Loop to check if the next process also arrives at the same clock tick    
            while(processes[iterator][2]==clockticks && processes.size() > 0){
		        totBurst = totBurst + processes[iterator][1]; //adds arriving process burst to total burst
                queue.insert(
                    processes[iterator][0],
                    processes[iterator][1],
                    processes[iterator][2],
                    processes[iterator][3],
                    processes[iterator][4],
                    processes[iterator][5]
                );
		        #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
		                printer = false;
                    }
		    	    else{
			            cout << "\t\t";
			        }
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
            
            while(list.getLastClockTick()==clockticks && !list.isEmpty()){
                int process = list.getLastPID();
                #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
                        printer = false;
                    }
                    else{
                        cout << "\t\t";
                    }
                    cout << " Process " << process << " is promoted" << '\n';
                #endif
                //Extracts the node/process that needs to be promoted

                NodePtr x = queue.searchTree(process);
                vector<int> pvalues = {
                    queue.returnPid(x),
                    queue.returnBurst(x),
                    queue.returnArrival(x),
                    queue.returnPriority(x),
                    queue.returnDeadline(x),
                    queue.returnIo(x)
                };
                int pri = pvalues[3];
                if(pri + 10 > 99){
                    pvalues[3] = 99;
                } else {
                    pvalues[3] = pri + 10;
                }

                if(process == 852){
                    queue.formatPrint();
                    queue.printProcess(queue.searchTree(process));
                    queue.printProcess(x);
                }
                queue.deleteNode(x);

                list.deleteNode(1);

                queue.insert(
                    pvalues[0],
                    pvalues[1],
                    pvalues[2],
                    pvalues[3],
                    pvalues[4],
                    pvalues[5]
                );
                //x = nullptr;
                int promotionClockTick = clockticks + 100;
                list.insertNode(pvalues[0], promotionClockTick);
                pvalues.clear();
                }
        }
        //print(processes);
        clockticks++;
	    iterator = 0;
	    printer = true;
        if(queue.getRoot() == queue.TNULL && CPU.empty() && processes.size() == 0){
           break;
        }
    }
    return clockticks;
}




int main(int argc,  char **argv){
    
    string processes=argv[1];

    vector<vector<int>> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);
    //cout << input.size() << endl;

    int startTime = input[0][2];

    cout << "Enter the time quantum: ";
    cin >> tq;
    
    //scheduler(input);
    double endTime = scheduler(input);
    double totalTime = endTime - startTime;
    
    cout << "Average Turn Around Time = " << totalTime/input.size();
    //cout << "Average Turn Around Time = " << tat/input.size();
    cout << "\t";
    cout << "Average Wait Time = " << (totalTime - totBurst)/input.size();
}
