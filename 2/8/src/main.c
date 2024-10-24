#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"




int main() {
    Response r = SumInBase(16, 4, "FF", "0", "1", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    if (r.status.code != OK) {
        fprintf(stderr, "%s\n", r.status.msg);
        return 1;
    }

    printf("Сумма: %s\n", (char*)(r.data));
    free((char*)(r.data));
    return 0;
}

