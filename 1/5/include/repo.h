#ifndef __MATH_REPO__
#define __MATH_REPO__

#include <stdbool.h>
#include "responses.h"

// Row

typedef double (*CalcFunc)(double x, double n);

double RowCalc(double x, double first_value, int start_k, double epsilon, CalcFunc next_difference);

double NextDifferenceA(double x, double n);

double NextDifferenceB(double x, double n);

double NextDifferenceC(double x, double n);

double NextDifferenceD(double x, double n);

// \== Row

#endif
