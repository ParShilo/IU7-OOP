#include <cmath>
#include "point.h"

void point_init(point_t &point)
{
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
}

static void to_origin(point_t &point, const point_t &center)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}

static void from_origin(point_t &point, const point_t &center)
{
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

static void calculate_rotation(double &a, double &b, const double cos_value, const double sin_value)
{
    double temp_a = a;
    double temp_b = b;

    a = temp_a * cos_value + temp_b * sin_value;
    b = -temp_a * sin_value + temp_b * cos_value;
}

static void rotate_x(point_t &point, const double angle_rad)
{
    double cos_value = cos(angle_rad);
    double sin_value = sin(angle_rad);
    calculate_rotation(point.y, point.z, cos_value, sin_value);
}

static void rotate_y(point_t &point, const double angle_rad)
{
    double cos_value = cos(angle_rad);
    double sin_value = sin(angle_rad);
    calculate_rotation(point.x, point.z, cos_value, sin_value);
}

static void rotate_z(point_t &point, const double angle_rad)
{
    double cos_value = cos(angle_rad);
    double sin_value = sin(angle_rad);
    calculate_rotation(point.x, point.y, cos_value, sin_value);
}

static void calculate_scaling(point_t &point, const scale_t &scale)
{
    point.x *= scale.kx;
    point.y *= scale.ky;
    point.z *= scale.kz;
}

void point_move(point_t &point, const move_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void point_scale(point_t &point, const point_t &center, const scale_t &scale)
{
    to_origin(point, center);
    calculate_scaling(point, scale);
    from_origin(point, center);
}

void point_rotate(point_t &point, const point_t &center, const rotate_t &rotate)
{
    to_origin(point, center);

    rotate_x(point, rotate.angle_x);
    rotate_y(point, rotate.angle_y);
    rotate_z(point, rotate.angle_z);

    from_origin(point, center);
}
