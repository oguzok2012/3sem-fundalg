#include "../../include/repo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>


int ParseToDecimal(const char *str, int base) {
    int num = 0;
    while (*str) {
        int value;

        if (*str >= '0' && *str <= '9') {
            value = *str - '0';

        } else if (*str >= 'A' && *str <= 'Z') {
            value = *str - 'A' + 10;

        } else if (*str >= 'a' && *str <= 'z') {
            value = *str - 'a' + 10;

        } else {
            return -1;
        }

        if (value >= base) {
            return -1;
        }
        if (WillMultiplyOverflow(num, base)) {
            return -1;
        }
        num = num * base + value;
        str++;
    }
    return num;
}


void ConvertFromDecimal(int num, int base, char *result) {
    char temp[65];
    int index = 0;

    do {
        int remainder = num % base;
        temp[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        num /= base;
    } while (num > 0);

    for (int i = 0; i < index; i++) {
        result[i] = temp[index - i - 1];
    }
    result[index] = '\0';
}


bool IsKaprekar(int num, int base) {
    if (num == 1) return true;

    int square = num * num;
    char square_str[65];
    ConvertFromDecimal(square, base, square_str);

    int len = strlen(square_str);
    for (int i = 1; i < len; i++) {
        char left_str[65], right_str[65];

        strncpy(left_str, square_str, i);
        left_str[i] = '\0';

        strcpy(right_str, square_str + i);

        int left = ParseToDecimal(left_str, base);
        int right = ParseToDecimal(right_str, base);

        if (right > 0 && left + right == num) {
            return true;
        }
    }
    return false;
}

void FindKaprekarNumbers(int base, int num_count, ...) {
    va_list args;
    va_start(args, num_count);

    printf("Kaperkar numbers in base %d: ", base);

    int found = 0;

    for (int i = 0; i < num_count; i++) {
        const char *num_str = va_arg(args, const char *);
        int num = ParseToDecimal(num_str, base);
        if (num < 0) {
            fprintf(stderr, "Invalid number was given");
            return;
        }
        
        if (IsKaprekar(num, base)) {
            printf("%s ", num_str);
            found = 1;
        }
    }
    if (!found) {
        printf("/u2205");
    }
    putchar('\n');

    va_end(args);
}

