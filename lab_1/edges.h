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

void edges_init(edges_t &edges);
void edges_free(edges_t &edges);
error_code_t edges_allocate(edge_t *&edges, size_t count);

#endif
