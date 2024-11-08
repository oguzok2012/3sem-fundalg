#include "responses.h"


Response CreateErrorResponse(StatusCode code, const char* message) {
    Response response;
    response.status.code = code;
    response.status.msg = message;
    response.data = NULL;
    return response;
}

Response CreateSuccessResponse(void* data_value) {
    Response response;
    response.status.code = OK;
    response.status.msg = NULL;
    response.data = data_value;
    return response;
}
