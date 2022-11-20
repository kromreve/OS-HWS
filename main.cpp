#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <queue>
#include <algorithm>
#include "RedBlackTree.h"
#include "QueueList.h"
#include "LinkedList.h"

#define DBUG

using namespace std;

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

int main(int argc,  char **argv) {
    int tq;
    Linkedlist queues[100];
    for (int i = 0; i<= 100; i++) {
        queues[i] = new Linkedlist(i);
    }
    

    cout << "Enter the time quantum: ";
    cin >> tq;

    

    string processes=argv[1];

    vector<vector<int>> input = readInput(processes);
    
    sort(input.begin(), input.end(), compareArrival);

    for (int i = 0; i < input.size(); i++) {
        queues[0].insertNode(
            input[i][0],
            input[i][1],
            input[i][2],
            input[i][3],
            input[i][4],
            input[i][2]+100,
        );
    }
    queues[0].printList();
    

    return 0;
}
