#include "../../include/repo.h"


double PolynomlValue(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        double coefficient = va_arg(args, double);
        result = result * x + coefficient;
    }

    va_end(args);
    printf("Result: %f\n", result);
    return result;
}