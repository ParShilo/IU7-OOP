#ifndef MODEL_H__
#define MODEL_H__

#include "points.h"
#include "edges.h"

typedef struct model_t
{
    point_t center;
    points_t points;
    edges_t edges;
} model_t;

#endif
