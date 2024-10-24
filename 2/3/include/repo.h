#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define BUFFER_SIZE 256

typedef struct {
    int line_number;
    int position;
} MATCH;

Response FindSubstringInFile(FILE* input_file, const char* substring, MATCH* matches);
Response GetMatches(const char* substring, int count_files, ...);

Response ValidateInput(const char* substring, int count_files);
Response ProcessFile(char* file_name, const char* substring);
Response PrintMatches(char* file_name, MATCH* matches, int max_count_matches);



#endif
