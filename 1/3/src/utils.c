#include "utils.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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

    // Process integer part
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


void SortThreeNumbers(double* nums) {
    if (nums[0] > nums[1]) {
        Swap(nums, 0, 1);
    }
    if (nums[0] > nums[2]) {
        Swap(nums, 0, 2);
    }
    if (nums[1] > nums[2]) {
        Swap(nums, 1, 2);
    }
}


void Swap(double* nums, int i, int j) {
    double temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}


// вначале передается отсортированный по возрастанию массив
int FindNextPermutation(double *nums, int n) {
    int j = n - 2;
    // ищем первый элемент, который меньше, чем правый сосед
    while (j != -1 && nums[j] >= nums[j + 1]) {
	    j--;
    }
    if (j == -1) {
        return 0; // больше перестановок нет
    }

    // ищем от левого конца первый элемент, больший, чем nums[j]
    int k = n - 1;
    while (nums[j] >= nums[k]) {
	    k--;
    }
    Swap(nums, j, k);

    // теперь сортируем повозрастанию от j + 1 оставшуюся часть последовательности
    // тк из-за первого цикла в функции while мы проверили элементы упорядоченность, нужно просто сделать реверс
    int l = j + 1, r = n - 1; 
    while (l < r) {
	    Swap(nums, l++, r--);
    }
    return 1;
}