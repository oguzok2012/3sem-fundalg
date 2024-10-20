#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


Response GetOpts(int argc, char** argv, double *params) {
    if (argc != 2) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass one argumnet - epsilon.");
    }

    Response r_e = Atof(argv[1]);
    if (r_e.status.code != OK) {
        return r_e;
    }
    double e = *(double*)(r_e.data);
    if (e <= 0) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Epsilon can't not positive");
    }

    params[0] = e;

    return CreateSuccessResponse(NULL);
}


// Handlers

void Handler(double epsilon) {
    printf("=== Accuracy: %e ===\n", epsilon);

    double integral_a = Trapez(IntegralA, 0, 1, epsilon);
    printf("a) Integral of ln(1+x)/x from 0 to 1 = %.12f\n", integral_a);

    double integral_b = Trapez(IntegralB, 0, 1, epsilon);
    printf("b) Integral of e^(-x^2/2) from 0 to 1 = %.12f\n", integral_b);

    double integral_c = Trapez(IntegralC, 0, 1 - epsilon, epsilon);
    printf("c) Integral of ln(1/(1-x)) from 0 to 1 = %.12f\n", integral_c);

    double integral_d = Trapez(IntegralD, 0, 1, epsilon);
    printf("d) Integral of x^x from 0 to 1 = %.12f\n", integral_d);
    
}

// \== Handlers


int main(int argc, char** argv) {
    double params[1];
    
    Response response = GetOpts(argc, argv, params); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }
    Handler(params[0]);
    return 0;
}
