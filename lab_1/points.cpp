#include <cstdlib>

#include "points.h"
#include "errors.h"

void points_init(points_t &points)
{
    points.arr = NULL;
    points.count = 0;
}

void points_free(points_t &points)
{
    free(points.arr);
    points_init(points);
}

error_code_t points_allocate(point_t *&points, size_t count)
{
    error_code_t rc = ERROR_OK;

    if (count <= 0)
        rc = ERROR_AMOUNT_POINTS;
    else
    {
        points = (point_t *) malloc(count * sizeof(point_t));
        if (points == NULL)
            rc = ERROR_MEMORY;
    }

    return rc;
}

static void average_points(point_t &center, const point_t *points, const size_t count)
{
    point_init(center);

    for (size_t i = 0; i < count; i++)
        point_accumulate(center, points[i]);

    point_div_scalar(center, (double) count);
}

error_code_t calculate_center(point_t &center, const points_t &points)
{
    if (points.arr == NULL || points.count <= 0)
        return ERROR_POINTS;

    average_points(center, points.arr, points.count);

    return ERROR_OK;
}

error_code_t points_move(points_t &points, point_t &center, const move_data_t &move)
{
    if (points.arr == NULL || points.count <= 0)
        return ERROR_POINTS;

    for (size_t i = 0; i < points.count; i++)
        point_move(points.arr[i], move);
    point_move(center, move);

    return ERROR_OK;
}

error_code_t points_scale(points_t &points, const point_t &center, const scale_data_t &scale)
{
    if (points.arr == NULL || points.count <= 0)
        return ERROR_POINTS;

    for (size_t i = 0; i < points.count; i++)
        point_scale(points.arr[i], center, scale);

    return ERROR_OK;
}

error_code_t points_rotate(points_t &points, const point_t &center, const rotate_data_t &rotate)
{
    if (points.arr == NULL || points.count <= 0)
        return ERROR_POINTS;

    for (size_t i = 0; i < points.count; i++)
        point_rotate(points.arr[i], center, rotate);

    return ERROR_OK;
}
