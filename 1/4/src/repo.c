#include "repo.h"


Response ExcludeArabicNumerals(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        return CreateErrorResponse(ERROR_FILE, "Error opening input file");
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return CreateErrorResponse(ERROR_FILE, "Error opening output file");
    }

    int symbol;
    while ((symbol = fgetc(input_file)) != EOF) {
        if (!isdigit(symbol)) {
            fputc(symbol, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    return CreateSuccessResponse(NULL);

}


Response CountLatinLetters(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        return CreateErrorResponse(ERROR_FILE, "Error opening input file");
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return CreateErrorResponse(ERROR_FILE, "Error opening output file");
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        int latin_letter_count = 0;

        if (line[strlen(line) - 1] != '\n' && !feof(input_file)) {
            fclose(input_file);
            fclose(output_file);
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow detected. Line in file exceeds buffer size (1024)");
        }

        for (int i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i])) {
                latin_letter_count++;
            }
        }

        fprintf(output_file, "%d\n", latin_letter_count);
    }

    fclose(input_file);
    fclose(output_file);

    return CreateSuccessResponse(NULL);
}


Response CountSpecialSymbols(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        return CreateErrorResponse(ERROR_FILE, "Error opening input file");
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return CreateErrorResponse(ERROR_FILE, "Error opening output file");
    }

    char line[1024];
    int special_symbol_count;
    while (fgets(line, sizeof(line), input_file) != NULL) {
        special_symbol_count = 0;

        if (line[strlen(line) - 1] != '\n' && !feof(input_file)) {
            fclose(input_file);
            fclose(output_file);
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow detected. Line in file exceeds buffer size (1024)");
        }

        for (int i = 0; line[i] != '\0'; i++) {
            if (!isalpha(line[i]) && !isdigit(line[i]) && line[i] != ' ' && line[i] != '\n') {
                special_symbol_count++;
            }
        }

        fprintf(output_file, "%d\n", special_symbol_count);
    }

    fclose(input_file);
    fclose(output_file);

    return CreateSuccessResponse(NULL);
}


Response ReplaceNonDigitWithAsciiHex(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        return CreateErrorResponse(ERROR_FILE, "Error opening input file");
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return CreateErrorResponse(ERROR_FILE, "Error opening output file");
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file) != NULL) {  'z'

        if (line[strlen(line) - 1] != '\n' && !feof(input_file)) {
            fclose(input_file);
            fclose(output_file);
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Buffer overflow detected. Line in file exceeds buffer size (1024)");
        }

        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {
                fputc(line[i], output_file);
            } else {
                fprintf(output_file, "%02X", line[i]);
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    return CreateSuccessResponse(NULL);
}