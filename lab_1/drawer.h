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
    point_t first;
    point_t second;
} line_t;

error_code_t model_draw(const model_t &model, scene_t &scene);

#endif
