// https://www.hackerrank.com/challenges/c-tutorial-pointer/problem

#include <stdio.h>
#include <cmath>

void update(int *a,int *b) {
    int temp_a = 0;
    temp_a = *a + *b;
    *b = std::abs(*a - *b);
    *a = temp_a;
    return;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}