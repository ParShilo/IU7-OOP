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

typedef struct task_t
{
    enum action action;
    union
    {
        move_data_t move;
        scale_data_t scale;
        rotate_data_t rotate;
        const char *file_name;
    };
    scene_t scene;
} task_t;

error_code_t choose_action(task_t &task);

#endif
