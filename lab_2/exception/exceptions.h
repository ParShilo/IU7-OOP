#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <cstring>

class BaseException : public std::exception 
{
public:
    BaseException(const char* file, const char* func, const char* reason) noexcept;
    const char* what() const noexcept override;

protected:
    char msg_[512] = {};
};

class LogicException : public BaseException 
{
public:
    LogicException(const char* file, const char* func, const char* reason) noexcept
        : BaseException(file, func, reason) {}
};

class EmptyListException : public LogicException 
{
public:
    EmptyListException(const char* file, const char* func) noexcept
        : LogicException(file, func, "Невалидное изменение пустого списка") {}
};

class InvalidIteratorException : public LogicException 
{
public:
    InvalidIteratorException(const char* file, const char* func) noexcept
        : LogicException(file, func, "Невалидное использование итератора") {}
};

class MemoryException : public BaseException 
{
public:
    MemoryException(const char* file, const char* func) noexcept
        : BaseException(file, func, "Ошибка выделения памяти") {}
};

#endif