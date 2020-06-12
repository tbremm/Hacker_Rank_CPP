// https://www.hackerrank.com/challenges/arrays-introduction/problem

#include <cstdio>
#include <iostream>
using namespace std;


int main() {
    int num_ints = 0;
    cin >> num_ints;
    int arr[num_ints];
    for (int i = 0; i < num_ints; i++){
        cin >> arr[i];
    }

    for (int j = num_ints - 1; j >= 0; j--) {
        if (j == 0) {
            printf("%d", arr[j]);
            break;
        }
        printf("%d ", arr[j]);
    }

    return 0;
}
