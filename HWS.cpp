#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

string stringLine;

int main(){
  ifstream IFILE("input.txt");

  while (getline (IFILE, stringLine)) {
    cout << stringLine;
  }


IFILE.close();
}
