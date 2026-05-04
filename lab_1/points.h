#ifndef POINTS_H__
#define POINTS_H__

#include <cstdio>
#include "errors.h"
#include "point.h"

typedef struct points_t
{
    point_t *arr;
    size_t count;
} points_t;

void points_init(points_t &points);
void points_free(points_t &points);
error_code_t points_allocate(point_t *&arr_points, size_t count);

error_code_t calculate_center(point_t &center, const points_t &points);

error_code_t points_move(points_t &points, point_t &center, const point_t &move);
error_code_t points_scale(points_t &points, const point_t &center, const scale_data_t &scale);
error_code_t points_rotate(points_t &points, const point_t &center, const rotate_data_t &rotate);

#endif
