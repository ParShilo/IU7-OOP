#ifndef DRAWER_H__
#define DRAWER_H__

#include <QGraphicsScene>
#include <QColor>
#include "model.h"

typedef struct scene_t
{
    QGraphicsScene *scene;
    double width;
    double height;
} scene_t;

typedef struct line
{
    point_t first_point;
    point_t second_point;
} line_t;

error_code_t model_draw(const model_t &model, scene_t &scene);

error_code_t clear_scene(const scene_t &view);
error_code_t from_math_to_display(point_t &result, const point_t &point, const scene_t &view);
error_code_t get_points(line_t &line, const scene_t &view, const edge_t &edge, const point_t *array_points, const int points_count);
error_code_t draw_line(const scene_t &view, const point_t &p1, const point_t &p2);
error_code_t draw_lines(const scene_t &view, const points_t &points, const edges_t &edges);

#endif
