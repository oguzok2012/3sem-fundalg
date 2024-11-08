#include <stdio.h>



int main() {
    void * v;
    int a = 5;
    int b = 4;
    {
        int * c[5] = {[0] = &a, [1] = &b}; 
        v = c;
    }
    int ** n = (int **) v;
    printf("%d", *n[1]);
    return 0;
}

