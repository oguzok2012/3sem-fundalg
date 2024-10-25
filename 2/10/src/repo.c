#include "../include/repo.h"


double factorial(int n) {
    if (n == 0) return 1.0;
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}


double polynomial_derivative(int order, double a, int n, const double *coeffs) {
    double result = 0.0;

    for (int j = order; j <= n; j++) {
        double term = coeffs[j];
        for (int k = 0; k < order; k++) {
            term *= (j - k);
        }
        result += term * pow(a, j - order);
    }
    return result;
}

void taylor_series(double epsilon, double a, double** result, int degree, ...) {
    *result = (double*) malloc((degree + 1) * sizeof(double));

    va_list args;
    va_start(args, degree);

    double *coeffs = (double*) malloc((degree + 1) * sizeof(double));
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = va_arg(args, double);
    }

    double *g = *result;

    for (int i = 0; i <= degree; i++) {
        g[i] = polynomial_derivative(i, a, degree, coeffs) / factorial(i);
        if (fabs(g[i]) < epsilon) {
            g[i] = 0.0;
        }
    }

    free(coeffs);
    va_end(args);
}

