#include "../include/repo.h"

Response FindSubstringInFile(FILE* input_file, const char* substring, MATCH* matches)
{
    if (input_file == NULL || substring == NULL)
        return CreateErrorResponse(ERROR_NULL_PTR, "Null pointer");

    char buffer[BUFFER_SIZE];
    int index_line = 1;
    int match_index = 0;

    while (fgets(buffer, BUFFER_SIZE, input_file)) {
        char* ptr = buffer;

        printf("\t\tline: %s\n", buffer);
        
        if ((ptr = Strstr(ptr, substring).data) != NULL)
        {
            matches[match_index].line_number = index_line;
            matches[match_index].position = ptr - buffer + 1;

            match_index++;
        
        }

        index_line++;
    }

    return CreateSuccessResponse(matches);
}

Response GetMatches(const char* substring, int count_files, ...)
{
    Response validation_response = ValidateInput(substring, count_files);
    
    if (validation_response.status.code != OK)
        return validation_response;

    va_list files;
    va_start(files, count_files);

    for (int i = 0; i < count_files; i++) {
        char* file_name = va_arg(files, char*);

        if (file_name == NULL) {
            va_end(files);
            return CreateErrorResponse(ERROR_NULL_PTR, "Null pointer");
        }

        Response process_response  = ProcessFile(file_name, substring);

        if (process_response.status.code != OK) {
            va_end(files);
            return process_response;
        }
    }

    va_end(files);
    
    return CreateSuccessResponse(NULL);
}


Response ValidateInput(const char* substring, int count_files)
{
    if (substring == NULL || count_files < 1)  
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");

    return CreateSuccessResponse(NULL);
}

Response ProcessFile(char* file_name, const char* substring)
{
    FILE* file = fopen(file_name, "r");

    if (file == NULL)
        return CreateErrorResponse(ERROR_FILE, "File not found");

    int* max_count_matches = CountLines(file).data;

    if (*max_count_matches == -1) {
        fclose(file);
        return CreateErrorResponse(ERROR_INVALID_INPUT, "Invalid input");
    }

    MATCH* matches = (MATCH*)malloc(*max_count_matches * sizeof(MATCH));

    if (matches == NULL) {
        fclose(file);
        return CreateErrorResponse(ERROR_INVALID_MEMORY, "Memory allocation error");    
    }

    if (FindSubstringInFile(file, substring, matches).status.code == ERROR_NULL_PTR) {
        free(matches);
        fclose(file);
        return CreateErrorResponse(ERROR_INVALID_MEMORY, "Null pointer");
    }

    if (matches[0].line_number != 0)
        PrintMatches(file_name, matches, *max_count_matches);


    free(matches);
    fclose(file);   

    return CreateSuccessResponse(NULL);
}

Response PrintMatches(char* file_name, MATCH* matches, int max_count_matches)
{
    if (file_name == NULL || matches == NULL)
        return CreateErrorResponse(ERROR_NULL_PTR, "File name or matches is NULL");

    printf("File %s:\n", file_name);

    for (int j = 0; j < max_count_matches; j++) {
        if (matches[j].line_number != 0)
            printf("\tline: %d, position: %d\n", matches[j].line_number, matches[j].position);
    }

    return CreateSuccessResponse(NULL);
}