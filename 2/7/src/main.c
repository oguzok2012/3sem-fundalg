#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>

int main(int argc, char **argv) {
    double result;

    Response re = DichotomyMethod(0, 2.11111, 0.000000000001, equation2, &result);
    
    printf("Result: %lf\n", result);

    return 0;
}
