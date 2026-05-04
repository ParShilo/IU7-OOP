#include "exceptions.h"

BaseException::BaseException(const char *filename, const char *classname, const char *methodname) noexcept
{
    sprintf(msg, "Error occured! File : %s Classname : %s, Method : %s", filename, classname, methodname);
}

const char *BaseException::what() const noexcept 
{
    return msg;
}

IteratorException::IteratorException(const char *filename, const char *classname, const char *methodname) noexcept : 
            BaseException(filename, classname, methodname) {}

TransmittedIteratorException::TransmittedIteratorException(const char *filename, const char *classname, const char *methodname) noexcept : 
            BaseException(filename, classname, methodname) {}

MemoryException::MemoryException(const char *filename, const char *classname, const char *methodname) noexcept : 
            BaseException(filename, classname, methodname) {}

EmptyListException::EmptyListException(const char *filename, const char *classname, const char *methodname) noexcept : 
            BaseException(filename, classname, methodname) {}