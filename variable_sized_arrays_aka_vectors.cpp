// https://www.hackerrank.com/challenges/variable-sized-arrays/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n = 0;
    int q = 0;
    int numElements = 0;
    int temp = 0;
    int q1 = 0;
    int q2 = 0;
    cin >> n >> q;
    vector< vector<int> > a(n);  // 2D array to hold data, sized for n number of sub-vectors
    
    // Get array elements to be queried
    for (int i = 0; i < n; i++) {
        cin >> numElements; // Number of array elements in this line
        for (int j = 0; j < numElements; j++) {
            cin >> temp;  // Collect the nested vector elements from stdin
            a[i].push_back(temp);
        }
    }

    // Get and print queries
    for (int i = 0; i < q; i++) {
        cin >> q1 >> q2;  // Get the guaranteed 2 query elements
        printf("%d\n", a[q1][q2]);
    }

    return 0;
}