#ifndef ACTIONS_H__
#define ACTIONS_H__

#include "errors.h"
#include "action.h"
#include "drawer.h"

enum action
{
    OPEN,
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
    scene_t scene;
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
