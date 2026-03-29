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
    double temp_a = a;
    double temp_b = b;

    a = temp_a * value.cos_value + temp_b * value.sin_value;
    b = -temp_a * value.sin_value + temp_b * value.cos_value;
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

void point_move(point_t &point, const move_data_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void point_scale(point_t &point, const point_t &center, const scale_data_t &scale)
{
    point_t temp_center = {-center.x, -center.y, -center.z};
    point_accumulate(point, temp_center);
    calculate_scaling(point, scale);
    point_accumulate(point, center);
}

void point_rotate(point_t &point, const point_t &center, const rotate_data_t &rotate)
{
    point_t temp_center = {-center.x, -center.y, -center.z};
    point_accumulate(point, temp_center);

    rotate_x(point, rotate.angle_x);
    rotate_y(point, rotate.angle_y);
    rotate_z(point, rotate.angle_z);

    point_accumulate(point, center);
}

void point_accumulate(point_t &point_1, const point_t &point_2)
{
    point_1.x += point_2.x;
    point_1.y += point_2.y;
    point_1.z += point_2.z;
}

void point_div(point_t &point, double divisor)
{
    point.x /= divisor;
    point.y /= divisor;
    point.z /= divisor;
}
