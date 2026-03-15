#include "actions.h"
#include "model.h"
#include "drawer.h"
#include "loader.h"

error_code_t choose_action(request_t &request)
{
    error_code_t rc = ERROR_OK;
    static model_t model = model_create();

    switch (request.action)
    {
    case DRAW:
        rc = model_draw(model, request.scene);
        break;
    case MOVE:
        rc = model_move(model, request.move);
        break;
    case SCALE:
        rc = model_scale(model, request.scale);
        break;
    case ROTATE:
        rc = model_rotate(model, request.rotate);
        break;
    case OPEN:
        rc = model_download(model, request.file_name);
        break;
    case SAVE:
        rc = model_save(model, request.file_name);
        break;
    case EXIT:
        model_free(model);
        break;
    default:
        rc = ERROR_ACTION;
    }

    return rc;
}
