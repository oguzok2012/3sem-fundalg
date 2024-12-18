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
Response CheckOwerflows(double* number);
int WillMultiplyOverflow(double a, double b);

#endif