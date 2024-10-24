#include "repo.h"
#include <stdarg.h>


Response CharToValue(char c, int base) {
    int val;

    if (isdigit(c)) {
        val = c - '0';
    } else if (isalpha(c)) {
        val = toupper(c) - 'A' + 10;
    } else {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect digit in number");
    }

    if (val >= base) {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect digit in number");
    }

    return CreateSuccessResponse(&val);
}


char ValueToChar(int val) {
    if (val < 10) {
        return '0' + val;
    } else {
        return 'A' + (val - 10);
    }
}

Response AddInBase(const char *num1, const char *num2, int base) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = len1 > len2 ? len1 : len2;

    char *result = (char *)malloc(max_len + 2);
    if (result == NULL) {
        return CreateErrorResponse(ERROR_MEMORY, "Memory allocation error");
    }
    result[max_len + 1] = '\0';

    int carry = 0;
    int i = len1 - 1, j = len2 - 1, k = max_len;

    while (k >= 0) {
        int sum = carry;
        
        if (i >= 0) {
            Response r_part1 = CharToValue(num1[i--], base);
            if (r_part1.status.code != OK) {
                free(result);
                return r_part1;
            }
            sum += *(int*)(r_part1.data);
        }
        if (j >= 0) {
            Response r_part2 = CharToValue(num2[j--], base);
            if (r_part2.status.code != OK) {
                free(result);
                return r_part2;
            }
            sum += *(int*)(r_part2.data);
        }

        result[k--] = ValueToChar(sum % base);
        carry = sum / base;
    }
    
    if (carry > 0) {
        result[0] = ValueToChar(carry);
        return CreateSuccessResponse(result);
    }
    
    if (result[0] == '0') {
        char *new_result = strdup(result + 1);
        free(result);
        return CreateSuccessResponse(new_result);
    }
    return CreateSuccessResponse(result);
        
}

Response SumInBase(int base, int num_count, ...) {
    if (base < 2 || base > 36) {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect base");
    }
    if (num_count <= 0) {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect number of argumnents");
    }
    
    va_list args;
    va_start(args, num_count);

    char *sum = strdup("0");
    if (sum == NULL) {
        return CreateErrorResponse(ERROR_MEMORY, "Memory allocation error");
    }

    for (int i = 0; i < num_count; i++) {
        const char *num = va_arg(args, const char *);

        Response r_new_sum = AddInBase(sum, num, base);
        if (r_new_sum.status.code != OK) {
            free(sum);
            return r_new_sum;
        }
        char *new_sum = (char*)(r_new_sum.data);
        free(sum);
        sum = new_sum;
    }

    va_end(args);

    char *start = sum; 
    while (*sum == '0' && *(sum + 1) != '\0') {
        sum++;
    }

    if (start != sum) {
        char *new_sum = strdup(sum);
        free(start);
        sum = new_sum;
    }

    return CreateSuccessResponse(sum);
}
