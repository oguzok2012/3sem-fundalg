#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Response ExcludeArabicNumerals(char *input_file_name, char *output_file_name);
Response CountLatinLetters(char *input_file_name, char *output_file_name);
Response CountSpecialSymbols(char *input_file_name, char *output_file_name);
Response ReplaceNonDigitWithAsciiHex(char *input_file_name, char *output_file_name);

#endif
