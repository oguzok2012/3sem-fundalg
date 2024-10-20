#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


typedef enum kOpts {
    OPT_A,
    OPT_B,
    OPT_C,
    OPT_D,
    OPT_UNKNOWN,
} kOpts;



Response GetOpts(int argc, char** argv, kOpts *option, double *params) {
    if (argc != 4) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass two arguments. First - option. Second - x. Third - espilon");
    }

    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'a': 
                *option = OPT_A; 
                break;
            case 'b':
                *option = OPT_B; 
                break;
            case 'c': 
                *option = OPT_C; 
                break;
            case 'd':
                *option = OPT_D; 
                break;
            default: return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
        }
    } else {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument must be started with '-'");
    }


    Response r_x = Atof(argv[2]);
    if (r_x.status.code != OK) {
        return r_x;
    }
    double x = *(double*)(r_x.data);
    if (fabs(x) >= 100) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "x must be in range (-100; 100)");
    }


    Response r_e = Atof(argv[3]);
    if (r_e.status.code != OK) {
        return r_e;
    }
    double e = *(double*)(r_e.data);
    if (e <= 0) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Epsilon can't not positive");
    }

    params[0] = x;
    params[1] = e;

    return CreateSuccessResponse(NULL);
}


// HANDLERS

void HandlerOptA(double x, double epsilon) {
    printf("=== X = %f. Accuracy: %e ===\n", x, epsilon);
    double a = RowCalc(x, 1, 1, epsilon, NextDifferenceA);
    printf("a) sum = %f\n", a);
}

void HandlerOptB(double x, double epsilon) {
    printf("=== X = %f. Accuracy: %e ===\n", x, epsilon);
    double b = RowCalc(x, 1, 0, epsilon, NextDifferenceB);
    printf("b) sum = %f\n", b);
}

void HandlerOptC(double x, double epsilon) {
    if (x >= 1) {
        printf("X can't be equal or more than 1\n");
        return;
    }

    printf("=== X = %f. Accuracy: %e ===\n", x, epsilon);
    double c = RowCalc(x, 1, 0, epsilon, NextDifferenceC);
    printf("c) sum = %f\n", c);
}

void HandlerOptD(double x, double epsilon) {
    if (x >= 1) {
        printf("X can't be equal or more than 1\n");
        return;
    }

    printf("=== X = %f. Accuracy: %e ===\n", x, epsilon);
    double d = RowCalc(x, 0, 1, epsilon, NextDifferenceD);
    printf("d) sum = %f\n", d);
}



// \== Handlers


int main(int argc, char** argv) {
    double params[2];
    kOpts opt = OPT_UNKNOWN;


    void (*handlers[])(double, double) = {
        HandlerOptA,
        HandlerOptB,
        HandlerOptC,
        HandlerOptD
    };
 
    Response response = GetOpts(argc, argv, &opt, params); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    handlers[opt](params[0], params[1]);
    return 0;
}
