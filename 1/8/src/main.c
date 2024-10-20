#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"
#include <limits.h>


#define MAX_BASE 36

void act() {
    int a;
}

Response ScanBase(int *base) {
    printf("Enter base (from 2 to 36)\n");
    char str_base[2];
    char c;
    bool wereZeros = false;
    while((c = fgetc(stdin)) == '0') {
        wereZeros = true;
    } 
    if (wereZeros) {
        if (c == '\n' || c == ' ' || c == EOF) {
            return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Incorrect input for base");
        }
    }
    ungetc(c, stdin);
    if (scanf("%2s", str_base) == 0) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Incorrect input for base");
    }
    char extra = fgetc(stdin);
    if (extra != '\n' && extra != ' ' && extra != EOF) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Incorrect input for base");
    }
    Response r = Atoi(str_base);
    if (r.status.code != OK) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Incorrect input for base");
    }
    int temp = *(int*)(r.data);
    if (temp < 2 || temp > 36) {
        return CreateErrorResponse(ERROR_READING_ARGUMENTS, "Incorrect input for base");
    }
    *base = temp;
    return CreateSuccessResponse(NULL);
    
}

int main() {
    int base;
    Response r = ScanBase(&base);
    if (r.status.code != OK) {
        printf("%s\n", r.status.msg);
        return 1;
    }
        
    printf("%d\n", base);
    return 0;
}
