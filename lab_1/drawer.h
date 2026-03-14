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

error_code_t model_draw(model_t &model, scene_t &scene);

#endif
