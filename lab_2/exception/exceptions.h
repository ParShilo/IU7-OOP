#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <cstdio>

class BaseException: public std::exception
{
public:
    BaseException(const char *filename, const char *classname, const char *methodname) noexcept;
    const char *what() const noexcept override;

protected:
    static const size_t size = 512;
    char msg[size] = "";
};

class IteratorException : public BaseException 
{
public:
    IteratorException(const char *filename, const char *classname, const char *methodname) noexcept;
};

class TransmittedIteratorException : public BaseException 
{
public:
    TransmittedIteratorException(const char *filename, const char *classname, const char *methodname) noexcept;
};

class EmptyListException : public BaseException 
{
public:
    EmptyListException(const char *filename, const char *classname, const char *methodname) noexcept;
};

class MemoryException : public BaseException 
{
public:
    MemoryException(const char *filename, const char *classname, const char *methodname) noexcept;
};

#endif