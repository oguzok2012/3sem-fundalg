#include "../include/repo.h"

#include "../include/repo.h"

Response DichotomyMethod(double min, double max, double eps, double (*function)(double), double* result) {
    if (min > max)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");

    if (eps <= 0)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");

    if (function(min) * function(max) > 0)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");
    
    double mid;
    while (max - min > eps) {
        mid = (max + min) / 2.0;     
    
        if (function(mid) == 0.0) {
            *result = mid;
            return CreateSuccessResponse(result);
        }

        if (function(min) * function(mid) < 0)
            max = mid;
        else
            min = mid;
    } 

    *result = mid;

    return CreateSuccessResponse(result);
}

double equation1(double x) {
    return x * x - 2;
}

double equation2(double x) {
    return pow(x - 1, 2) / (x - 1);
}
