#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>


void polynoml_value(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        double coefficient = va_arg(args, double);
        result = result * x + coefficient;
    }

    va_end(args);
    printf("Result: %f\n", result);
}


void calc(double* coeffs, int degree, double a, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x - a, i);
    }
    printf("Result: %f\n", result);
}


int main() {
    int n = 3; 
    double epsilon = 0.000001;
    double a = 1.0;

    polynoml_value(2, 3, 4.0, 3.0, 2.0, 1.0);

    double* result = NULL;
    if (taylor_series(epsilon, a, &result, n, 1.0, 2.0, 3.0, 4.0) != 0) {
        return 1;
    }


    printf("Coeffs:\n");
    for (int i = 0; i <= n; i++) {
        printf("g%d = %f\n", i, result[i]);
    }

    calc(result, 3, 1, 2);
    free(result);
    return 0;
}