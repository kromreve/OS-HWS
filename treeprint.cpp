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

bool compareArrival(vector<int> a, vector<int> b) {
		if (a[2] < b[2]) {
				return 1;
		}
		else {
				return 0;
		}
}


int main(int argc,  char **argv) {
    RBTree queue;
    string processes=argv[1];
    int tq;

    vector<vector<int>> input = readInput(processes);
    sort(input.begin(), input.end(), compareArrival);

    cout << "Enter the time quantum: ";
    cin >> tq;

    for (int i=0; i<=input.size()-numNegatives; i++) {
        //cout << "inserting " << i << endl; 
        queue.insert(
            input[i][0],
            input[i][1],
            input[i][2],
            input[i][3],
            input[i][4],
            input[i][5]
        );
    }
    //cout << "insert is passed" <<endl;
    queue.formatPrint();

    cout << "Address of Node 5038: " << queue.searchTree(5038) << endl;

    queue.deleteNode(queue.searchTree(5038));

    queue.formatPrint();

    return 0;
}