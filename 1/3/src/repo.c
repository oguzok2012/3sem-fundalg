#include <stdio.h>
#include <math.h>
#include "repo.h"
#include "utils.h"

void SolveSingleQuadratic(double epsilon, double a, double b, double c) {
    // ax^2 + bx + c = 0

    // 0 = 0
    if (fabs(a) < epsilon && fabs(b) < epsilon && fabs(c) < epsilon) {
        printf("x \u2208 U.\n");
        return;
    }

    // a = 0 => bx + c = 0
    if (fabs(a) < epsilon) {
        if (fabs(b) > epsilon) {
            double solution = -c / b;
            printf("x = %.5f\n", solution);
        } else if (fabs(c) < epsilon) {
             printf("x \u2208 U.\n"); // тождество 0x = 0
        } else {
            printf("x \u2208 \u2205.\n"); // нет решений N = 0, N != 0
        }
        return;
    }

    // a != 0 => ax^2 + bx + c = 0
    double discriminant = b * b - 4 * a * c;

    if (fabs(discriminant) < epsilon) {
        // D = 0
        double solution = -b / (2 * a);
        printf("x = %.5f\n", solution);
    } else if (discriminant > 0) {
        // D > 0
        double solution1 = (-b + pow(discriminant, 0.5)) / (2*a);
        double solution2 = (-b - pow(discriminant, 0.5)) / (2*a);
        printf("x1 = %.5f, x2 = %.5f\n", solution1, solution2);
    } else {
        // D < 0
        printf("x \u2209 R\n"); // нет действительных корней
    }
}


void SolveQuadraticWithPermutations(double epsilon, double *coeffs) {
    SortThreeNumbers(coeffs);
    do {
        double a = coeffs[0], b = coeffs[1], c = coeffs[2];
        printf("(%.2f) * x^2 + (%.2f) * x + (%.2f) = 0\n", a, b, c);
        SolveSingleQuadratic(epsilon, a, b, c);
    } while (FindNextPermutation(coeffs, 3));
}


void CheckDivisibility(int num1, int num2) {
    if (num2 == 0) {
        printf("Can't be divided by zero\n");
        return;
    }
    if (num1 % num2 == 0) {
        printf("%d is divided by %d\n", num1, num2);
    } else {
        printf("%d is NOT divided by %d\n", num1, num2);
    }
}


void CheckRightTriangle(double epsilon, double *sides) {
    SortThreeNumbers(sides);
    double a = sides[0], b = sides[1], c = sides[2];
    if (a <= 0 || b <= 0|| c <= 0) {
        printf("Sides cannot be not positive\n");
        return;
    }

    if (fabs(c * c - (a * a + b * b)) < epsilon) {
        printf("The triangle with sides %.2f, %.2f, %.2f is rectangular\n", a, b, c);
    } else {
        printf("The triangle with sides %.2f, %.2f, %.2f is NOT rectangular\n", a, b, c);
    }
}
