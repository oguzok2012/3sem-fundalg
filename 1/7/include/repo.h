#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Response ConcatinateLexemes(FILE *file1, FILE *file2, FILE *output);
Response ProcessingFile(FILE *input, FILE *output);

#endif
