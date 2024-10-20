#ifndef __UTILS__
#define __UTILS__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "responses.h"

#define MAX_FILENAME_LENGTH 256
#define FILE_COUNT 3

Response Atoi(const char* str);
Response Atof(const char* str);
Response CheckIfTheSameFile(const char* path1, const char* path2);
Response OpenFiles(char file_names[FILE_COUNT][MAX_FILENAME_LENGTH], char *modes, FILE **files, int file_count);

#endif