#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>


#define MAX_STRINGS 256
#define MAX_LENGTH 100

#define DECLARE_STRING_ARRAY(name, size) \
    char name##Strings[size][MAX_LENGTH]; \
    char *name[size]; \
    for (int i = 0; i < size; i++) { name[i] = name##Strings[i]; }

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
        case 'r':
            *option = OPT_R;
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

int HandlerOptL(char** argh, char *output) {
    int str_len = strlen(argh[0]); 
    sprintf(output, "%d", str_len);
}


int HandlerOptR(char** argh, char *output) {
    char string[MAX_LENGTH];
    strcpy(string, argh[0]);

    int left = 0;
    int right = strlen(string) - 1;
    char temp;

    while (left < right) {
        temp = string[left];
        string[left] = string[right];
        string[right] = temp;

        left++;
        right--;
    }

    strcpy(output, string);
}


int HandlerOptU(char** argh, char *output) {
    char string[MAX_LENGTH];
    strcpy(string, argh[0]);

    for (int i = 0; i < strlen(string); i++) {
        if (i % 2 == 1) {
            output[i] = toupper(string[i]);
        } else {
            output[i]
        }
    }
}


// \== Handlers


int main(int argc, char **argv) {

    kOpts opt = OPT_UNKNOWN;
    DECLARE_STRING_ARRAY(argh, MAX_STRINGS)

    int (*handlers[])(char **argh, char *output) = {
        HandlerOptL,
        HandlerOptR,
    };
    
    Response response = GetOpts(argc, argv, &opt, argh); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    char output[MAX_LENGTH];
    handlers[opt](argh, output);

    printf("output: %s\n", output);
    return 0;
}
