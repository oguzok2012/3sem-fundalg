#include "../include/repo.h"

Response HasFiniteRepresentation(int* flag, int numerator, int denominator, int base) {
    if (denominator == 0)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");
    
    if (base == 0)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");

    if (numerator == 0)
        return CreateSuccessResponse(NULL);

    Response GcdResponse = Gcd(numerator, denominator);
    if (*(int*)(GcdResponse.data) == 1)
        return CreateSuccessResponse(NULL);

    int common_divisor = *(int *)(GcdResponse.data);
    numerator /= common_divisor;
    denominator /= common_divisor; 

    while (denominator % base == 0)
        denominator /= base;

    for (int i = 2; i <= base; i++) {
        if (base % i == 0) {
            while (denominator % i == 0) {
                denominator /= i;
            }   
        }
    }

    if (denominator == 1) {
        *flag = 1;
        return CreateSuccessResponse(NULL);
    }

    return CreateSuccessResponse(NULL);
}

Response CheckFiniteRepresentation(int base, int count_fractions, ...) {
    va_list args;
    va_start(args, count_fractions);

    for (int i = 0; i < count_fractions; i++) {
        double fraction = va_arg(args, double);
        
        double numerator = fraction;
        double denominator = 1;

        while (numerator != floor(numerator)) {
            numerator *= 10;
            denominator *= 10;
        }

        int flag = 0;

        Response r = HasFiniteRepresentation(&flag, numerator, denominator, base);

        if (r.status.code != OK) {
            va_end(args);
            return r;
        }  

        if (flag == 1)
            printf("Fraction %f has finite representation in base %d\n", fraction, base);
        else
            printf("Fraction %f doesn't have infinite representation in base %d\n", fraction, base);
    }

    va_end(args);

    return CreateSuccessResponse(NULL);
}

