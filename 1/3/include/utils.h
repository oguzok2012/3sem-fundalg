#ifndef __UTILS__
#define __UTILS__

#include "responses.h"

Response Atoi(const char* str);
Response Atof(const char* str);
void Swap(double* nums, int i, int j);
int FindNextPermutation(double *nums, int n);
void SortThreeNumbers(double* nums);

#endif