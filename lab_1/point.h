#ifndef POINT_H
#define POINT_H

#include "errors.h"

struct point_t
{
    double x;
    double y;
    double z;
};

int point_translate(point_t *point, double dx, double dy, double dz);

int point_scale(point_t *point, double kx, double ky, double kz);

int point_rotate_x(point_t *point, double angle);

int point_rotate_y(point_t *point, double angle);

int point_rotate_z(point_t *point, double angle);

#endif
