#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
using namespace std;

int numNegatives = 0;

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
    int numProcesses, bst, arr, pri, dline, io, tq;
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

int main(int argc,  char **argv){
    string processes=argv[1];
    vector<vector<int>> input = readInput(processes);
    print(menu(input));
    //cout << input[2][0];
    //printBurst(input);
    return 0;
}
