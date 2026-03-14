#include <cstdio>
#include "model.h"
#include "errors.h"

void model_init(model_t &model)
{
    //point_default(model.center);
    //points_default(model.points);
    //edges_init(model.edges);
}

model_t model_create()
{
    model_t model;
    model_init(model);
    return model;
}

void model_free(model_t &model)
{
    //free_points(model.points);
    //edges_free(model.edges);
}

error_code_t model_download(model_t &model, const char *filename)
{
    if (!filename)
        return ERROR_NULL_POINTER;

    error_code_t rc = ERR_OK;

    FILE *file_in = fopen(filename, "r");
    if (!file_in)
    {
        rc = ERR_FILE_OPEN;
    }
    else
    {
        model_t tmp_model;

        rc = file_read_model(tmp_model, file_in);
        fclose(file_in);
        if (rc == ERR_OK)
        {
            model_free(model);
            model = tmp_model;
        }
    }

    return rc;
}

error_code_t file_read_model(model_t &model, FILE *file_in)
{
    if (!file_in)
    {
        return ERR_FILE_INVALID;
    }

    error_code_t rc = ERR_OK;
    model_init(model);

    rc = file_read_points(model.points, file_in);
    if (rc != ERR_OK)
    {
        return rc;
    }

    rc = calculate_center(model.center, model.points);
    if (rc == ERR_OK)
    {
        rc = file_read_edges(model.edges, file_in);
        if (rc != ERR_OK)
        {
            free_points(model.points);
        }
    }
    else
    {
        model_free(model);
    }

    return rc;
}

error_code_t model_scale(model_t &model, const scale_t &scale)
{
    error_code_t rc = scale_points(model.points, model.center, scale);
    if (rc == ERR_OK)
    {
        rc = calculate_center(model.center, model.points);
    }

    return rc;
}

error_code_t model_move(model_t &model, const move_t &move)
{
    error_code_t rc = move_points(model.points, model.center, move);
    if (rc == ERR_OK)
    {
        rc = calculate_center(model.center, model.points);
    }

    return rc;
}

error_code_t model_rotate(model_t &model, const rotate_t &rotate)
{
    error_code_t rc = rotate_points(model.points, model.center, rotate);
    if (rc == ERR_OK)
    {
        rc = calculate_center(model.center, model.points);
    }

    return rc;
}

// Проверка на нулевой указатель
error_code_t model_save(model_t &model, const char *filename)
{
    error_code_t rc = ERR_OK;

    if (!filename)
    {
        return ERR_FILE_POINTER_INVALID;
    }

    FILE *fout = fopen(filename, "w");
    if (!fout)
    {
        rc = ERR_FILE_OUT;
    }
    else
    {
        rc = file_write_points(model.points, fout);
        if (rc == ERR_OK)
        {
            rc = file_write_edges(model.edges, fout);
        }
        fclose(fout);
    }
    return rc;
}

