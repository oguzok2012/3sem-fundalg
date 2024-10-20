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
    OPT_R,
    OPT_A,
    OPT_UNKNOWN
} kOpts;


Response GetOpts(int argc, char** argv, kOpts *option, char file_names[FILE_COUNT][MAX_FILENAME_LENGTH]) {
    if (argc < 4) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "You need to pass one flag and pathes of two or three files");
    }

    if (argv[1][0] != '-') {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Setting argument(s) must be started with '-'");
    }

    switch (argv[1][1]) {
        case 'r': 
            if (argc < 5)
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "For flag <r> you need to pass pathes to the first and the second input files and path to output file");
            
            if (strlen(argv[2]) > 255 || strlen(argv[3]) > 255 || strlen(argv[4]) > 255)
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "File names cannot contain more than 255 symbols");


            strcpy(file_names[0], argv[2]);
            strcpy(file_names[1], argv[3]);
            strcpy(file_names[2], argv[4]);

            Response r2 = CheckIfTheSameFile(file_names[0], file_names[2]);
            if (r2.status.code != OK)
                return r2;

            Response r3 = CheckIfTheSameFile(file_names[1], file_names[2]);
            if (r3.status.code != OK)
                return r3;

            *option = OPT_R; 
            break;

        case 'a':
            if (strlen(argv[2]) > 255 || strlen(argv[3]) > 255)
                return CreateErrorResponse(ERROR_READING_ARGUMENTS, "File names cannot contain more than 255 symbols");

            strcpy(file_names[0], argv[2]);
            strcpy(file_names[1], argv[3]);

            *option = OPT_A; 
            break;

        default: 
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Unknown option");
    }


    Response r1 = CheckIfTheSameFile(file_names[0], file_names[1]);
    if (r1.status.code != OK)
        return r1;

    return CreateSuccessResponse(NULL);
}


// HANDLERS


int HandlerOptR(char file_names[FILE_COUNT][MAX_FILENAME_LENGTH]) {
    FILE *files[3];
    Response r1 = OpenFiles(file_names, "rrw", files, 3);
    if (r1.status.code != OK) {
        fprintf(stderr, "%s\n", r1.status.msg);
        return 1;
    }
    Response r2 = ConcatinateLexemes(files[0], files[1], files[2]);
    if (r2.status.code != OK) {
        fclose(files[0]);
        fclose(files[1]);
        fclose(files[2]);

        fprintf(stderr, "%s\n", r2.status.msg);
        return 1;
    }

    fclose(files[0]);
    fclose(files[1]);
    fclose(files[2]);

    printf("The operation has been completed successfully\n");
}


int HandlerOptA(char file_names[FILE_COUNT][MAX_FILENAME_LENGTH]) {
    FILE *files[2];
    Response r1 = OpenFiles(file_names, "rw", files, 2);
    if (r1.status.code != OK) {
        fprintf(stderr, "%s\n", r1.status.msg);
        return 1;
    }
    Response r2 = ProcessingFile(files[0], files[1]);
    if (r2.status.code != OK) {
        fclose(files[0]);
        fclose(files[1]);

        fprintf(stderr, "%s\n", r2.status.msg);
        return 1;
    }

    fclose(files[0]);
    fclose(files[1]);

    printf("The operation has been completed successfully\n");
}


// \== Handlers


int main(int argc, char** argv) {
    kOpts opt = OPT_UNKNOWN;

    char file_names[FILE_COUNT][MAX_FILENAME_LENGTH];

    strcpy(file_names[0], "2.txt");
    strcpy(file_names[1], "4.txt");
    
    int (*handlers[])(char [FILE_COUNT][MAX_FILENAME_LENGTH]) = {
        HandlerOptR,
        HandlerOptA 
    };
    
    Response response = GetOpts(argc, argv, &opt, file_names); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }
    handlers[opt](file_names);
    return 0;
}
