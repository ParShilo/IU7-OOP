#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum error_code_t
{
    ERROR_OK = 0,
    ERROR_ACTION,
    ERROR_INPUT_POINTS,
    ERROR_AMOUNT_POINTS,
    ERROR_INPUT_EDGES,
    ERROR_AMOUNT_EDGES,
    ERROR_FILE,
    ERROR_FILENAME,
    ERROR_FILE_OPEN,
    ERROR_FILE_WRITE,
    ERROR_MEMORY,
    ERROR_SCENE,
    ERROR_SCENE_SIZES,
    ERROR_POINTS,
    ERROR_EDGES,
    ERROR_EDGE_INDEX
} error_code_t;

void print_error(error_code_t error);

#endif
