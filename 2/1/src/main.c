#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define FILE_COUNT 3


typedef enum kOpts {
    OPT_L,
    OPT_R,
    OPT_U,
    OPT_N,
    OPT_C,
    OPT_UNKNOWN
} kOpts;


Response GetOpts(int argc, char** argv, kOpts *option, char **argh) {
    if (argc < 3) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass one flag and at least one string");
    }

    if (argv[1][0] != '-') {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument(s) must be started with '-'");
    }

    switch (argv[1][1]) {
        case 'l': 
            *option = OPT_L;
            break;
        case 'u':
            *option = OPT_U;
            break;
        case 'n':
            *option = OPT_N;
            break;
        case 'c':
            *option = OPT_C;
            break;
        
        default: 
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
    }

    if (*option != OPT_C) {
        if (strlen(argv[2]) > 255) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Too long string");
        }
        strcpy(argh[0], argv[2]);
    } else {
        Response r = Atoi(argv[2]);
        if (r.status.code != OK) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Seed must be type of unsigned int");
        }
        int seed = *(int*)r.data;
        if (seed <= 0 ) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Seed cant be not positive");
        }
        strcpy(argh[0], argv[2]);
        for (int i = 3; i < argc; i++) {
            if (strlen(argv[i]) > 255) {
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Too long string");
            }
            strcpy(argh[i - 2], argv[i]);
        }
    }
    return CreateSuccessResponse(NULL);
}


// HANDLERS

int HandlerOptL(char** argh) {
    printf("\n");
    printf("\n");
}


int HandlerOptC(char** argh) {
    printf("\n");
    printf("\n");
}

// \== Handlers


int main(int argc, char **argv) {

    kOpts opt = OPT_UNKNOWN;

    char *(argh[256]);

    
    int (*handlers[])(char **argh) = {
        HandlerOptL,
        HandlerOptC 
    };
    
    Response response = GetOpts(argc, argv, &opt, argh); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }
    handlers[opt](argh);
    return 0;
}
