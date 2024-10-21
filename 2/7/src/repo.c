#include "repo.h"



typedef double (*CalcFunc)(double n);



double EqCalcGamma(double x) {
    return exp(-x);
}

double Dihotomy(double left, double right, double value, CalcFunc calc_func, double epsilon) {
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