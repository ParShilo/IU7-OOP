#ifndef LOADER_H__
#define LOADER_H__

#include "errors.h"
#include "model.h"

error_code_t model_read(model_t &model, FILE *file);
error_code_t model_download(model_t &model, const char *filename);
error_code_t model_save(model_t &model, const char *filename);

error_code_t points_read_amount(size_t &count, FILE *file);
error_code_t points_read_data(point_t *points, size_t count, FILE *file);
error_code_t points_read(points_t &points, FILE *file);
error_code_t points_save(const points_t &points, FILE *file);

error_code_t edges_read_amount(size_t &count, FILE *file);
error_code_t edges_read_data(edges_t *edges, size_t count, FILE *file);
error_code_t edges_read(edges_t &edges, FILE *file);
error_code_t edges_save(const edges_t &edges, FILE *file);

error_code_t point_read(point_t &point, FILE *file);
error_code_t point_save(FILE* file, const point_t &point);

error_code_t edge_read(edge_t &edge, FILE *file);
error_code_t edge_save(FILE *file, const edge_t &edge);

#endif
