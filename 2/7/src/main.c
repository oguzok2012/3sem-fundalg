#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "responses.h"
#include "utils.h"
#include "repo.h"


#define MAX_STRINGS 256
#define MAX_LENGTH 100

#define DECLARE_STRING_ARRAY(name, size) \
    char name##Strings[size][MAX_LENGTH]; \
    char *name[size]; \
    for (int i = 0; i < size; i++) { name[i] = name##Strings[i]; }



Response GetOpts(int argc, char** argv, char **argh) {
    
}


// HANDLERS

int Handler(char** argh) {
}


// \== Handlers


int main(int argc, char **argv) {
    DECLARE_STRING_ARRAY(argh, MAX_STRINGS);
    
    Response response = GetOpts(argc, argv, argh); 
    if (response.status.code != OK) {
        fprintf(stderr, "%s\n", response.status.msg);
        return 1;
    }

    return 0;
}
