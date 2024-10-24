#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "../include/utils.h"
#include "../include/repo.h"
#include <string.h>

int main(int argc, char **argv) {
    double result;

    Response re = GetMatches("test", 2, "./tests/test_1.txt", "./tests/test_2.txt");
    
    if (re.status.code != OK) {
        printf("Error: %s\n", re.status.msg);
        return 1;
    }

    return 0;
}
