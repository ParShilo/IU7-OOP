#include "exceptions.h"
#include <cstdio>

BaseException::BaseException(const char* file, const char* func, const char* reason) noexcept 
{
    std::snprintf(msg_, sizeof(msg_), "[%s:%s] %s", file, func, reason);
}
const char* BaseException::what() const noexcept 
{
    return msg_;
}