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

void taylor_series(double epsilon, double a, double** result, int degree, ...);

#endif
