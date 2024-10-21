#ifndef __STATUS__
#define __STATUS__

#include "stdio.h"


typedef enum StatusCode {
    OK,
    ERROR_READING_ARGUMENTS,
    ERROR_ATOI,
    ERROR_ATOF,
} StatusCode;


typedef struct Status {
    StatusCode code;
    const char* msg;
} Status;


typedef struct Response {
    Status status;
    void *data;
} Response;


Response CreateErrorResponse(StatusCode code, const char* message);
Response CreateSuccessResponse(void* data_value);

#endif