#ifndef POINT_H__
#define POINT_H__

#include <cstdio>
#include "action.h"

typedef struct point_t
{
    double x;
    double y;
    double z;
} point_t;

void point_init(point_t &point);
void point_scale(point_t &point, const point_t &center, const scale_t &scale_data);
void point_move(point_t &point, const move_t &move);
void point_rotate(point_t &point, const point_t &center, const rotate_t &rotate);

#endif
