#include <cstdio>
#include "loader.h"

static error_code_t point_read(point_t &point, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    double x, y, z;

    if (fscanf(file, "%lf %lf %lf", &x, &y, &z) != 3)
        rc = ERROR_INPUT_POINTS;
    else
    {
        point.x = x;
        point.y = y;
        point.z = z;
    }

    return rc;
}

static error_code_t point_save(FILE* file, const point_t &point)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    if (fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        rc = ERROR_FILE_WRITE;

    return rc;
}

static error_code_t edge_read(edge_t &edge, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    int start, end;

    if (fscanf(file, "%d %d", &start, &end) != 2 || start < 0 || end < 0)
        rc = ERROR_INPUT_EDGES;
    else
    {
        edge.first_ind = start;
        edge.second_ind = end;
    }

    return rc;
}

static error_code_t edge_save(FILE *file, const edge_t &edge)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    if (fprintf(file, "%zu %zu\n", edge.first_ind, edge.second_ind) < 0)
        rc = ERROR_FILE_WRITE;

    return rc;
}

static error_code_t points_read_amount(size_t &count, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    int temp_count = 0;

    if (fscanf(file, "%d", &temp_count) != 1)
        rc = ERROR_INPUT_POINTS;
    else if (temp_count <= 0)
        rc = ERROR_AMOUNT_POINTS;
    else
        count = temp_count;

    return rc;
}

static error_code_t points_read_data(point_t *points, size_t count, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;
    if (points == NULL)
        return ERROR_POINTS;
    if (count <= 0)
        return ERROR_AMOUNT_POINTS;

    error_code_t rc = ERROR_OK;

    for (size_t i = 0; rc == ERROR_OK && i < count; i++)
        rc = point_read(points[i], file);

    return rc;
}

static error_code_t points_read(points_t &points, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = points_read_amount(points.count, file);

    if (rc == ERROR_OK)
    {
        rc = points_allocate(points.arr, points.count);
        if (rc == ERROR_OK)
        {
            rc = points_read_data(points.arr, points.count, file);
            if (rc != ERROR_OK)
                points_free(points);
        }
    }

    return rc;
}

static error_code_t points_save(const points_t &points, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;
    if (points.arr == NULL)
        return ERROR_POINTS;
    if (points.count <= 0)
        return ERROR_AMOUNT_POINTS;

    error_code_t rc = ERROR_OK;

    if (fprintf(file, "%zu\n", points.count) < 0)
        rc = ERROR_FILE_WRITE;

    for (size_t i = 0; rc == ERROR_OK && i < points.count; i++)
        rc = point_save(file, points.arr[i]);

    return rc;
}

static error_code_t edges_read_amount(size_t &count, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    int temp_count = 0;

    if (fscanf(file, "%d", &temp_count) != 1)
        rc = ERROR_INPUT_EDGES;
    else if (temp_count <= 0)
        rc = ERROR_AMOUNT_EDGES;
    else
        count = temp_count;

    return rc;
}

static error_code_t edges_read_data(edge_t *edges, size_t count, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;
    if (edges == NULL)
        return ERROR_EDGES;
    if (count <= 0)
        return ERROR_AMOUNT_EDGES;

    error_code_t rc = ERROR_OK;

    for (size_t i = 0; rc == ERROR_OK && i < count; i++)
        rc = edge_read(edges[i], file);

    return rc;
}

static error_code_t edges_read(edges_t &edges, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = edges_read_amount(edges.count, file);

    if (rc == ERROR_OK)
    {
        rc = edges_allocate(edges.arr, edges.count);
        if (rc == ERROR_OK)
        {
            rc = edges_read_data(edges.arr, edges.count, file);
            if (rc != ERROR_OK)
                edges_free(edges);
        }
    }

    return rc;
}

static error_code_t edges_save(const edges_t &edges, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;
    if (edges.arr == NULL)
        return ERROR_EDGES;
    if (edges.count <= 0)
        return ERROR_AMOUNT_EDGES;

    error_code_t rc = ERROR_OK;

    if (fprintf(file, "%zu\n", edges.count) < 0)
        rc = ERROR_FILE_WRITE;

    for (size_t i = 0; rc == ERROR_OK && i < edges.count; i++)
        rc = edge_save(file, edges.arr[i]);

    return rc;
}

static error_code_t model_read(model_t &model, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = ERROR_OK;

    model_init(model);

    rc = points_read(model.points, file);

    if (rc == ERROR_OK)
    {
        rc = edges_read(model.edges, file);
        if (rc != ERROR_OK)
            points_free(model.points);
    }

    return rc;
}

static error_code_t model_write(model_t &model, FILE *file)
{
    if (file == NULL)
        return ERROR_FILE;

    error_code_t rc = points_save(model.points, file);
    if (rc == ERROR_OK)
        rc = edges_save(model.edges, file);

    return rc;
}

error_code_t model_open(model_t &model, const char *filename)
{
    if (filename == NULL)
        return ERROR_FILENAME;

    error_code_t rc = ERROR_OK;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;
    else
    {
        model_t tmp_model;

        rc = model_read(tmp_model, file);

        fclose(file);

        if (rc == ERROR_OK)
        {
            rc = model_calculate_center(tmp_model);
            if (rc != ERROR_OK)
            {
                model_free(tmp_model);
            }
            else
            {
                model_free(model);
                model = tmp_model;
            }
        }
    }

    return rc;
}

error_code_t model_save(model_t &model, const char *filename)
{
    if (filename == NULL)
        return ERROR_FILENAME;

    error_code_t rc = ERROR_OK;

    FILE *file = fopen(filename, "w");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;
    else
    {
        rc = model_write(model, file);
        fclose(file);
    }

    return rc;
}
