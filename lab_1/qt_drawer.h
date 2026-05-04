#ifndef QT_DRAWER_H__
#define QT_DRAWER_H__

#include <QGraphicsScene>
#include <QColor>
#include "point.h"

void scene_clear(QGraphicsScene *scene);
void scene_add_line(QGraphicsScene *scene, const point_t &p1, const point_t &p2);
void scene_add_point(QGraphicsScene *scene, const point_t &p);

#endif
