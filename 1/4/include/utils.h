#ifndef __UTILS__
#define __UTILS__

#include "responses.h"

Response Atoi(const char* str);
Response Atof(const char* str);
void Swap(double* nums, int i, int j);
int FindNextPermutation(double *nums, int n);
void SortThreeNumbers(double* nums);
void create_new_filename(char *input_file_name, char *output_file_name);

#endif