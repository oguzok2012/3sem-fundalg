#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>

int main(int argc, char **argv) {
    printf("---------\n");
    IsConvexPolygon(5,   1.0, 0.0,    0.0, 0.0,   0.0, 1.0,   1.0, 1.0,   0.9, 0.4);

    printf("---------\n");
    PolynomlValue(2.0, 2, 3.0, 2.0, 1.0);

    printf("---------\n");
    FindKaprekarNumbers(10, 3,    "45", "297", "46");
    FindKaprekarNumbers(16, 3,    "9", "F", "3F");
        
    return 0;
}
