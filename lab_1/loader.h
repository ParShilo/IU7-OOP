#ifndef LOADER_H__
#define LOADER_H__

#include "errors.h"
#include "model.h"

error_code_t model_open(model_t &model, const char *filename);
error_code_t model_save(model_t &model, const char *filename);

#endif
