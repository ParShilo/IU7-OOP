#include <QPen>
#include <QBrush>
#include "qt_drawer.h"

void scene_clear(QGraphicsScene *scene)
{
    if (scene)
        scene->clear();
}

void scene_add_line(QGraphicsScene *scene, const point_t &p1, const point_t &p2)
{
    if (scene)
    {
        QPen pen(Qt::white);
        scene->addLine(p1.x, p1.y, p2.x, p2.y, pen);
    }
}

void scene_add_point(QGraphicsScene *scene, const point_t &p)
{
    if (scene)
    {
        double r = 2.0;
        QBrush brush(Qt::white);
        QPen pen(Qt::white);
        scene->addEllipse(p.x - r, p.y - r, 2 * r, 2 * r, pen, brush);
    }
}
