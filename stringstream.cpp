// https://www.hackerrank.com/challenges/c-tutorial-stringstream/problem

#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

vector<int> parseInts(string str) {
	stringstream ss(str);
    vector<int> out;
    int num = 0;
    char comma;
    while (!ss.eof()) {
        if (ss.peek() != ',') {
            ss >> num;
            out.push_back(num);
        } else {
            ss >> comma;  // Who cares
        }
    }
    return out;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}