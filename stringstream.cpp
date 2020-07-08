// https://www.hackerrank.com/challenges/c-tutorial-stringstream/problem

#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

vector<int> parseInts(string str) {
	stringstream ss(str);
    char comma;
    vector<int> nums;
    while(ss) {
        int num = 0;
        ss >> num;
        printf("%d", num);
        nums.push_back(num);
        // printf("%d", ss.get());  // Gets the ascii number for the char, not the actual char or number
    }
    return nums;
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