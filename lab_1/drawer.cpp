#include <QPen>
#include <QBrush>
#include <QColor>
#include <QApplication>
#include <QPalette>

#include "drawer.h"
#include "errors.h"

static void qt_clear_scene(QGraphicsScene *scene)
{
    if (scene)
        scene->clear();
}

static void qt_draw_line(QGraphicsScene *scene, double x1, double y1, double x2, double y2)
{
    if (scene)
    {
        QPen pen(Qt::white);
        scene->addLine(x1, y1, x2, y2, pen);
    }
}

static void qt_draw_point(QGraphicsScene *scene, double x, double y)
{
    if (scene)
    {
        double r = 2.0;
        QBrush brush(Qt::white);
        QPen pen(Qt::white);
        scene->addEllipse(x - r, y - r, 2 * r, 2 * r, pen, brush);
    }
}

error_code_t clear_scene(const scene_t &view)
{
    error_code_t rc = ERROR_OK;
    if (view.scene == NULL)
        rc = ERROR_ARGS;
    else
        qt_clear_scene(view.scene);
    return rc;
}

error_code_t from_math_to_display(point_t &result, const point_t &point, const scene_t &view)
{
    error_code_t rc = ERROR_OK;
    if (view.scene == NULL || view.width <= 0 || view.height <= 0)
        rc = ERROR_ARGS;

    if (rc == ERROR_OK)
    {
        result = point;
        result.x += view.width / 2;
        result.y += view.height / 2;
    }

    return rc;
}

error_code_t get_points(line_t &line, const scene_t &view, const edge_t &edge, const point_t *array_points, size_t points_count)
{
    error_code_t rc = ERROR_OK;

    if (array_points == NULL || view.scene == NULL || edge.start_ind >= points_count || edge.end_ind >= points_count)
        rc = ERROR_ARGS;

    if (rc == ERROR_OK)
        rc = from_math_to_display(line.first_point, array_points[edge.start_ind], view);

    if (rc == ERROR_OK)
        rc = from_math_to_display(line.second_point, array_points[edge.end_ind], view);

    return rc;
}

error_code_t draw_line(const scene_t &view, const point_t &p1, const point_t &p2)
{
    if (view.scene == NULL)
        return ERROR_ARGS;

    qt_draw_line(view.scene, p1.x, p1.y, p2.x, p2.y);
    return ERROR_OK;
}

error_code_t draw_lines(const scene_t &view, const points_t &points, const edges_t &edges)
{
    if (view.scene == NULL || points.arr == NULL || points.count <= 0 || edges.arr == NULL || edges.count <= 0)
        return ERROR_ARGS;

    error_code_t rc = ERROR_OK;
    line_t line;

    for (size_t i = 0; rc == ERROR_OK && i < edges.count; ++i)
    {
        const edge_t &edge = edges.arr[i];
        rc = get_points(line, view, edge, points.arr, points.count);
        if (rc == ERROR_OK)
            rc = draw_line(view, line.first_point, line.second_point);
    }

    return rc;
}

error_code_t draw_points(const scene_t &view, const points_t &points)
{
    if (view.scene == NULL || points.arr == NULL || points.count == 0)
        return ERROR_ARGS;

    error_code_t rc = ERROR_OK;
    point_t display_point;

    for (size_t i = 0; rc == ERROR_OK && i < points.count; ++i)
    {
        rc = from_math_to_display(display_point, points.arr[i], view);
        if (rc == ERROR_OK)
            qt_draw_point(view.scene, display_point.x, display_point.y);
    }

    return rc;
}


error_code_t model_draw(const model_t &model, scene_t &view)
{
    error_code_t rc = clear_scene(view);
    if (rc != ERROR_OK)
        return rc;

    rc = draw_lines(view, model.points, model.edges);
    if (rc == ERROR_OK)
        rc = draw_points(view, model.points);
    return rc;
}
