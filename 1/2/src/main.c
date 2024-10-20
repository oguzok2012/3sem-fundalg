// printf("== Eilers's constant ==\n");
// double part_of_gamma = RowCalc(2, epsilon, NextPartGamma, 0);
// printf("\u03B3 = %f\n", part_of_gamma - (kPi * kPi / 6));


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"

#define kPi 3.141592653589793

typedef enum kOpts {
    OPT_L,
    OPT_R,
    OPT_E,
    OPT_UNKNOWN
} kOpts;



Response GetOpts(int argc, char** argv, kOpts *option, double *number) {
    if (argc != 3) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass two arguments");
    }

    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'l': *option = OPT_L; break;
            case 'r': *option = OPT_R; break;
            case 'e': *option = OPT_E; break;
            default: return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
        }
    } else {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument must be started with '-'");
    }

    double num = atof(argv[2]);
    if (num <= 0) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Epsilon can't not positive");
    }
    *number = num;
    return CreateSuccessResponse(NULL);
}


// HANDLERS

void HandlerOptL(double epsilon) {
    printf("=== Limit mode ===\n");
    printf("=== Accuracy: %e ===\n", epsilon);

    putchar('\n');

    printf("== Euler's number ==\n");
    double e = LimitCalc(epsilon, LimitCalcE);
    printf("e = %f\n", e);
    putchar('\n');

    printf("== Number PI ==\n");
    double pi = LimitCalc(epsilon, LimitCalcPi);
    printf("π = %f\n", pi);
    putchar('\n');

    printf("== The natural logarithm of two ==\n");
    double ln_2 = LimitCalc(epsilon, LimitCalcLn2);
    printf("ln2 = %f\n", ln_2);
    putchar('\n');

    printf("== Square root of two ==\n");
    double sqrt_2 = LimitCalcSqrt2(epsilon);
    printf("\u221A2 = %f\n", sqrt_2);
    putchar('\n');

    printf("== Eilers's constant ==\n");
    double gamma = LimitCalc(epsilon, LimitCalcGamma);
    printf("\u03B3 = %f\n", gamma);
}

void HandlerOptR(double epsilon) {
    printf("=== Row mode ===\n");
    printf("=== Accuracy: %e ===\n", epsilon);

    putchar('\n');

    printf("== Euler's number ==\n");
    double e = RowCalcE(epsilon);
    printf("e = %f\n", e);
    putchar('\n');

    printf("== Number PI ==\n");
    double pi = RowCalc(1, epsilon, NextPartPi, 0);
    printf("π = %f\n", pi);
    putchar('\n');

    printf("== The natural logarithm of two ==\n");
    double ln_2 = RowCalc(1, epsilon, NextPartLn2, 0);
    printf("ln2 = %f\n", ln_2);
    putchar('\n');

    printf("== Square root of two ==\n");
    double sqrt_2 = RowCalc(2, epsilon, NextPartSqrt2, 1);
    printf("\u221A2 = %f\n", sqrt_2);
    putchar('\n');

}


void HandlerOptE(double epsilon) {
    printf("=== The dichotomy mode ===\n");
    printf("=== Accuracy: %e ===\n", epsilon);

    putchar('\n');

    printf("== Euler's number ==\n");
    double e = EqCalc(2, 3, 1, EqCalcE, epsilon);
    printf("e = %f\n", e);
    putchar('\n');

    printf("== Number PI ==\n");
    double pi = EqCalcPi(epsilon);
    printf("π = %f\n", pi);
    putchar('\n');

    printf("== The natural logarithm of two ==\n");
    double ln_2 = EqCalc(0, 1, 2, EqCalcLn2, epsilon);
    printf("ln2 = %f\n", ln_2);
    putchar('\n');

    printf("== Square root of two ==\n");
    double sqrt_2 = EqCalc(1, 2, 2, EqCalcLnSqrt2, epsilon);
    printf("\u221A2 = %f\n", sqrt_2);
    putchar('\n');

    printf("== Eilers's constant ==\n");
    double value_for_gamma = LimitCalc(epsilon, LimitCalcGamma2);
    double gamma = EqCalc(1, 0, value_for_gamma, EqCalcGamma, epsilon); 
    printf("\u03B3 = %f\n", gamma);
}

// \== Handlers


int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;
    double epsilon = 0;
    
    void (*handlers[])(double) = {
        HandlerOptL,
        HandlerOptR,
        HandlerOptE,
    };
    
    Response response = GetOpts(argc, argv, &opt, &epsilon); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    handlers[opt](epsilon);
    return 0;
}
