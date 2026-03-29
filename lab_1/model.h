#ifndef MODEL_H__
#define MODEL_H__

#include "points.h"
#include "edges.h"

typedef struct model_t
{
    point_t center;
    points_t points;
    edges_t edges;
} model_t;

model_t model_create();
void model_init(model_t &model);
void model_free(model_t &model);

error_code_t model_scale(model_t &model, const scale_data_t &scale);
error_code_t model_move(model_t &model, const move_data_t &move);
error_code_t model_rotate(model_t &model, const rotate_data_t &rotate);

error_code_t model_calculate(model_t &model);

#endif
