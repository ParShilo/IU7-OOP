#include <cstdio>
#include "model.h"
#include "errors.h"

model_t model_create()
{
    model_t model;
    model_init(model);
    return model;
}

void model_init(model_t &model)
{
    point_init(model.center);
    points_init(model.points);
    edges_init(model.edges);
}

void model_free(model_t &model)
{
    points_free(model.points);
    edges_free(model.edges);
}

error_code_t model_scale(model_t &model, const scale_data_t &scale)
{
    error_code_t rc = points_scale(model.points, model.center, scale);
    if (rc == ERROR_OK)
        rc = calculate_center(model.center, model.points);

    return rc;
}

error_code_t model_move(model_t &model, const move_data_t &move)
{
    error_code_t rc = points_move(model.points, model.center, move);
    if (rc == ERROR_OK)
        rc = calculate_center(model.center, model.points);

    return rc;
}

error_code_t model_rotate(model_t &model, const rotate_data_t &rotate)
{
    error_code_t rc = points_rotate(model.points, model.center, rotate);
    if (rc == ERROR_OK)
        rc = calculate_center(model.center, model.points);

    return rc;
}


