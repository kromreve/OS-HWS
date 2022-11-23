#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
//#include "RedBlackTree.h"
#include "RBTree.h"
#include "Process.h"
//#include "Queue.h"
#define DBUG
using namespace std;

int numNegatives = 0;
int tq;
int tat=0;
int wt=0;
int totBurst =0;

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
        << input[i].arrival << " "
        << input[i].priority << " "
        << input[i].io << endl;
    }
    cout << '\n';
}

int scheduler(vector<Process> processes){
    int clockticks = 0;
    int iterator = 0;
    //RBTree queue;
    //Linkedlist list;
    vector<int> CPU;
    bool printer = true;
    //NodePtr temp;
    vector <Process> ioWait;
    //NodePtr inCPU;
    RBTree treeList;
    QueueList queue[100];
    //cout << "queue created" << endl;
    for (int i=1;i<100;i++) {
        //cout << "i=" << i << endl;
        queue[i] = QueueList(i);
    }
    

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
		
	   if(!CPU.empty() && (CPU[6]-1) == clockticks && CPU[5] > 0){ //does io
                #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
                        printer = false;
                    }
                    else{
                        cout << "\t\t";
                    }
                        cout << " Process " << CPU[0] << " does I/O" << '\n';
                #endif
            
                CPU[6] = CPU[5] + clockticks;

                ioWait.push_back(CPU);

                int promotionClockTick= CPU[6] +100;
                int pID = CPU[0];
               
                list.insertNode(pID, promotionClockTick);
                CPU.clear();
                
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
        if(processes[iterator].arrival == clockticks){
            //Loop to check if the next process also arrives at the same clock tick    
            while(processes[iterator].arrival==clockticks && processes.size() > 0){
		        totBurst = totBurst + processes[iterator].burst; //adds arriving process burst to total burst
                int pri = processes[iterator].priority;

                queue[pri].insertProcess(&processes[iterator]);

                if(treeList.searchTree(pri)==NULL){
                    treeList.insert(pri);
                }

		        #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
		                printer = false;
                    }
		    	    else{
			            cout << "\t\t";
			        }
                    cout << " Process " << processes[iterator].pid << " arrives" << '\n';
                #endif
                //cout << "Process " << processes[iterator][0] << " arrived at clock tick " << clockticks << '\n';

                //Insert process into linked list and calculate the clock tick that process will have to promote, if it is still in the tree

                iterator++;
            }
        }
        //Check linked list to see if last value needs to be promoted
        if(treeList.getRoot() != NULL){
		
	    //     for(int i =0; i<ioWait.size(); i++){
        //     if(ioWait[i][6] == clockticks && clockticks !=0){ //io promotion
        //         int process = ioWait[i][0];
        //         #ifdef DBUG
        //             if(printer == true){
        //                 cout << "Clock Tick " << clockticks << ": |";
        //                 printer = false;
        //             }
        //             else{
        //                 cout << "\t\t";
        //             }
        //             cout << " Process " << process << " is IO promoted" << '\n';
        //          #endif
                
        //         int pri = ioWait[i][3];
        //         if(pri + ioWait[i][5] > 99){
        //             ioWait[i][3] = 99;
        //         } else {
        //             ioWait[i][3] = pri + ioWait[i][5];
        //         }

        //         queue.insert(
        //             ioWait[i][0],
        //             ioWait[i][1],
        //             ioWait[i][2],
        //             ioWait[i][3],
        //             ioWait[i][4],
        //             ioWait[i][5]
        //         );
                
        //         ioWait.erase(ioWait.begin());
        //     }
        //    }
            
            for(int i = 0; i <= 99; i++){
                while(!queue[i].isEmpty() && queue[i].getHeadPTick()==clockticks){
                    PPtr process = queue[i].popProcess();
                    process->promoteTick = process->promoteTick + 100;

                    if(i + 10 > 99){
                        process->priority = 99;
                    } else {
                        process->priority = i + 10;
                    }

                    if(treeList.searchTree(i)==NULL){
                        treeList.insert(i);
                    }

                    queue[process->priority].insertProcess(process);

                #ifdef DBUG
                    if(printer == true){
                        cout << "Clock Tick " << clockticks << ": |";
                        printer = false;
                    }
                    else{
                        cout << "\t\t";
                    }
                    cout << " Process " << process->pid << " is promoted" << '\n';
                #endif
                }
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

    vector<Process> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);
    //cout << input.size() << endl;

    int startTime = input[0].arrival;

    cout << "Enter the time quantum: ";
    cin >> tq;
    
    scheduler(input);

    //input[1].arrival;
    // queue[1].insertProcess(&input[0]);
    // queue[1].insertProcess(&input[1]);
    // queue[1].isEmpty();
    // queue[1].printList();
    // queue[2].printList();
    
    

    
    

    //scheduler(input);
    //double endTime = scheduler(input);
    //double totalTime = endTime - startTime;
    
    //cout << "Average Turn Around Time = " << totalTime/input.size();
    //cout << "Average Turn Around Time = " << tat/input.size();
    //cout << "\t";
    //cout << "Average Wait Time = " << (totalTime - totBurst)/input.size();
}