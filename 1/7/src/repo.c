#include "repo.h"

#define MAX_LEXEME_LEN 100


void WriteToBase(FILE *output, int number, int base) {
    if (number < 0) {
        number = -number;
    }
    if (number == 0) {
        fprintf(output, "0 ");
        return;
    }

    char buffer[32];
    char *ptr = &buffer[sizeof(buffer) - 1];
    *ptr = '\0';

    while (number > 0) {
        int digit = number % base;
        *(--ptr) = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= base;
    }

    fprintf(output, "%s ", ptr);
}



Response read_lexeme(FILE *file, char *lexeme, size_t max_len) {
    size_t len = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) {
            break;
        }
    }

    if (ch == EOF) {
        lexeme[0] = '\0';
        return CreateSuccessResponse(NULL);
    }

    do {
        if (len >= max_len) {
            lexeme[len] = '\0';
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Lexeme in file exceeds max len");
        }
        lexeme[len++] = ch;
    } while ((ch = fgetc(file)) != EOF && !isspace(ch));

    lexeme[len] = '\0';

    if (ch == EOF && len == 0) {
        lexeme[0] = '\0';
        return CreateSuccessResponse(NULL);
    }

    return CreateSuccessResponse(NULL);
}


Response ConcatinateLexemes(FILE *file1, FILE *file2, FILE *output) {
    char lexeme[MAX_LEXEME_LEN + 1];
    Response response1, response2;

    if (!file1 || !file2 || !output) {
        return CreateErrorResponse(ERROR_FILE, "One or more files are not opened");
    }

    while (!(feof(file1) && feof(file2))) {
        response1 = read_lexeme(file1, lexeme, MAX_LEXEME_LEN);
        if (response1.status.code != OK) {
            
            return response1;
        }
        if (strlen(lexeme) > 0) {
            fprintf(output, "%s ", lexeme);
        }

        response2 = read_lexeme(file2, lexeme, MAX_LEXEME_LEN);
        if (response2.status.code != OK) {
            return response2;
        }
        if (strlen(lexeme) > 0) {
            fprintf(output, "%s ", lexeme);
        }
    }
    return CreateSuccessResponse(NULL);
}


Response ProcessingFile(FILE *input, FILE *output) {
    char lexeme[MAX_LEXEME_LEN + 1];
    int lexeme_count = 0;

    while (true) {
        Response r = read_lexeme(input, lexeme, MAX_LEXEME_LEN);
        
        if (lexeme[0] == '\0') {
            break;
        }

        if (r.status.code != OK) {
            return r;
        }

        lexeme_count++;

        if (lexeme_count % 10 == 0) {
           for (int i = 0; lexeme[i] != '\0'; i++) {
                lexeme[i] = tolower(lexeme[i]);
            }
            int lexeme_value = 0;
            for (int i = 0; lexeme[i] != '\0'; i++) {
                lexeme_value += (unsigned char)lexeme[i];
            }
            WriteToBaseл(output, lexeme_value, 4);
        } else if (lexeme_count % 2 == 0) {
            for (int i = 0; lexeme[i] != '\0'; i++) {
                if (isalpha(lexeme[i])) {
                    lexeme[i] = tolower(lexeme[i]);
                }
            }
            fprintf(output, "%s ", lexeme);
        } else if (lexeme_count % 5 == 0) {
            int lexeme_value = 0;
            for (int i = 0; lexeme[i] != '\0'; i++) {
                lexeme_value += (unsigned char)lexeme[i];
            }
            WriteToBase(output, lexeme_value, 8);
        }
        else {
            fprintf(output, "%s ", lexeme);
        }
    }
    return CreateSuccessResponse(NULL);
}