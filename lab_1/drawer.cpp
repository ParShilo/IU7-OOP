#include <QPen>
#include <QBrush>
#include <QColor>

#include "drawer.h"
#include "errors.h"

static void scene_clear_qt(QGraphicsScene *scene)
{
    if (scene)
        scene->clear();
}

static void scene_add_line(QGraphicsScene *scene, const point_t &p1, const point_t &p2)
{
    if (scene)
    {
        QPen pen(Qt::white);
        scene->addLine(p1.x, p1.y, p2.x, p2.y, pen);
    }
}

static void scene_add_point(QGraphicsScene *scene, const point_t &p)
{
    if (scene)
    {
        double r = 2.0;
        QBrush brush(Qt::white);
        QPen pen(Qt::white);
        scene->addEllipse(p.x - r, p.y - r, 2 * r, 2 * r, pen, brush);
    }
}

static error_code_t scene_clear(const scene_t &view)
{
    if (view.scene == NULL)
        return ERROR_SCENE;

    scene_clear_qt(view.scene);

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
    error_code_t rc = ERROR_OK;

    if (view.scene == NULL || view.width <= 0 || view.height <= 0)
        rc = ERROR_SCENE;

    if (rc == ERROR_OK)
    {
        point.x += view.width / 2;
        point.y += view.height / 2;
    }

    return rc;
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
    error_code_t rc = ERROR_OK;

    if (points.arr == NULL)
        rc = ERROR_POINTS;
    else if (edge.first_ind >= points.count || edge.second_ind >= points.count)
        rc = ERROR_EDGE_INDEX;

    if (rc == ERROR_OK)
    {
        line.first = points.arr[edge.first_ind];
        line.second = points.arr[edge.second_ind];
    }

    return rc;
}

static error_code_t edge_draw(const scene_t &view, const edge_t &edge, const points_t &points)
{
    line_t line;

    error_code_t rc = edge_to_line(line, edge, points);

    if (rc == ERROR_OK)
        rc = line_to_display(line, view);

    if (rc == ERROR_OK)
        rc = draw_line_on_scene(view, line);

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
    error_code_t rc = ERROR_OK;

    if (edges.arr == NULL || edges.count <= 0)
        rc = ERROR_EDGES;

    for (size_t i = 0; rc == ERROR_OK && i < edges.count; ++i)
        rc = edge_draw(view, edges.arr[i], points);

    return rc;
}

static error_code_t points_draw(const scene_t &view, const points_t &points)
{
    error_code_t rc = ERROR_OK;

    if (points.arr == NULL || points.count <= 0)
        rc = ERROR_POINTS;

    for (size_t i = 0; rc == ERROR_OK && i < points.count; ++i)
        rc = point_draw(view, points.arr[i]);

    return rc;
}

error_code_t model_draw(const model_t &model, scene_t &view)
{
    error_code_t rc = scene_clear(view);

    if (rc == ERROR_OK)
        rc = edges_draw(view, model.edges, model.points);

    if (rc == ERROR_OK)
        rc = points_draw(view, model.points);

    return rc;
}
