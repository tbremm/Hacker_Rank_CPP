#include <iostream>
#include <cstdio>
using namespace std;

// https://www.hackerrank.com/challenges/c-tutorial-basic-data-types/problem

int main() {
    int i;
    long l;
    char c;
    float f;
    double d;

    scanf("%d %ld %c %f %lf", &i, &l, &c, &f, &d);

    printf("%d\n%ld\n%c\n%.3f\n%.9lf", i, l, c, f, d);

    return 0;
}