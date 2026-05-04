#include "drawer.h"
#include "qt_drawer.h"
#include "errors.h"

static error_code_t view_clear(const scene_t &view)
{
    if (view.scene == NULL)
        return ERROR_SCENE;

    scene_clear(view.scene);

    return ERROR_OK;
}

static error_code_t draw_line_on_scene(const scene_t &view, const line_t &line)
{
    if (view.scene == NULL)
        return ERROR_SCENE;

    scene_add_line(view.scene, line.first, line.second);

    return ERROR_OK;
}

static error_code_t draw_point_on_scene(const scene_t &view, const point_t &point)
{
    if (view.scene == NULL)
        return ERROR_SCENE;

    scene_add_point(view.scene, point);

    return ERROR_OK;
}

static error_code_t point_to_display(point_t &point, const scene_t &view)
{
    if (view.scene == NULL)
        return ERROR_SCENE;
    if (view.width <= 0 || view.height <= 0)
        return ERROR_SCENE_SIZES;

    point.x += view.width / 2;
    point.y += view.height / 2;

    return ERROR_OK;
}

static error_code_t line_to_display(line_t &line, const scene_t &view)
{
    error_code_t rc = point_to_display(line.first, view);

    if (rc == ERROR_OK)
        rc = point_to_display(line.second, view);

    return rc;
}

static error_code_t edge_to_line(line_t &line, const edge_t &edge, const points_t &points)
{
    if (points.arr == NULL)
        return ERROR_POINTS;
    else if (edge.first_ind >= points.count || edge.second_ind >= points.count)
        return ERROR_EDGE_INDEX;

    line.first = points.arr[edge.first_ind];
    line.second = points.arr[edge.second_ind];

    return ERROR_OK;
}

static error_code_t edge_draw(const scene_t &view, const edge_t &edge, const points_t &points)
{
    line_t line;

    error_code_t rc = edge_to_line(line, edge, points);

    if (rc == ERROR_OK)
    {
        rc = line_to_display(line, view);
        if (rc == ERROR_OK)
            rc = draw_line_on_scene(view, line);
    }

    return rc;
}

static error_code_t point_draw(const scene_t &view, const point_t &point)
{
    point_t display = point;

    error_code_t rc = point_to_display(display, view);

    if (rc == ERROR_OK)
        rc = draw_point_on_scene(view, display);

    return rc;
}

static error_code_t edges_draw(const scene_t &view, const edges_t &edges, const points_t &points)
{
    if (edges.arr == NULL)
        return ERROR_EDGES;
    if (edges.count <= 0)
        return ERROR_AMOUNT_EDGES;

    error_code_t rc = ERROR_OK;

    for (size_t i = 0; rc == ERROR_OK && i < edges.count; i++)
        rc = edge_draw(view, edges.arr[i], points);

    return rc;
}

static error_code_t points_draw(const scene_t &view, const points_t &points)
{
    if (points.arr == NULL)
        return ERROR_POINTS;
    if (points.count <= 0)
        return ERROR_AMOUNT_POINTS;

    error_code_t rc = ERROR_OK;

    for (size_t i = 0; rc == ERROR_OK && i < points.count; i++)
        rc = point_draw(view, points.arr[i]);

    return rc;
}

error_code_t model_draw(const model_t &model, scene_t &view)
{
    error_code_t rc = view_clear(view);

    if (rc == ERROR_OK)
    {
        rc = edges_draw(view, model.edges, model.points);
        if (rc == ERROR_OK)
            rc = points_draw(view, model.points);
    }

    return rc;
}
