#ifndef ACTIONS_H__
#define ACTIONS_H__

#include "errors.h"
#include "action.h"

enum action
{
    OPEN = 0,
    SAVE,
    DRAW,
    SCALE,
    MOVE,
    ROTATE,
    EXIT
};

typedef struct request_t
{
    enum action action;
    //drawing_view_t view;
    union
    {
        const char *file_name;
        move_t move;
        scale_t scale;
        rotate_t rotate;
    };
} request_t;

error_code_t choose_action(request_t &request);

#endif
