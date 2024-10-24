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

Response HasFiniteRepresentation(int* flag, int numerator, int denominator, int base);
Response CheckFiniteRepresentation(int base, int count_fractions, ...);

#endif
