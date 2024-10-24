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

Response DichotomyMethod(double min, double max, double eps, double (*function)(double), double* result);
double equation1(double x);
double equation2(double x);

#endif
