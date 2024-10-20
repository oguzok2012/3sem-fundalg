#include "utils.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>

#define INT_MAX 2147483647 
#define INT_MIN -2147483648


Response Atoi(const char* str) {
    int result = 0;
    int sign = 1;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    if (!isdigit(*str)) {
        return CreateErrorResponse(ERROR_ATOI, "Incorrect number");
    }

    while (isdigit(*str)) {
        int digit = *str - '0';

        if (sign == 1 && (result > (INT_MAX - digit) / 10) || (sign == -1 && (result > (INT_MIN + digit) / -10))) {
            return CreateErrorResponse(ERROR_ATOI, "Number type overflow");
        }
        result = result * 10 + digit;
        str++;
        
    }

    if (*str == '.') {
        return CreateErrorResponse(ERROR_ATOI, "Number type can't be float");
    }

    if (*str != '\0' && !isspace(*str)) {
        return CreateErrorResponse(ERROR_ATOI, "Incorrect number");
    }

    result *= sign;
    return CreateSuccessResponse(&result);
}

