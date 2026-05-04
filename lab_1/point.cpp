#include <cmath>
#include "point.h"

void point_init(point_t &point)
{
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
}

static void calculate_rotation(double &a, double &b, const rotating value)
{
    double ta = a;
    double tb = b;

    a = ta * value.cos_value + tb * value.sin_value;
    b = -ta * value.sin_value + tb * value.cos_value;
}

static void rotate_x(point_t &point, const double angle_rad)
{
    rotating value = {cos(angle_rad), sin(angle_rad)};
    calculate_rotation(point.y, point.z, value);
}

static void rotate_y(point_t &point, const double angle_rad)
{
    rotating value = {cos(angle_rad), sin(angle_rad)};
    calculate_rotation(point.x, point.z, value);
}

static void rotate_z(point_t &point, const double angle_rad)
{
    rotating value = {cos(angle_rad), sin(angle_rad)};
    calculate_rotation(point.x, point.y, value);
}

static void calculate_scaling(point_t &point, const scale_data_t &scale)
{
    point.x *= scale.kx;
    point.y *= scale.ky;
    point.z *= scale.kz;
}

void point_move(point_t &point, const point_t &move)
{
    point.x += move.x;
    point.y += move.y;
    point.z += move.z;
}

void point_scale(point_t &point, const point_t &center, const scale_data_t &scale)
{
    point_move(point, {-center.x, -center.y, -center.z});
    calculate_scaling(point, scale);
    point_move(point, center);
}

void point_rotate(point_t &point, const point_t &center, const rotate_data_t &rotate)
{
    point_move(point, {-center.x, -center.y, -center.z});
    rotate_x(point, rotate.angle_x);
    rotate_y(point, rotate.angle_y);
    rotate_z(point, rotate.angle_z);
    point_move(point, center);
}

void point_div(point_t &point, double divisor)
{
    point.x /= divisor;
    point.y /= divisor;
    point.z /= divisor;
}
