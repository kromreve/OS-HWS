#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

string stringLine;

void extractInts(string str) {
  stringstream ss;
  ss << str;
  string tmp;
  int found;
  while (!ss.eof()) {
    ss >> tmp;
    if (stringstream(tmp) >> found)
      cout << found << ", ";

    tmp = " ";
  }
}

int main(){
  ifstream IFILE("input.txt");

  while (getline (IFILE, stringLine)) {
    extractInts(stringLine);
    return 0;
  }


IFILE.close();
}
