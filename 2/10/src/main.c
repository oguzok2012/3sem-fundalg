#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>


int main() {
    int n = 3; 
    double epsilon = 0.000001;
    double a = 1.0;

    double* result = NULL;
    taylor_series(epsilon, a, &result, n, 1.0, 2.0, 3.0, 4.0);


    printf("Coeffs:\n");
    for (int i = 0; i <= n; i++) {
        printf("g%d = %f\n", i, result[i]);
    }

    free(result);
    return 0;
}