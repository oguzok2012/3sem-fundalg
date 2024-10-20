#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>


typedef enum kOpts {
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A,
    OPT_UNKNOWN
} kOpts;


Response GetOpts(int argc, char** argv, kOpts *option, char *input_file_name, char *output_file_name) {
    if (argc < 3) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass at least one flag and path to input file");
    }

    if (strlen(argv[2]) > 255) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "File name cannot contain more than 255 symbols");
    }

    strcpy(input_file_name, argv[2]);

    if (argv[1][0] != '-') {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument(s) must be started with '-'");
    }

    int flag_number = strlen(argv[1]) - 1;

    if (!(flag_number == 1 || flag_number == 2)) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You can't set more than two flags");
    }

    int id_opt = 1;
    if (flag_number == 2) {
        int id_n = -1;
        for (int i = 1; i < flag_number + 1; i++) {
            if (argv[1][i] == 'n') {
                id_n = i;
                break;
            }
        }
        if (id_n == -1) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "When setting two flags, the <n> flag is mandatory");
        }
        if (argc < 4) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "When setting the <n> flag, you must pass the output file name as 3nd argument");
        }

        strcpy(output_file_name, argv[3]);
        id_opt = 3 - id_n;
    }

    switch (argv[1][id_opt]) {
        case 'd':
            *option = OPT_D; 
            break;
        case 'i':
            *option = OPT_I; 
            break;
        case 's':
            *option = OPT_S; 
            break;
        case 'a':
            *option = OPT_A; 
            break;
        default:
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
    }

    if (flag_number == 1) {
        create_new_filename(input_file_name, output_file_name);
    }
    
    return CreateSuccessResponse(NULL);
}


// HANDLERS



int HandlerOptD(char *input_file_name, char *output_file_name) {
    Response r = ExcludeArabicNumerals(input_file_name, output_file_name);
    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }
    printf("Operation completed successfully.\n");
}

int HandlerOptI(char *input_file_name, char *output_file_name) {
    Response r = CountLatinLetters(input_file_name, output_file_name);
    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }
    printf("Operation completed successfully.\n");
}

int HandlerOptS(char *input_file_name, char *output_file_name) {
    Response r = CountSpecialSymbols(input_file_name, output_file_name);
    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }
    printf("Operation completed successfully.\n");
}

int HandlerOptA(char *input_file_name, char *output_file_name) {
    Response r = ReplaceNonDigitWithAsciiHex(input_file_name, output_file_name);
    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }
    printf("Operation completed successfully.\n");
}


// \== Handlers


int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;
    char input_file_name[256];
    char output_file_name[256];
    
    int (*handlers[])(char*, char*) = {
        HandlerOptD,
        HandlerOptI,
        HandlerOptS,
        HandlerOptA
    };
    
    Response response = GetOpts(argc, argv, &opt, input_file_name, output_file_name); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    handlers[opt](input_file_name, output_file_name);
    return 0;
}
