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

#define uint unsigned int

void IsConvexPolygon(int num_points, ...);
double PolynomlValue(double x, int degree, ...);
void FindKaprekarNumbers(int ase, int count, ...);

#endif
