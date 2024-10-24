#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <string.h>

int main(int argc, char **argv) {
    Response r = CheckFiniteRepresentation(2, 3, 0.2, 0.25, 0.125);

    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }
    
    return 0;
}
