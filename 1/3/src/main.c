#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


typedef enum kOpts {
    OPT_Q,
    OPT_M,
    OPT_T,
    OPT_UNKNOWN
} kOpts;


Response GetOpts(int argc, char** argv, kOpts *option, double *params) {
    if (argc < 3) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass at least two arguments");
    }

    int param_count; 

    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'q': 
                if (argc != 6) {
                    return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Insufficient number of arguments for flag <q> (needed 4)");
                }
                param_count = 4;
                *option = OPT_Q; 
                break;
            case 'm':
                if (argc != 4) {
                    return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Insufficient number of arguments for flag <m> (needed 2)");
                }
                param_count = 2;
                *option = OPT_M; 
                break;
            case 't': 
                if (argc != 6) {
                    return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Insufficient number of arguments for flag <t> (needed 4)");
                }
                param_count = 4;
                *option = OPT_T; 
                break;
            default: return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
        }
    } else {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument must be started with '-'");
    }

    for (int i = 0; i < param_count; ++i) {
        Response response = Atof(argv[2 + i]);
        if (response.status.code == OK) {
            params[i] = *(double*)response.data;
        } else {
            return response;
        }
    }

    if (params[0] <= 0) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Epsilon can't not positive");
    } 
    
    return CreateSuccessResponse(NULL);
}


// HANDLERS


void HandlerOptQ(double *params) {
    double epsilon = params[0];
    double coeffs[3] = {params[1], params[2], params[3]};
    SolveQuadraticWithPermutations(epsilon, coeffs);
}

void HandlerOptM(double *params) {
    CheckDivisibility(params[0], params[1]);
}

void HandlerOptT(double *params) {
    double epsilon = params[0];
    double sides[3] = {params[1], params[2], params[3]};
    CheckRightTriangle(epsilon, sides);
}


// \== Handlers


int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;
    double params[4];
    
    void (*handlers[])(double*) = {
        HandlerOptQ,
        HandlerOptM,
        HandlerOptT
    };
    
    Response response = GetOpts(argc, argv, &opt, params); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    handlers[opt](params);
    return 0;
}
