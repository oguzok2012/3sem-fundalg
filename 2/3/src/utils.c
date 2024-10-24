#include "../include/utils.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "string.h"

#define INT_MAX 2147483647 
#define INT_MIN -2147483648
#define DBL_MAX 1.7976931348623158e+308
#define BUFFER_SIZE 256

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


Response CheckOwerflows(double* number) {
    if (*number == DBL_MAX) {
        return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow");
    }
    return CreateSuccessResponse(number);
}


Response Strstr(const char* src, const char* origin)
{
    char* src_ptr = NULL, * origin_ptr = NULL;

    if (src == NULL || origin == NULL)
        return CreateErrorResponse(ERROR_NULL_PTR, "Null pointer");

    while(*src  != '\0') {
        if(*src == *origin) {
            int trigger_out = 1;

            src_ptr = (char*)src;
            origin_ptr = (char*)origin;   

            while(*src && *origin) {
           
                trigger_out = trigger_out && (*src == *origin);
                src++;
                origin++;
            }

            if(trigger_out && *origin == '\0')
                return CreateSuccessResponse(src_ptr);
            
            origin = origin_ptr;
            src = src_ptr;
        }
        src++;
    }
    return CreateErrorResponse(ERROR_INVALID_INPUT, "Substring not found");
}

Response CountLines(FILE* file)
{
    if (file == NULL)
        return CreateErrorResponse(ERROR_NULL_PTR, "Null pointer");

    int count = 0;
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, file))
        count++;

    rewind(file);
    return CreateSuccessResponse(&count);
}