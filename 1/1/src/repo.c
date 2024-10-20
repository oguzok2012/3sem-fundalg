#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "repo.h"
#include <limits.h>


bool DivisibleNumbers(int number) {
    int found = false;
    for (int i = number; i <= 100; i += number) {
        printf("%d ", i);
        found = true;
    }
    return found;
}


bool IsPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}


void HexDigits(int number) {
    printf("%X\n", number);
}


void PowerTable(int number) {
    for (int base = 1; base <= 10; base++) {
        for (int exp = 1; exp <= number; exp++) {
            long long int result = 1;
            for (int i = 0; i < exp; i++) {
                result *= base;
            }
            printf("%2d^%-d = %-12lld", base, exp, result);
        }
        printf("\n");
    }
}


int SumNatural(int number) {
    int sum = (1 + number) * number / 2;
    return sum;
}


#define LONG_LONG_MAX 9223372036854775807LL

int will_multiply_overflow(int a, int b) {
    if (a > 0 && b > INT_MAX / a) {
        return 1;
    }
    return 0;
}


int Factorial(int number) {
    if (number < 0) {
        return 0;
    }
    int fact = 1;
    for (int i = 1; i <= number; i++) {
        if (will_multiply_overflow(i, fact)) {
            return -1;
        }
        fact *= i;
    }
    return fact;
}
