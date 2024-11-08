#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


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
        for (int i = 2; i < argc; i++) {
            if (strlen(argv[i]) > 255) {
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Too long string");
            }
            strcpy(argh[i - 2], argv[i]);
        }
    } else {
        Response r = Atoi(argv[2]);
        if (r.status.code != OK) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Seed must be type of int");
        }
        int seed = *(int*)r.data;
        srand(seed);
        for (int i = 3; i < argc; i++) {
            if (strlen(argv[i]) > 255) {
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Too long string");
            }
            strcpy(argh[i - 3], argv[i]);
        }
    }
    return CreateSuccessResponse(NULL);
}


// HANDLERS

int HandlerOptL(char** argh, char *output) {
    int str_len = strlen(argh[0]); 
    sprintf(output, "%d", str_len);
    return 0;
}


int HandlerOptR(char** argh, char *output) {
    char string[MAX_LENGTH];
    Strcpy(string, argh[0]);

    int left = 0;
    int right = Strlen(string) - 1;
    char temp;

    while (left < right) {
        temp = string[left];
        string[left] = string[right];
        string[right] = temp;

        left++;
        right--;
    }

    Strcpy(output, string);
    return 0;
}

int HandlerOptU(char** argh, char *output) {
    char string[MAX_LENGTH];
    Strcpy(string, argh[0]);

    for (int i = 0; i < Strlen(string); i++) {
        if (i % 2 == 1) {
            output[i] = Toupper(string[i]);
        } else {
            output[i] = string[i];
        }
    }
    return 0;
}

int HandlerOptN(char** argh, char *output) {
    char string[MAX_LENGTH];
    Strcpy(string, argh[0]);

    char *digits = InitStr(MAX_LENGTH);
    char *letters = InitStr(MAX_LENGTH);
    char *others = InitStr(MAX_LENGTH);

    if (digits == NULL || letters == NULL || others == NULL) {
        fprintf(stderr, "%s\n", "Memory allocation error");
        return 1;
    }

    int digitIndex = 0;
    int letterIndex = 0;
    int otherIndex = 0;

    for (int i = 0; i < Strlen(string); i++) {
        char c = string[i];
        if (c >= '0' && c <= '9') {
            digits[digitIndex++] = c;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            letters[letterIndex++] = c;
        } else {
            others[otherIndex++] = c;
        }
    }

    digits[digitIndex] = '\0';
    letters[letterIndex] = '\0';
    others[otherIndex] = '\0';

    Response concatenated = concatStrings(digits, letters);
    if (concatenated.status.code != OK) {
        fprintf(stderr, "%s\n", concatenated.status.msg);
        return 1;
    }

    Response final_result = concatStrings(concatenated.data, others);
    if (final_result.status.code != OK) {
        fprintf(stderr, "%s\n", final_result.status.msg);
        free(concatenated.data);
        return 1;
    }

    Strcpy(output, final_result.data);

    free(concatenated.data);
    free(final_result.data);
    free(digits);
    free(letters);
    free(others);

    return 0;
}


int HandlerOptC(char** argh, char *output) {
    char *result = InitStr(MAX_LENGTH * MAX_STRINGS);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error");
        return 1;
    } 
    int num_strings = 0;
    
    while (argh[num_strings][0] != '\0') {
        num_strings++;
    }
    
    int indices[num_strings];
    for (int i = 0; i < num_strings; i++) {
        indices[i] = i;
    }

    for (int i = num_strings - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < num_strings; i++) {
        Strcat(result, argh[indices[i]]);
        Strcat(result, " ");
    }

    Strcpy(output, result);
    return 0;
}

// \== Handlers


int main(int argc, char *argv[]) {

    kOpts opt = OPT_UNKNOWN;
    DECLARE_STRING_ARRAY(argh, MAX_STRINGS)

    int (*handlers[])(char **argh, char *output) = {
        HandlerOptL,
        HandlerOptR,
        HandlerOptU,
        HandlerOptN,
        HandlerOptC
    };
    
    Response response = GetOpts(argc, argv, &opt, argh); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    char *output = InitStr(MAX_LENGTH);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    if (handlers[opt](argh, output) != 0) {
        return 1;
    }
    printf("output: %s\n", output);
    return 0;
}
