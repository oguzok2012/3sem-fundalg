#include "../include/utils.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "string.h"

#define INT_MAX 2147483647 
#define INT_MIN -2147483648
#define DBL_MAX 1.7976931348623158e+308



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


Response Atof(const char* str) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int divisor = 1;
    bool has_fraction = false;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    if (!isdigit(*str) && *str != '.') {
        return CreateErrorResponse(ERROR_ATOF, "Incorrect number");
    }

    while (isdigit(*str)) {
        int digit = *str - '0';

        if (sign == 1 && result > (DBL_MAX - digit) / 10) {
            return CreateErrorResponse(ERROR_ATOF, "Number type overflow");
        }
        result = result * 10 + digit;
        str++;
    }

    if (*str == '.') {
        has_fraction = true;
        str++;
        while (isdigit(*str)) {
            int digit = *str - '0';
            if (sign == 1 && result > (DBL_MAX - digit) / 10) {
                return CreateErrorResponse(ERROR_ATOF, "Number type overflow");
            }
            fraction = fraction * 10 + digit;
            divisor *= 10;
            str++;
        }
    }

    if (has_fraction) {
        result += fraction / divisor;
    }

    if (*str != '\0' && !isspace(*str)) {
        return CreateErrorResponse(ERROR_ATOF, "Incorrect number");
    }

    result *= sign;
    return CreateSuccessResponse(&result);
}


int WillMultiplyOverflow(double a, double b) {
    if (a > 0 && b > DBL_MAX / a) {
        return 1;
    }
    return 0;
}
