#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum error_code_t
{
    ERROR_OK = 0,
    ERROR_ACTION,
    ERROR_NULL_POINTER,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_MEMORY,
    ERROR_FORMAT
} error_code_t;

void print_error(error_code_t error);

#endif
