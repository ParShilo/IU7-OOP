#include <cstdlib>
#include "edges.h"

void edges_init(edges_t &edges)
{
    edges.arr = NULL;
    edges.count = 0;
}

void edges_free(edges_t &edges)
{
    if (edges.arr)
        free(edges.arr);
    edges_init(edges);
}

error_code_t edges_allocate(edge_t *&edges, size_t count)
{
    error_code_t rc = ERROR_OK;

    if (count <= 0)
        rc = ERROR_ARGS;
    else
    {
        edges = (edge_t *) malloc(count * sizeof(edge_t));
        if (edges == NULL)
            rc = ERROR_MEMORY;
    }
    return rc;
}
