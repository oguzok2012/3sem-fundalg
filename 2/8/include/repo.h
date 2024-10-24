#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Response CharToValue(char c, int base);
char ValueToChar(int val);
Response AddInBase(const char *num1, const char *num2, int base);
Response SumInBase(int base, int num_count, ...);

#endif
