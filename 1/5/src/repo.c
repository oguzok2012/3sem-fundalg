#include "repo.h"
#include <math.h>
#include <stdio.h>
#include "responses.h"


// Row

double NextDifferenceA(double x, double n) {
    return x / n;
}

double NextDifferenceB(double x, double n) {
    return -x * x / (2 * n + 2) / (2 * n + 1);
}

double NextDifferenceC(double x, double n) {
    return (double)27 * pow((n + 1.0), 3.0) * x * x / (double)(3.0 * n + 3.0) / (double)(3.0 * n + 2.0) / (double)(3.0 * n + 1.0);
    //return ((9 * n * n * x * x) + (18 * n * x * x) + (9 * x * x)) / (9 * n * n + 9 * n + 2);
}

double NextDifferenceD(double x, double n) {
    return -1 * x * x * (2 * n - 1) / (2 * n);
}


double RowCalc(double x, double first_value, int start_k, double epsilon, CalcFunc next_difference) {
    double result = first_value;
    int k = start_k;
    double part = 1;

    do {
        part *= next_difference(x, k);
        result += part;
        k++;        
    } while (fabs(part) > epsilon);

    return result;
}


// \== Row


