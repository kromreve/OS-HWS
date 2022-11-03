#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<string>> readInput(const string filename){
    string line;
    ifstream file(filename);
    vector<vector<string>> lines;
    
    while(getline(file,line)){
        vector<string> row;
        row.push_back(line);
        lines.push_back(row);
    }
    return lines;
}

void print(vector<vector<string>> input){
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            cout << input[i][j] << ' ';
        }
    }
}

void printBurst(vector<vector<string>> input){
    for(int i = 0; i < input.size(); i++){
        cout << input[i][1];
    }
}

int main(int argc,  char **argv){
    string processes=argv[1];
    vector<vector<string>> input = readInput(processes);
    //print(input);
    cout << input[0][0];
    printBurst(input);
    return 0;
}
