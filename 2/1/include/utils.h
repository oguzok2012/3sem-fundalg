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

size_t Strlen(const char *str);
char *Strcpy(char *dest, const char *src);
int Toupper(int c);
char *InitStr(size_t length);
Response concatStrings(const char *str1, const char *str2);
char* Strcat(char *dest, const char *src);

#endif