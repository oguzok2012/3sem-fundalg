#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Response char_to_val(char c, int base);
char val_to_char(int val);
Response add_in_base(const char *num1, const char *num2, int base);
Response sum_in_base(int base, int num_count, ...);

#endif
