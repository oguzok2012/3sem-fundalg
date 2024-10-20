#include "repo.h"
#include <math.h>
#include <stdio.h>
#include "responses.h"

#define LONG_LONG_MAX 9223372036854775807LL

int will_multiply_overflow(long long a, long long b) {
    if (a > 0 && b > LONG_LONG_MAX / a) {
        return 1;
    }
    return 0;
}

long long Factorial(int number) {
    if (number < 0) {
        return 0;
    }
    long long fact = 1;
    for (int i = 1; i <= number; i++) {
        if (will_multiply_overflow(i, fact)) {
            return -1;
        }
        fact *= i;
    }
    return fact;
}


Response BinomCoeff(int n, int k) {
    long long numeral = Factorial(n);
    if (numeral == -1) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    long long divide1 = Factorial(k);
    if (divide1 == -1) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    long long divide2 = Factorial(n - k);
    if (divide2 == -1) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    double res = numeral / divide1 / divide2;
    return CreateSuccessResponse(&res);
}


// Limit

Response LimitCalcE(int n) {
    double r = pow(1.0 + 1.0 / n, n);
    return CreateSuccessResponse(&r);
}

Response LimitCalcPi(int n) {
    long long d1 = Factorial(2 * n);
    if (d1 == -1) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    long long n1 = Factorial(n - 1);
    if (n1 == -1) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    double n2 = pow(16, n);

    if (isinf(n2)) {
        return CreateErrorResponse(ERROR_OVERFLOW, "double type overflow");
    }

    if (will_multiply_overflow(n1, n2)) {
        return CreateErrorResponse(ERROR_OVERFLOW, "long long type overflow");
    }

    long long n12 = n1 * n2;

    double n3 = pow(Factorial(n), 3);
    if (isinf(n3)) {
        return CreateErrorResponse(ERROR_OVERFLOW, "double type overflow");
    }

    double r = (double)n12 / d1 * n3 / d1;
    return CreateSuccessResponse(&r);
}


Response LimitCalcLn2(int n) {
    double r = n * (pow(2, 1.0 / n) - 1); 
    return CreateSuccessResponse(&r);
}

Response LimitCalcGamma(int n) {
    n += 1;
    double summa = 0;
    for (int k = 1; k <= n; k++) {
        Response r = BinomCoeff(n, k);
        if (r.status.code != OK) {
            return r;
        }
        double b_coeff = *(double*)(r.data);
        int sign = (k % 2 == 0) ? 1 : -1;
        long long k_fact = Factorial(k);
        summa += (b_coeff / k * log(k_fact) * sign);
    }
    return CreateSuccessResponse(&summa);
}


void SieveOfEratosthenes(bool *arr, int n) {
     for (int p = 2; p * p <= n; p++) {
        if (arr[p] == true) {
            for (int i = p * p; i <= n; i += p) {
                arr[i] = false;
            }
        }
    }
}


Response LimitCalcGamma2(int t) {
    t += 2;
    bool primes[t + 1];

    for (int i = 0; i <= t; i++) {
        primes[i] = true;
    }

    SieveOfEratosthenes(primes, t);

    double product = 1;
    for (int i = 2; i < t + 1; i++) {
        if (primes[i] == true) {        
            product *= ((double)(i - 1) / (double)i);
        }
    }

    double r = log(t) * product;
    return CreateSuccessResponse(&r);
}


double LimitCalc(double epsilon, CalcFuncLimit calc_func) {
    double curr = 1.0, prev = 0.0;
    int n = 1;
    do {
        Response r = calc_func(n);
        if (r.status.code != OK) {
            printf("Maximum accuracy = %f\n", fabs(curr - prev));
            return prev;
        }
        prev = curr;
        curr = *(double*)(r.data);
        n++;
    } while (fabs(curr - prev) > epsilon);
    
    return curr;
}


double LimitCalcSqrt2(double epsilon) {
    double curr = 0.0, prev = -0.5;

    while (true) {
        curr =  prev - (prev * prev / 2) + 1;
        if (fabs(curr - prev) < epsilon) {
            break;
        }
        prev = curr;
    }
    return curr;
}


// \== Limit


// Row

double NextPartSqrt2(double k) {
    return pow(2, pow(2, -k));
}

double NextPartPi(double n) {
    return (pow(-1, n - 1) / (2 * n - 1)) * 4;
}

double NextPartLn2(double n) {
    return pow(-1, n - 1) / n;
}

double NextPartGamma(double k) {
    double rounded_sqrt_k = (long long)floor(sqrt(k));
    double r = (1.0 / (pow(floor(sqrt(k)), 2))) - (1.0 / k);
    //printf("%d. %f\n", (int)k, r);
    return r;
}


double RowCalc(int start_k, double epsilon, CalcFunc next_part_func, int use_product) {
    double result = (use_product) ? 1.0 : 0.0;
    epsilon = (use_product) ? epsilon + 1 : epsilon;
    double part;
    int k = start_k;

    do {
        part = next_part_func(k);
        if (use_product) {
            result *= part;
        } else {
            result += part;
        }
        k++;        
    } while (fabs(part) > epsilon);

    return result;
}


double RowCalcE(double epsilon) {
    double e = 1.0, part = 1.0;
    int n = 1;
    while (part > epsilon) {
        part /= n;
        e += part;
        n++;
    }
    return e;
}

// \== Row


// Equation (dihotomy)

double EqCalcE(double x) {
    return log(x);
}

double EqCalcLn2(double x) {
    return exp(x);
} 

double EqCalcLnSqrt2(double x) {
    return x * x;
}

double EqCalcGamma(double x) {
    return exp(-x);
}

double EqCalc(double left, double right, double value, CalcFunc calc_func, double epsilon) {
    double mid, result;
    do {
        mid = (left + right) / 2.0;
        result = calc_func(mid);      

        if (result > value) {
            right = mid;
        } else {
            left = mid;
        }
    } while (fabs(result - value) > epsilon);
    return mid;
}


double EqCalcPi(double epsilon) {
    double left = 3, right = 4, value = -1;
    double mid, cos_mid, sin_mid;
    int k = 0;
    do {
        mid = (left + right) / 2.0;
        cos_mid = cos(mid);
        sin_mid = sin(mid);

        if (sin_mid < 0) {
            right = mid;
        } else {
            left = mid;
        }

    } while (fabs(cos_mid - value) > epsilon);
    return mid;
}


// \== Eq
