#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F,
    OPT_UNKNOWN
} kOpts;


Response GetOpts(int argc, char** argv, kOpts *option, int *number) {
    if (argc != 3) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass two arguments");
    }

    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'h': *option = OPT_H; break;
            case 'p': *option = OPT_P; break;
            case 's': *option = OPT_S; break;
            case 'e': *option = OPT_E; break;
            case 'a': *option = OPT_A; break;
            case 'f': *option = OPT_F; break;
            default: return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
        }
    } else {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument must be started with '-'");
    }

    Response response = Atoi(argv[2]);
    if (response.status.code == OK) {
        *number = *(int*)response.data;
        return CreateSuccessResponse(NULL);
    }
    return response;
}


// HANDLERS

void HandlerOptH(int x) {
    printf("Natural numbers divisible by %d up to 100:\n", x);
    bool found = DivisibleNumbers(x);
    if (!found) {
        printf("No numbers divisible by %d in the range [1, 100]", x);
    }
    printf("\n");
}

void HandlerOptP(int number) {
    if (number < 2) {
        printf("%d is not prime and not composite.\n", number);
    } else if (IsPrime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is a composite number.\n", number);
    }
}

void HandlerOptS(int number) {
    printf("Hexadecimal digits of %d are: ", number);
    HexDigits(number);
}

void HandlerOptE(int number) {
    if (number < 1) {
        printf("Number is too small for this operation (max 10).\n");
        return;
    }
    if (number > 10) {
        printf("Number is too large for this operation (max 10).\n");
        return;
    }
    printf("Power table for numbers 1 to 10, raised to powers from 1 to %d:\n", number);
    PowerTable(number);
}

void HandlerOptA(int number) {
    printf("Sum of natural numbers from 1 to %d is %d\n", number, SumNatural(number));
}

void HandlerOptF(int number) {
    int fact = Factorial(number);
    if (fact == -1) {
        printf("MAX INT overflow.\n");
        return;
    }
    if (fact == 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return;
    }
    printf("Factorial of %d is %d\n", number, Factorial(number));
}

// \== Handlers


int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;
    int procceed_number = 0;
    
    void (*handlers[])(int) = {
        HandlerOptH,
        HandlerOptP,
        HandlerOptS,
        HandlerOptE,
        HandlerOptA,
        HandlerOptF
    };
    
    Response response = GetOpts(argc, argv, &opt, &procceed_number); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    handlers[opt](procceed_number);
    return 0;
}
