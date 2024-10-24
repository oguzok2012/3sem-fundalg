#include "../include/repo.h"

Response GeomMean(double *result, int count, ...) {
    if (count < 1)
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Count of numbers must be greater than 0");

    if (result == NULL)
        return CreateErrorResponse(ERROR_NULL_PTR, "Result pointer is NULL");

    *result = 1;

    va_list args;
    va_start(args, count);
    
    double number;

    for (int i = 0; i < count; i++) {   
        number = va_arg(args, double);
        
        if (isnan(number) || isinf(number)) {
            va_end(args);
            return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");
        }

        if (WillMultiplyOverflow(number, *result)) {
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow");
        }

        *result *= number;
    }

    *result = pow(*result, 1.0 / count);
    
    va_end(args);

    return CreateSuccessResponse(result);
}


Response FastPow(double* result, double base, int power) {
    if (power == 0) {
        *result = 1;
        return CreateSuccessResponse(result);
    }

    if (power == 1) {
        *result = base;
        return CreateSuccessResponse(result);
    }

    if (power < 0) {
        base = 1 / base;
        power = -power;
    }

    Response response;
    if (power % 2 == 0) {
        double tmp;
        
        response = FastPow(&tmp, base, power / 2);
        if (response.status.code != OK)
            return response;

        if (WillMultiplyOverflow(tmp, tmp)) {
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow");
        }

        *result = tmp * tmp;

    } else {
        double tmp;
        response = FastPow(&tmp, base, power - 1);
        if (response.status.code != OK)
            return response;

        if (WillMultiplyOverflow(base, tmp)) {
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow");
        }
        
        *result = base * tmp;
    }
    
    return CreateSuccessResponse(result);
}