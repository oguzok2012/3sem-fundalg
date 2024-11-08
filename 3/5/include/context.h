#ifndef METADATA
#define METADATA

#include "repo.h"


typedef struct {
    int students_number;
    const char *input_file;
    const char *output_file;
} Context;

void create_context(Context *context, const char *input_file, const char *output_file);



#endif