#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>

int main(int argc, char **argv) {
    
    double result;
    Response r1 = GeomMean(&result, 3, 2.0, 0.0, 8.0);

    if (r1.status.code != OK) {
        fprintf(stderr, "%s\n", r1.status.msg);
        return 1;
    }

    printf("Result: %lf\n", result);

    Response r2 = FastPow(&result, 2, -2);

    if (r2.status.code != OK) {
        fprintf(stderr, "%s\n", r2.status.msg);
        return 1;
    }

    printf("Result: %lf\n", result);

    return 0;
}
