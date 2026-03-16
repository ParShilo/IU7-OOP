#include <QPen>
#include <QBrush>
#include <QColor>
#include <QApplication>
#include <QPalette>

#include "drawer.h"
#include "errors.h"

static void scene_clear_qt(QGraphicsScene *scene)
{
    if (scene)
        scene->clear();
}

static void line_draw_qt(QGraphicsScene *scene, double x1, double y1, double x2, double y2)
{
    if (scene)
    {
        QPen pen(Qt::white);
        scene->addLine(x1, y1, x2, y2, pen);
    }
}

static void point_draw_qt(QGraphicsScene *scene, double x, double y)
{
    if (scene)
    {
        double r = 2.0;
        QBrush brush(Qt::white);
        QPen pen(Qt::white);
        scene->addEllipse(x - r, y - r, 2 * r, 2 * r, pen, brush);
    }
}

static error_code_t scene_clear(const scene_t &view)
{
    if (view.scene == NULL)
        return ERROR_ARGS;

    scene_clear_qt(view.scene);

    return ERROR_OK;
}

static error_code_t to_display(point_t &result, const point_t &point, const scene_t &view)
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

static error_code_t points_get(line_t &line, const scene_t &view, const edge_t &edge, const point_t *array_points, size_t points_count)
{
    error_code_t rc = ERROR_OK;

    if (array_points == NULL || view.scene == NULL || edge.first_ind >= points_count || edge.second_ind >= points_count)
        rc = ERROR_ARGS;

    if (rc == ERROR_OK)
        rc = to_display(line.first, array_points[edge.first_ind], view);

    if (rc == ERROR_OK)
        rc = to_display(line.second, array_points[edge.second_ind], view);

    return rc;
}

static error_code_t line_draw(const scene_t &view, const point_t &p1, const point_t &p2)
{
    if (view.scene == NULL)
        return ERROR_ARGS;

    line_draw_qt(view.scene, p1.x, p1.y, p2.x, p2.y);

    return ERROR_OK;
}

static error_code_t lines_draw(const scene_t &view, const points_t &points, const edges_t &edges)
{
    if (view.scene == NULL || points.arr == NULL || points.count <= 0 || edges.arr == NULL || edges.count <= 0)
        return ERROR_ARGS;

    error_code_t rc = ERROR_OK;
    line_t line;

    for (size_t i = 0; rc == ERROR_OK && i < edges.count; ++i)
    {
        const edge_t &edge = edges.arr[i];
        rc = points_get(line, view, edge, points.arr, points.count);
        if (rc == ERROR_OK)
            rc = line_draw(view, line.first, line.second);
    }

    return rc;
}

static error_code_t points_draw(const scene_t &view, const points_t &points)
{
    if (view.scene == NULL || points.arr == NULL || points.count == 0)
        return ERROR_ARGS;

    error_code_t rc = ERROR_OK;
    point_t display_point;

    for (size_t i = 0; rc == ERROR_OK && i < points.count; ++i)
    {
        rc = to_display(display_point, points.arr[i], view);
        if (rc == ERROR_OK)
            point_draw_qt(view.scene, display_point.x, display_point.y);
    }

    return rc;
}


error_code_t model_draw(const model_t &model, scene_t &view)
{
    error_code_t rc = scene_clear(view);

    if (rc == ERROR_OK)
        rc = lines_draw(view, model.points, model.edges);

    if (rc == ERROR_OK)
        rc = points_draw(view, model.points);

    return rc;
}
