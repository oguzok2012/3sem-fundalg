#ifndef __MATH_REPO__
#define __MATH_REPO__

#include <stdbool.h>
#include "responses.h"

// Integral

typedef double (*CalcFunc)(double x);

double IntegralA(double x);
double IntegralB(double x);
double IntegralC(double x);
double IntegralD(double x);

double Trapez(CalcFunc f, double a, double b, double eps);


// \== Integral


#endif
