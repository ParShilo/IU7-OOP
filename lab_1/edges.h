#ifndef EDGES_H__
#define EDGES_H__

#include <cstdio>
#include "edge.h"
#include "errors.h"

typedef struct edges_t
{
    edge_t *arr;
    size_t count;
} edges_t;

#endif
