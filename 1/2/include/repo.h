#ifndef __MATH_REPO__
#define __MATH_REPO__

#include <stdbool.h>
#include "responses.h"


// Limit
typedef Response (*CalcFuncLimit)(int n);

Response LimitCalcE(int n);
Response LimitCalcPi(int n);
Response LimitCalcLn2(int n);
Response LimitCalcGamma(int n);
Response LimitCalcGamma2(int t);

double LimitCalc(double epsilon, CalcFuncLimit calc_func);
double LimitCalcSqrt2(double n);

// \== Limit


// Row

typedef double (*CalcFunc)(double n);

double NextPartSqrt2(double n);
double NextPartPi(double n);
double NextPartLn2(double n);
double NextPartGamma(double k);

double RowCalc(int start_k, double epsilon, CalcFunc next_part_func, int use_product);
double RowCalcE(double epsilon);

// \== Row

// Eq

double EqCalc(double left, double right, double value, CalcFunc calc_func, double epsilon);
double EqCalcPi(double epsilon);

double EqCalcE(double x);
double EqCalcLn2(double x);
double EqCalcLnSqrt2(double x);
double EqCalcGamma(double x);


#endif
