#ifndef __MATH_REPO__
#define __MATH_REPO__

#include <stdbool.h>

void SolveSingleQuadratic(double epsilon, double a, double b, double c);
void SolveQuadraticWithPermutations(double epsilon, double *coeffs);
void CheckDivisibility(int num1, int num2);
void CheckRightTriangle(double epsilon, double *sides);

#endif

