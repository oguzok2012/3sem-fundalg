#include <math.h>
#include "repo.h"


double IntegralA (double x) {  
    if (x == 0) {
        return 0;
    }
    return log(1 + x) / x;
}

double IntegralB(double x) {
    return exp(-x * x / 2);
}

double IntegralC(double x) {
    if (x == 0) {
        return 0;
    }
    return log(1 / (1 - x));
}

double IntegralD(double x) {
    return pow(x, x);
}


double Trapez(CalcFunc f, double a, double b, double epsilon) {
    double old_i = 0, new_i = old_i + 2 * epsilon;
    for (int n = 1; fabs(new_i - old_i) > epsilon; n *= 2) {
        old_i = new_i;
        double h = (b - a) / n, s = -(f(a) + f(b)) / 2;
        for (double i = 0; i <= n; i++) {
            s += f(a + i * h);
        }
        new_i = s * h;
    }
    return new_i;
}
