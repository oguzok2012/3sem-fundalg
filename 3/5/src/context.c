#include "context.h"


void create_context(Context *context, const char *input_file, const char *output_file) {
    context->input_file = input_file;
    context->output_file = output_file;
    context->students_number = 0;
}
