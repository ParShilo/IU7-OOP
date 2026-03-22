#include "actions.h"
#include "model.h"
#include "drawer.h"
#include "loader.h"

error_code_t choose_action(task_t &task)
{
    error_code_t rc = ERROR_OK;
    static model_t model = model_create();

    switch (task.action)
    {
    case DRAW:
        rc = model_draw(model, task.scene);
        break;
    case MOVE:
        rc = model_move(model, task.move);
        break;
    case SCALE:
        rc = model_scale(model, task.scale);
        break;
    case ROTATE:
        rc = model_rotate(model, task.rotate);
        break;
    case OPEN:
        rc = model_download(model, task.file_name);
        break;
    case SAVE:
        rc = model_save(model, task.file_name);
        break;
    case EXIT:
        model_free(model);
        break;
    default:
        rc = ERROR_ACTION;
    }

    return rc;
}
